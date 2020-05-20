// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.
//
//// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_ACTION_ENUMS_HPP
#define ROSETTASTONE_ACTION_ENUMS_HPP

#include <string>

namespace RosettaStone
{
//! \brief An enumerator for identifying main operation type.
enum class MainOpType
{
    INVALID,
    PLAY_CARD,
    ATTACK,
    USE_HERO_POWER,
    END_TURN
};

//! \brief An enumerator for identifying action type.
enum class ActionType
{
    INVALID,
    RANDOM,
    MAIN_ACTION,
    CHOOSE_HAND_CARD,
    CHOOSE_ATTACKER,
    CHOOSE_MINION_PUT_LOCATION,
    CHOOSE_TARGET,
    CHOOSE_ONE
};

//! Returns the string of the main operation type.
//! \param op The main operation type.
//! \return The string of the main operation type.
inline std::string GetMainOpString(MainOpType op)
{
    switch (op)
    {
        case MainOpType::INVALID:
            return "INVALID";
        case MainOpType::PLAY_CARD:
            return "PLAY_CARD";
        case MainOpType::ATTACK:
            return "ATTACK";
        case MainOpType::USE_HERO_POWER:
            return "USE_HERO_POWER";
        case MainOpType::END_TURN:
            return "END_TURN";
        default:
            return "UNKNOWN";
    }
}
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ACTION_ENUMS_HPP
