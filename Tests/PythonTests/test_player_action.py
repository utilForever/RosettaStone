import pytest

from pyRosetta import PlayerAction, PlayerActionType


def test_action_defaults_and_fields():
    action = PlayerAction()

    assert action.type == PlayerActionType.END_TURN
    assert action.source_id == action.target_id == action.field_pos == -1
    assert action.choose_one == 0
    assert action.choice_id == -1

    action = PlayerAction(
        PlayerActionType.PLAY_CARD,
        source_id=12,
        target_id=5,
        field_pos=2,
        choose_one=1,
    )

    assert action.source_id == 12
    assert action.target_id == 5
    assert action.field_pos == 2
    assert action.choose_one == 1
    assert action == PlayerAction(PlayerActionType.PLAY_CARD, 12, 5, 2, 1)

    action.choice_id = 17

    assert action.choice_id == 17
    assert action != PlayerAction(PlayerActionType.PLAY_CARD, 12, 5, 2, 1)


@pytest.mark.parametrize(
    "field,value",
    [
        ("type", PlayerActionType.PLAY_CARD),
        ("source_id", 1),
        ("target_id", 1),
        ("field_pos", 0),
        ("choose_one", 1),
        ("choice_id", 1),
    ],
)
def test_action_comparisons(field, value):
    first = PlayerAction()
    second = PlayerAction(**{field: value})

    assert first != second
    assert first < second
    assert first <= second
    assert second > first
    assert second >= first
    assert sorted([second, first]) == [first, second]
    assert first <= PlayerAction() <= first


def test_action_comparisons_with_unrelated_type():
    action = PlayerAction()
    other = object()

    for method in ("__eq__", "__ne__", "__lt__", "__le__", "__gt__", "__ge__"):
        assert getattr(action, method)(other) is NotImplemented

    assert action != other

    with pytest.raises(TypeError):
        assert action < other
