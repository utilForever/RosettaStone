# Copyright (c) 2026 Chris Ohk

import os
import struct
import subprocess
from concurrent.futures import ThreadPoolExecutor
from itertools import product, repeat
from pathlib import Path

import pytest

if "ROSETTA_RL_TESTS" not in os.environ:
    pytest.skip(
        "Run the RosettaRLPythonTrainer CTest for the native replay",
        allow_module_level=True,
    )

import torch
from pyRosettaRL import PolicyValueNetwork, load_training_batch
from rosetta_rl_trainer import train


GOLDEN = Path(__file__).resolve().parents[2] / "Resources/SchemaGolden/v1/self-play.rssp"


@pytest.fixture
def replay_path(tmp_path):
    subprocess.run(
        [os.environ["ROSETTA_RL_TESTS"], "--write-training-batches"],
        cwd=tmp_path,
        check=True,
    )
    return tmp_path / "valid.pt"


def test_trains_on_self_play_sample(tmp_path, subtests):
    batch = load_training_batch(GOLDEN)
    observations, policy, outcomes = batch
    assert observations.shape == (1, 444)
    assert observations.dtype == torch.int32
    assert observations[0, :3].tolist() == [1, 3, 1]
    assert policy.shape == (1, 4846)
    assert policy.dtype == torch.float32
    assert policy[0, [0, 2857]].tolist() == [0.25, 0.75]
    assert outcomes.tolist() == [-1]
    assert outcomes.dtype == torch.float32

    # The exact binary32 sum is inside 1e-5. A float64 reduction can round outside.
    wire = bytearray(GOLDEN.read_bytes())
    offset = struct.calcsize("<4sII444i4846s")
    near_limit = [0.0] * 4846
    for index, value in (
        (0, 1), (2381, 1e-5), (2385, 1137 * 2.0**-52),
        (2389, 2.0**-54), (2857, 2.0**-54), (2861, 2.0**-149),
    ):
        near_limit[index] = value
    struct.pack_into("<4846f", wire, offset, *near_limit)
    path = tmp_path / "boundary.rssp"
    path.write_bytes(wire)
    boundary_batch = load_training_batch(path)
    assert boundary_batch[1].view(torch.int32)[0, 2861].item() == 1

    devices = ("cpu", "cuda") if torch.cuda.is_available() else ("cpu",)
    for device, dtype in product(devices, (torch.float32, torch.float64)):
        with subtests.test(device=device, dtype=dtype):
            model = PolicyValueNetwork().to(device=device, dtype=dtype)
            inputs = observations.to(device)
            labels = outcomes.to(device=device, dtype=dtype)
            target = boundary_batch[1].to(device=device, dtype=dtype)
            batches = [
                (inputs, policy.to(device=device, dtype=dtype), labels),
                (inputs, target, labels),
            ]
            losses = train(model, batches, tmp_path / "trained.pt")
            assert torch.isfinite(torch.tensor(losses)).all()

            invalid_policy = target.clone()
            invalid_policy[0, 2861] = 2.0**-54
            predictions = model(inputs)
            with pytest.raises(RuntimeError, match="Policy targets"):
                model.training_losses(predictions, invalid_policy, labels)

    cli = [os.environ["ROSETTA_RL_CLI"], "train", tmp_path / "native.pt", path]
    subprocess.run(cli, check=True)

    # One more legal visit probability puts the exact sum outside the tolerance.
    struct.pack_into("<f", wire, offset + 4 * 2861, 2.0**-54)
    path.write_bytes(wire)
    with pytest.raises(ValueError):
        load_training_batch(path)
    rejected = subprocess.run(cli, capture_output=True, text=True)
    assert rejected.returncode != 0
    assert "sum to one" in rejected.stderr


def test_training_rejects_subnormal_masked_mass_and_outcomes(tmp_path):
    wire = bytearray(GOLDEN.read_bytes())
    struct.pack_into("<I", wire, struct.calcsize("<4sII444i4846s") + 4, 1)
    path = tmp_path / "masked.rssp"
    path.write_bytes(wire)
    observation, policy, _ = load_training_batch(GOLDEN)

    def check():
        if not torch.set_flush_denormal(True):
            pytest.skip("CPU does not support toggling denormal flushing")
        with pytest.raises(ValueError, match="Masked"):
            load_training_batch(path)
        for dtype, integer in (
            (torch.float16, torch.int16), (torch.bfloat16, torch.int16),
            (torch.float32, torch.int32), (torch.float64, torch.int64),
        ):
            model = PolicyValueNetwork().to(dtype)
            predictions = model(observation)
            targets = policy.to(dtype)
            invalid = torch.tensor([1], dtype=integer).view(dtype)
            with pytest.raises(RuntimeError, match="Outcomes"):
                model.training_losses(predictions, targets, invalid)
            negative = targets.clone()
            negative.view(integer)[0, 2381] = torch.iinfo(integer).min + 1
            draw = torch.zeros_like(invalid)
            with pytest.raises(RuntimeError, match="Policy targets"):
                model.training_losses(predictions, negative, draw)

    with ThreadPoolExecutor(max_workers=1) as worker:
        worker.submit(check).result()


@pytest.mark.parametrize("dtype", [torch.float16, torch.bfloat16])
def test_low_precision_models_check_the_stored_visit_probabilities(dtype):
    observation, policy, outcome = load_training_batch(GOLDEN)
    model = PolicyValueNetwork().to(dtype)
    targets, labels = policy.to(dtype), outcome.to(dtype)
    predictions = model(observation)
    assert model.training_losses(predictions, targets, labels)[2].isfinite().item()

    targets[0, 0], targets[0, 2857] = 1 / 3, 2 / 3
    assert targets.sum().item() == 1
    assert abs(targets.double().sum().item() - 1) > 1e-5
    with pytest.raises(RuntimeError, match="Policy targets"):
        model.training_losses(predictions, targets, labels)


def test_python_trains_native_replay_and_exchanges_weights(tmp_path, replay_path):
    replay_batch = load_training_batch(replay_path)
    observations, policy, outcomes = replay_batch
    assert not policy.is_inference()

    torch.manual_seed(1074)
    model = PolicyValueNetwork()
    assert isinstance(model, torch.nn.Module)
    model.eval()
    parameters = list(model.parameters())
    before = [p.detach().clone() for p in parameters]

    with torch.no_grad():
        _, _, first = model.training_losses(model(observations), policy, outcomes)

    policy_loss, value_loss, total_loss = train(
        model, repeat(replay_batch, 64), tmp_path / "trained.pt"
    )

    assert model.training
    assert all(p.grad is not None and torch.isfinite(p.grad).all() for p in parameters)
    assert all(not torch.equal(p, old) for p, old in zip(parameters, before))
    assert total_loss < first.item() * 0.15
    assert policy_loss < 0.35
    assert value_loss < 0.02

    with torch.no_grad():
        logits, values = model(observations)
    reference = torch.nn.Module()
    reference.register_buffer("observations", observations)
    reference.register_buffer("logits", logits)
    reference.register_buffer("values", values)
    torch.jit.script(reference).save(str(tmp_path / "reference.pt"))
    subprocess.run(
        [os.environ["ROSETTA_RL_INTEROP"], "check", "trained.pt", "reference.pt"],
        cwd=tmp_path,
        check=True,
    )


def test_inference_replay_step_returns_pre_update_losses(tmp_path, replay_path):
    with torch.inference_mode():
        batch = load_training_batch(replay_path)
    observations, policy, outcomes = batch
    assert policy.is_inference()

    model = PolicyValueNetwork()
    with torch.no_grad():
        losses = model.training_losses(model(observations), policy, outcomes)
        expected = tuple(loss.item() for loss in losses)

    actual = train(model, [batch], tmp_path / "trained.pt")

    assert actual == pytest.approx(expected)
    assert next(model.parameters()).grad is not None


def test_incomplete_training_preserves_checkpoint(tmp_path, replay_path):
    model = PolicyValueNetwork()
    checkpoint = tmp_path / "weights.pt"
    model.save_weights(checkpoint)
    before = checkpoint.read_bytes()

    with pytest.raises(ValueError, match="at least one batch"):
        train(model, [], checkpoint)

    invalid = load_training_batch(tmp_path / "invalid.pt")
    with pytest.raises(RuntimeError, match="Outcomes must be"):
        train(model, [load_training_batch(replay_path), invalid], checkpoint)

    assert checkpoint.read_bytes() == before
