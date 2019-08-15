// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.
//
//// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_ENUMS_HPP
#define ROSETTASTONE_ACTION_ENUMS_HPP

namespace RosettaStone
{
//! \brief An enumerator for identifying main operation type.
enum class MainOpType
{
    PLAY_CARD,
    ATTACK,
    USE_HERO_POWER,
    END_TURN
};

//! \brief An enumerator for identifying action type.
enum class ActionType
{
    INVALID,
    MAIN_ACTION,
    CHOOSE_HAND_CARD,
    CHOOSE_ATTACKER,
    CHOOSE_MINION_PUT_LOCATION,
    CHOOSE_TARGET,
    CHOOSE_ONE
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_ENUMS_HPP
