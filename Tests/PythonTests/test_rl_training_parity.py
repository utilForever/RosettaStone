# Copyright (c) 2026 Chris Ohk

import os
import subprocess
from itertools import repeat

import pytest

if "ROSETTA_RL_TRAINING_REFERENCE" not in os.environ:
    pytest.skip(
        "Run the RosettaRLTrainingParity CTest for the native reference",
        allow_module_level=True,
    )

import torch
from pyRosettaRL import PolicyValueNetwork
from rosetta_rl_trainer import train


# CPU float32 contract; see Documents/RosettaRL.md.
RTOL = 1e-5
ATOL = 1e-6


def assert_close(name, actual, expected):
    assert actual is not None, f"{name}: missing Python tensor"
    assert torch.isfinite(actual).all(), f"{name}: non-finite Python tensor"
    assert torch.isfinite(expected).all(), f"{name}: non-finite native tensor"
    torch.testing.assert_close(
        actual,
        expected,
        rtol=RTOL,
        atol=ATOL,
        msg=lambda detail: f"{name}: {detail}",
    )


def assert_named_close(stage, actual, expected):
    assert actual.keys() == expected.keys(), f"{stage}: parameter names differ"
    for name, tensor in actual.items():
        assert_close(f"{stage}.{name}", tensor, expected[name])


def assert_losses_close(stage, actual, expected):
    for name, value, reference in zip(
        ("policy", "value", "total"), actual, expected, strict=True
    ):
        assert_close(
            f"{stage}.{name}", torch.tensor(value, dtype=torch.float64), reference
        )


def test_native_and_python_training_parity(tmp_path):
    subprocess.run(
        [os.environ["ROSETTA_RL_TRAINING_REFERENCE"], "reference.pt"],
        cwd=tmp_path,
        check=True,
    )
    reference = torch.jit.load(str(tmp_path / "reference.pt"), map_location="cpu")
    batch = (reference.observations, reference.policy, reference.outcomes)
    observations, policy, outcomes = batch

    original_threads = torch.get_num_threads()
    torch.set_num_threads(1)
    try:
        torch.manual_seed(1074)
        model = PolicyValueNetwork().eval()
        assert_named_close(
            "initial_weights", dict(model.named_parameters()), reference.initial_weights
        )

        with torch.no_grad():
            logits, values = model(observations)
        assert_close("forward.logits", logits, reference.logits)
        assert_close("forward.values", values, reference.values)

        first = train(model, [batch], tmp_path / "first.pt")
        assert model.training
        assert_losses_close("first_losses", first, reference.first_losses)
        assert_named_close(
            "gradients",
            {name: parameter.grad for name, parameter in model.named_parameters()},
            reference.gradients,
        )
        assert_named_close(
            "step_weights", dict(model.named_parameters()), reference.step_weights
        )

        # Plain SGD has no optimizer state to preserve between these calls.
        last = train(model, repeat(batch, 63), tmp_path / "last.pt")
        assert_losses_close("last_losses", last, reference.last_losses)
        with torch.no_grad():
            logits, values = model(observations)

        for frontend, first_losses, last_losses, final_logits, final_values in (
            (
                "native",
                reference.first_losses,
                reference.last_losses,
                reference.final_logits,
                reference.final_values,
            ),
            ("python", first, last, logits, values),
        ):
            assert last_losses[0] < 0.35, f"{frontend}: policy loss did not overfit"
            assert last_losses[1] < 0.02, f"{frontend}: value loss did not overfit"
            assert last_losses[2] < first_losses[2] * 0.15, (
                f"{frontend}: total loss did not overfit"
            )
            torch.testing.assert_close(
                final_logits.softmax(1),
                policy,
                rtol=0,
                atol=0.1,
                msg=lambda detail: f"{frontend}.overfit.policy: {detail}",
            )
            torch.testing.assert_close(
                final_values,
                outcomes,
                rtol=0,
                atol=0.1,
                msg=lambda detail: f"{frontend}.overfit.values: {detail}",
            )
    finally:
        torch.set_num_threads(original_threads)


def test_parity_failure_names_first_mismatched_tensor():
    expected = {"shared.weight": torch.zeros(2), "policy.bias": torch.zeros(2)}
    actual = {name: tensor + 1 for name, tensor in expected.items()}
    with pytest.raises(AssertionError, match=r"gradients\.shared\.weight") as error:
        assert_named_close("gradients", actual, expected)
    assert "policy.bias" not in str(error.value)
    assert "Greatest absolute difference" in str(error.value)


@pytest.mark.parametrize("value", [float("nan"), float("inf")])
def test_parity_rejects_non_finite_tensors(value):
    tensor = torch.tensor([value])
    with pytest.raises(AssertionError, match="forward.values: non-finite"):
        assert_close("forward.values", tensor, tensor)
