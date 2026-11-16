# Copyright (c) 2026 Chris Ohk

import os
import subprocess

import pytest

if os.environ.get("ROSETTA_RL_INTEROP"):
    import torch
    import pyRosettaRL
else:
    torch = pytest.importorskip("torch")
    pyRosettaRL = pytest.importorskip("pyRosettaRL")


def input_batch():
    batch = torch.arange(888, dtype=torch.int32).reshape(2, 444)
    batch[:, 0] = 1
    return batch


def test_cross_runtime_weight_round_trip(tmp_path):
    native = os.environ.get("ROSETTA_RL_INTEROP")

    if not native:
        pytest.skip("Run the RosettaRLWeightInterop CTest for native exchange")

    cpp_weights = tmp_path / "cpp.pt"
    reference_path = tmp_path / "reference.pt"

    subprocess.run([native, "save", str(cpp_weights), str(reference_path)], check=True)

    reference = torch.jit.load(str(reference_path))
    model = pyRosettaRL.PolicyValueNetwork()

    assert isinstance(model, torch.nn.Module)

    model.load_weights(str(cpp_weights))
    logits, values = model(reference.observations)

    torch.testing.assert_close(logits, reference.logits, rtol=1e-5, atol=1e-6)
    torch.testing.assert_close(values, reference.values, rtol=1e-5, atol=1e-6)

    # Distinct Python-side weights prevent a fresh native initialization passing.
    with torch.no_grad():
        for parameter in model.parameters():
            parameter.add_(0.001)

        logits, values = model(reference.observations)

    assert not torch.equal(logits, reference.logits)

    reference.logits = logits
    reference.values = values
    reference.save(str(reference_path))

    python_weights = tmp_path / "python.pt"
    model.save_weights(str(python_weights))

    subprocess.run(
        [native, "check", str(python_weights), str(reference_path)], check=True
    )


@pytest.mark.parametrize("dtype", [torch.float32, torch.float64, torch.float16])
def test_weight_round_trip_preserves_parameter_handles(tmp_path, dtype):
    path = str(tmp_path / "weights.pt")

    source = pyRosettaRL.PolicyValueNetwork()
    source.to(dtype)
    source.save_weights(path)

    target = pyRosettaRL.PolicyValueNetwork()
    target.to(dtype)
    target.eval()

    handles = list(target.parameters())

    target.load_weights(path)

    assert not target.training
    assert all(a is b for a, b in zip(handles, target.parameters()))

    for expected, actual in zip(source(input_batch()), target(input_batch())):
        torch.testing.assert_close(actual, expected, rtol=0, atol=0)


def test_unicode_weight_path_round_trip(tmp_path):
    directory = tmp_path / "한글 폴더"
    directory.mkdir()

    path = directory / "가중치.pt"
    filename = str(path)

    source = pyRosettaRL.PolicyValueNetwork()
    source.save_weights(filename)

    assert list(directory.iterdir()) == [path]

    target = pyRosettaRL.PolicyValueNetwork()
    target.load_weights(filename)

    for expected, actual in zip(source(input_batch()), target(input_batch())):
        torch.testing.assert_close(actual, expected, rtol=0, atol=0)


def test_save_reports_file_open_errors(tmp_path):
    model = pyRosettaRL.PolicyValueNetwork()

    for path in (tmp_path, tmp_path / "missing" / "weights.pt"):
        with pytest.raises(
            RuntimeError, match="Cannot open weight artifact for writing"
        ):
            model.save_weights(str(path))


@pytest.mark.parametrize("inference_parameters", [False, True])
@pytest.mark.parametrize("inference_load", [False, True])
def test_load_preserves_inference_state(tmp_path, inference_parameters, inference_load):
    path = str(tmp_path / "weights.pt")

    source = pyRosettaRL.PolicyValueNetwork()
    source.save_weights(path)

    with torch.inference_mode(inference_parameters):
        target = pyRosettaRL.PolicyValueNetwork()

    handles = list(target.parameters())

    with torch.inference_mode(inference_load):
        target.load_weights(path)
        assert torch.is_inference_mode_enabled() == inference_load

    assert all(p.is_inference() == inference_parameters for p in handles)
    assert all(a is b for a, b in zip(handles, target.parameters()))

    with torch.inference_mode():
        for expected, actual in zip(source(input_batch()), target(input_batch())):
            torch.testing.assert_close(actual, expected, rtol=0, atol=0)

    if not inference_parameters:
        optimizer = torch.optim.SGD(handles, lr=0.01)
        before = handles[0].detach().clone()
        logits, values = target(input_batch())

        (logits.square().mean() + values.square().mean()).backward()

        assert all(p.grad is not None and torch.isfinite(p.grad).all() for p in handles)

        optimizer.step()

        assert not torch.equal(before, handles[0])


@pytest.mark.parametrize(
    "field,value",
    [
        ("format", "AnotherModel"),
        ("artifact_version", 2),
        ("model_version", 2),
        ("observation_version", 2),
        ("policy_version", 2),
    ],
)
def test_incompatible_metadata_is_atomic(tmp_path, field, value):
    assert_failed_load_is_atomic(
        tmp_path, field, lambda archive: setattr(archive, field, value)
    )


@pytest.mark.parametrize(
    "damage,message",
    [
        ("shape", "shape mismatch: value.bias"),
        ("dtype", "dtype/layout mismatch: value.bias"),
        ("missing", "parameter count mismatch"),
        ("extra", "parameter count mismatch"),
        ("renamed", "Missing or invalid weight: value.bias"),
        ("nan", "Non-finite weight: value.bias"),
        ("inf", "Non-finite weight: value.bias"),
    ],
)
def test_invalid_parameters_are_atomic(tmp_path, damage, message):
    def corrupt(archive):
        weights = archive.weights

        if damage == "shape":
            weights["value.bias"] = torch.zeros(2)
        elif damage == "dtype":
            weights["value.bias"] = weights["value.bias"].double()
        elif damage == "missing":
            del weights["value.bias"]
        elif damage == "extra":
            weights["extra"] = torch.zeros(1)
        elif damage == "renamed":
            weights["renamed"] = weights.pop("value.bias")
        else:
            weights["value.bias"].fill_(float(damage))

        archive.weights = weights

    assert_failed_load_is_atomic(tmp_path, message, corrupt)


def assert_failed_load_is_atomic(tmp_path, message, corrupt):
    path = str(tmp_path / "bad.pt")

    source = pyRosettaRL.PolicyValueNetwork()
    source.save_weights(path)

    artifact = torch.jit.load(path)
    corrupt(artifact)
    artifact.save(path)

    target = pyRosettaRL.PolicyValueNetwork()
    before = [parameter.detach().clone() for parameter in target.parameters()]
    outputs = target(input_batch())

    with pytest.raises(RuntimeError, match=message):
        target.load_weights(path)

    for expected, actual in zip(before, target.parameters()):
        assert torch.equal(expected, actual)
    for expected, actual in zip(outputs, target(input_batch())):
        assert torch.equal(expected, actual)


@pytest.mark.parametrize("damage", ["truncated", "garbage", "missing", "no_metadata"])
def test_unreadable_artifact_is_atomic(tmp_path, damage):
    path = tmp_path / "bad.pt"

    target = pyRosettaRL.PolicyValueNetwork()
    target.save_weights(str(path))

    if damage == "truncated":
        path.write_bytes(path.read_bytes()[:64])
    elif damage == "garbage":
        path.write_bytes(b"not a weight archive")
    elif damage == "missing":
        path.unlink()
    else:
        torch.jit.script(torch.nn.Linear(1, 1)).save(str(path))

    before = [parameter.detach().clone() for parameter in target.parameters()]

    with pytest.raises(RuntimeError):
        target.load_weights(str(path))

    for expected, actual in zip(before, target.parameters()):
        assert torch.equal(expected, actual)
