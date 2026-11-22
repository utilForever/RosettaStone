# Copyright (c) 2026 Chris Ohk

import os
import subprocess
from itertools import repeat

import pytest

if "ROSETTA_RL_TESTS" not in os.environ:
    pytest.skip(
        "Run the RosettaRLPythonTrainer CTest for the native replay",
        allow_module_level=True,
    )

import torch
from pyRosettaRL import PolicyValueNetwork, load_training_batch
from rosetta_rl_trainer import train


@pytest.fixture
def replay_path(tmp_path):
    subprocess.run(
        [os.environ["ROSETTA_RL_TESTS"], "--write-training-batches"],
        cwd=tmp_path,
        check=True,
    )
    return tmp_path / "valid.pt"


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
