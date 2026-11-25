# Copyright (c) 2026 Chris Ohk

import struct
from decimal import Decimal, FloatOperation, localcontext
from fractions import Fraction
from pathlib import Path

import pytest

from pyRosetta import deserialize_self_play_sample, serialize_self_play_sample


GOLDEN = (
    Path(__file__).resolve().parents[2] / "Resources/SchemaGolden/v1/self-play.rssp"
)
MASK_OFFSET = struct.calcsize("<4sII444i")
POLICY_OFFSET = MASK_OFFSET + 4846


def test_golden_round_trip():
    wire = GOLDEN.read_bytes()
    observation, mask, policy, outcome = deserialize_self_play_sample(wire)
    assert observation[:3] == [1, 3, 1]
    assert sum(mask) == 14 and mask[2381] == 1 and policy[2381] == 0
    assert policy[0] == 0.25 and policy[2857] == 0.75 and sum(policy) == 1
    assert outcome == -1

    independent = struct.pack(
        "<4sII444i4846s4846ff",
        b"RSSP", 1, 1, *observation, bytes(mask), *policy, outcome,
    )
    encoded = serialize_self_play_sample(observation, mask, policy, outcome)
    assert encoded == independent == wire

    policy[1] = -0.0
    assert serialize_self_play_sample(observation, mask, policy, outcome) == wire

    draw = serialize_self_play_sample(observation, mask, policy, -0.0)
    assert draw[-4:] == bytes(4)


def test_reads_each_iterable_once():
    class SinglePass:
        def __init__(self, values):
            self.values = values

        def __iter__(self):
            assert self.values is not None, "Iteration requested twice"
            values, self.values = self.values, None
            return iter(values)

    wire = GOLDEN.read_bytes()
    observation, mask, policy, outcome = deserialize_self_play_sample(wire)
    assert serialize_self_play_sample(
        SinglePass(observation), SinglePass(mask), SinglePass(policy), outcome
    ) == wire


@pytest.mark.parametrize(
    "offset,fmt,value",
    [
        (0, "4s", b"junk"),
        (4, "I", 2),                      # Sample version
        (8, "I", 2),                      # Policy version
        (12, "i", 2),                     # Embedded observation version
        (MASK_OFFSET + 1, "B", 2),        # Nonbinary mask
        (MASK_OFFSET, "4846s", b""),      # No legal action
        (MASK_OFFSET, "B", 0),            # Positive mass on a masked move
        (POLICY_OFFSET, "f", 0.125),      # Unnormalized
        (POLICY_OFFSET, "f", -0.25),
        (POLICY_OFFSET, "f", float("nan")),
        (POLICY_OFFSET, "f", float("inf")),
        (-4, "f", 0.5),
        (-4, "f", float("nan")),
        (-4, "f", -float("inf")),
    ],
)
def test_rejects_invalid_wire_values(offset, fmt, value):
    wire = bytearray(GOLDEN.read_bytes())
    struct.pack_into("<" + fmt, wire, offset, value)
    with pytest.raises(ValueError):
        deserialize_self_play_sample(bytes(wire))


def test_rejects_wrong_sizes_and_invalid_fields_on_write():
    wire = GOLDEN.read_bytes()
    for malformed in (wire[:-1], wire + b"\0"):
        with pytest.raises(ValueError):
            deserialize_self_play_sample(malformed)

    fields = deserialize_self_play_sample(wire)
    for index in range(3):
        wrong_shape = list(fields)
        wrong_shape[index] = wrong_shape[index][:-1]
        with pytest.raises(TypeError):
            serialize_self_play_sample(*wrong_shape)

    observation, mask, policy, outcome = fields
    def too_long():
        yield from observation
        yield 0
        pytest.fail("Read beyond the first extra entry")

    with pytest.raises(TypeError):
        serialize_self_play_sample(too_long(), mask, policy, outcome)

    mask[2857] = 0
    with pytest.raises(ValueError):
        serialize_self_play_sample(observation, mask, policy, outcome)


@pytest.mark.parametrize(
    "field,index,value",
    [
        (0, 0, Decimal("1.9")),          # Fractional observation version
        (0, 1, 2**32 + 3),               # Would wrap to the recorded turn number, 3
        (1, 1, Decimal("1.9")),          # Fractional legal mask
        (1, 0, 257),                     # Would wrap to the legal mask value 1
        (2, 1, 1e-50),                   # Masked mass below the float32 range
        (2, 1, Decimal("1e-999")),       # Below the Python float range
        (2, 2381, -1e-50),
        (2, 0, 0.25 + 1j),
        (3, None, 1.00000001),
        (3, None, Decimal("1.00000000000000000001")),
        (3, None, 1e-50),
    ],
)
def test_rejects_invalid_values_before_narrowing(field, index, value):
    row = list(deserialize_self_play_sample(GOLDEN.read_bytes()))
    if index is None:
        row[field] = value
    else:
        row[field][index] = value
    with pytest.raises((TypeError, ValueError)):
        serialize_self_play_sample(*row)


def test_rejects_decimal_probability_above_one_before_narrowing():
    observation, mask, _, outcome = deserialize_self_play_sample(GOLDEN.read_bytes())
    policy = [0.0] * len(mask)
    policy[0] = Decimal("1.00000000000000000001")
    assert float(policy[0]) == 1.0
    with pytest.raises(ValueError):
        serialize_self_play_sample(observation, mask, policy, outcome)


def test_decimal_outcome_preserves_float_operation_flag():
    golden = GOLDEN.read_bytes()
    observation, mask, policy, _ = deserialize_self_play_sample(golden)
    with localcontext() as context:
        context.clear_flags()
        context.traps[FloatOperation] = True
        wire = serialize_self_play_sample(observation, mask, policy, Decimal(1))
        assert not context.flags[FloatOperation]
    assert wire == golden[:-4] + struct.pack("<f", 1)


def test_decimal_rounding_at_policy_sum_boundary():
    golden = GOLDEN.read_bytes()
    observation, mask, policy, outcome = deserialize_self_play_sample(golden)
    policy[0] = 0.24998998641967773
    policy[2857] = Decimal("0.7500000298023224")

    expected = bytearray(golden)
    struct.pack_into("<f", expected, POLICY_OFFSET, policy[0])
    struct.pack_into("<I", expected, POLICY_OFFSET + 4 * 2857, 0x3F400001)
    with localcontext() as context:
        context.traps[FloatOperation] = True
        assert serialize_self_play_sample(observation, mask, policy, outcome) == expected


@pytest.mark.parametrize("lower_bits", [0, 0x007FFFFF, 0x3F400000, 0x3F400001])
def test_fraction_rounding_on_both_sides_of_float32_midpoint(lower_bits):
    observation, mask, policy, outcome = deserialize_self_play_sample(GOLDEN.read_bytes())
    lower, upper = struct.unpack("<ff", struct.pack("<II", lower_bits, lower_bits + 1))
    midpoint = (Fraction(lower) + Fraction(upper)) / 2
    delta = midpoint / 2**60
    policy[0] = 1 - float(midpoint)

    for value, expected in (
        (midpoint - delta, lower_bits),
        (midpoint, lower_bits + (lower_bits & 1)),
        (midpoint + delta, lower_bits + 1),
    ):
        assert float(value) == float(midpoint)
        policy[2857] = value
        wire = serialize_self_play_sample(observation, mask, policy, outcome)
        assert struct.unpack_from("<I", wire, POLICY_OFFSET + 4 * 2857)[0] == expected
