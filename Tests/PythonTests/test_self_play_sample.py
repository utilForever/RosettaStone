# Copyright (c) 2026 Chris Ohk

import ctypes
import struct
import warnings
from array import array
from concurrent.futures import ThreadPoolExecutor
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
    assert sum(mask) == 14
    assert mask[2381] == 1
    assert policy[2381] == 0
    assert policy[0] == 0.25
    assert policy[2857] == 0.75
    assert sum(policy) == 1
    assert outcome == -1

    independent = struct.pack(
        "<4sII444i4846s4846ff",
        b"RSSP", 1, 1, *observation, bytes(mask), *policy, outcome,
    )
    encoded = serialize_self_play_sample(observation, mask, policy, outcome)
    assert independent == wire
    assert encoded == wire

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

    long_observation = too_long()
    with pytest.raises(TypeError):
        serialize_self_play_sample(long_observation, mask, policy, outcome)

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


def test_requires_scalar_entries_and_outcome():
    torch = pytest.importorskip("torch")
    for field, index in ((0, 0), (1, 0), (2, 0), (3, None)):
        row = list(deserialize_self_play_sample(GOLDEN.read_bytes()))
        if index is None:
            row[field] = torch.tensor([[-1.0]])
        else:
            row[field][index] = torch.tensor([row[field][index]])
        with pytest.raises((TypeError, ValueError)):
            serialize_self_play_sample(*row)

    observation, mask, policy, outcome = deserialize_self_play_sample(GOLDEN.read_bytes())
    assert serialize_self_play_sample(
        torch.tensor(observation), torch.tensor(mask),
        torch.tensor(policy), torch.tensor(outcome),
    ) == GOLDEN.read_bytes()
    complex_outcome = torch.tensor(-1 + 0j)
    with pytest.raises(TypeError):
        serialize_self_play_sample(observation, mask, policy, complex_outcome)


@pytest.mark.parametrize("dtype", ["complex64", "complex128"])
def test_rejects_numpy_complex_before_float_conversion(dtype):
    np = pytest.importorskip("numpy")
    observation, mask, policy, outcome = deserialize_self_play_sample(GOLDEN.read_bytes())
    with warnings.catch_warnings():
        warnings.simplefilter("error")
        for imaginary in (0, 0.75):
            value = np.array(complex(0.25, imaginary), dtype=dtype)
            for scalar in (value, value[()], np.array(value[()], dtype=object)):
                policy[0] = scalar
                with pytest.raises(TypeError):
                    serialize_self_play_sample(observation, mask, policy, outcome)


@pytest.mark.parametrize(
    "field,index,dtype",
    [(0, 0, "int32"), (1, 0, "uint8"), (2, 0, "float64"), (3, None, "float64")],
)
def test_numpy_masked_scalars_require_a_value(field, index, dtype):
    np = pytest.importorskip("numpy")
    golden = GOLDEN.read_bytes()
    row = list(deserialize_self_play_sample(golden))
    entries, slot = (row, field) if index is None else (row[field], index)
    scalar = np.ma.array(entries[slot], mask=False, dtype=dtype)
    entries[slot] = scalar

    with warnings.catch_warnings():
        warnings.simplefilter("error")
        assert serialize_self_play_sample(*row) == golden
        scalar.mask = True
        with pytest.raises(ValueError, match="masked"):
            serialize_self_play_sample(*row)


@pytest.mark.parametrize("dtype", ["timedelta64[ns]", "datetime64[ns]", "U1"])
def test_rejects_nonnumeric_numpy_policy_dtype(dtype):
    np = pytest.importorskip("numpy")
    observation, mask, policy, outcome = deserialize_self_play_sample(GOLDEN.read_bytes())
    policy[2857] = 0
    value = np.array(1, dtype=dtype)
    for entry in (value, value[()]):
        policy[0] = entry
        with pytest.raises(TypeError):
            serialize_self_play_sample(observation, mask, policy, outcome)


def test_numpy_object_rows_validate_their_individual_entries():
    np = pytest.importorskip("numpy")
    golden = GOLDEN.read_bytes()
    observation, mask, policy, outcome = deserialize_self_play_sample(golden)
    row = np.array(policy, dtype=object)
    assert serialize_self_play_sample(observation, mask, row, outcome) == golden
    object_outcome = np.array(outcome, dtype=object)
    with pytest.raises(TypeError):
        serialize_self_play_sample(observation, mask, row, object_outcome)


def test_lazy_policy_uses_the_callers_float_mode():
    torch = pytest.importorskip("torch")
    golden = GOLDEN.read_bytes()
    observation, mask, policy, outcome = deserialize_self_play_sample(golden)
    tensor = torch.tensor(policy, dtype=torch.float32)
    tensor.view(torch.int32)[1] = 1  # The smallest binary32 on a masked action.

    class ComputedRow(array):
        def __iter__(self):
            return map(float, tensor)

    class ComputedItems(ctypes.c_float * len(policy)):
        def __getitem__(self, index):
            return float(tensor[index])

    def check():
        if not torch.set_flush_denormal(True):
            pytest.skip("CPU does not support toggling denormal flushing")
        for row in (
            list(map(float, tensor)), map(float, tensor), ComputedRow("f", policy),
            iter(ComputedItems()),
        ):
            assert serialize_self_play_sample(observation, mask, row, outcome) == golden
        with pytest.raises(ValueError):
            serialize_self_play_sample(observation, mask, tensor, outcome)
        assert float(tensor[1]) == 0.0

    with ThreadPoolExecutor(max_workers=1) as worker:
        worker.submit(check).result()


def test_subnormal_probability_bits_in_both_flush_modes():
    torch = pytest.importorskip("torch")
    golden = GOLDEN.read_bytes()
    base_policy = deserialize_self_play_sample(golden)[2]
    legal = POLICY_OFFSET + 4 * 2381

    def check_modes():
        for flush in (False, True):
            if not torch.set_flush_denormal(flush):
                pytest.skip("CPU does not support toggling denormal flushing")
            for bits in (1, 0x007FFFFF):
                wire = bytearray(golden)
                struct.pack_into("<I", wire, legal, bits)
                fields = deserialize_self_play_sample(bytes(wire))
                assert fields[2][2381] == bits * 2.0**-149
                assert serialize_self_play_sample(*fields) == wire
                scalar = torch.tensor(bits, dtype=torch.int32).view(torch.float32)
                fields[2][2381] = scalar
                assert serialize_self_play_sample(*fields) == wire
                buffer = array("f", base_policy)
                words = memoryview(buffer).cast("B").cast("I")
                words[2381] = bits
                c_buffer = (ctypes.c_float * len(buffer)).from_buffer(buffer)
                buffers = (buffer, memoryview(buffer), c_buffer)
                for stored in buffers:
                    for row in (stored, iter(stored)):
                        assert serialize_self_play_sample(
                            fields[0], fields[1], row, fields[3]
                        ) == wire
                assert serialize_self_play_sample(
                    fields[0], fields[1], reversed(buffer[::-1]), fields[3]
                ) == wire
                words[1] = bits  # The same stored probability on an illegal action.
                for stored in buffers:
                    row = iter(stored)
                    with pytest.raises(ValueError):
                        serialize_self_play_sample(
                            fields[0], fields[1], row, fields[3]
                        )
                assert float(scalar) == (0.0 if flush else bits * 2.0**-149)

            for offset, invalid in ((POLICY_OFFSET + 4, 1), (legal, 0x80000001), (-4, 1)):
                wire = bytearray(golden)
                struct.pack_into("<I", wire, offset, invalid)
                with pytest.raises(ValueError):
                    deserialize_self_play_sample(bytes(wire))

            fields = deserialize_self_play_sample(golden)
            with pytest.raises(ValueError):
                serialize_self_play_sample(*fields[:3], scalar)
            assert float(scalar) == (0.0 if flush else bits * 2.0**-149)

    # The floating-point mode belongs to the worker thread.
    with ThreadPoolExecutor(max_workers=1) as worker:
        worker.submit(check_modes).result()
