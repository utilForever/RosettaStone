# Copyright (c) 2026 Chris Ohk

import struct
from pathlib import Path

import pytest

from pyRosetta import deserialize_self_play_sample


GOLDEN = (
    Path(__file__).resolve().parents[2] / "Resources/SchemaGolden/v1/self-play.rssp"
)
MASK_OFFSET = struct.calcsize("<4sII444i")
POLICY_OFFSET = MASK_OFFSET + 4846


def test_reads_golden_sample():
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
    assert independent == wire


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


def test_rejects_wrong_sizes():
    wire = GOLDEN.read_bytes()
    for malformed in (wire[:-1], wire + b"\0"):
        with pytest.raises(ValueError):
            deserialize_self_play_sample(malformed)
