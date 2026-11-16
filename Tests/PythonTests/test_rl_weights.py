# Copyright (c) 2026 Chris Ohk

import pytest

torch = pytest.importorskip("torch")
pyRosettaRL = pytest.importorskip("pyRosettaRL")


def input_batch():
    batch = torch.arange(888, dtype=torch.int32).reshape(2, 444)
    batch[:, 0] = 1
    return batch


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
