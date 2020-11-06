// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_NEURAL_NET_FIELD_ENUMS_HPP
#define ROSETTASTONE_TORCH_NEURAL_NET_FIELD_ENUMS_HPP

namespace RosettaTorch::NeuralNet
{
//! \brief An enumerator for identifying the side of the field.
enum class FieldSide
{
    INVALID,
    CURRENT,
    OPPONENT
};

//! \brief An enumerator for identifying the type of the field.
enum class FieldType
{
    INVALID,
    MANA_CRYSTAL_CURRENT,
    MANA_CRYSTAL_TOTAL,
    MANA_CRYSTAL_OVERLOAD_OWED,
    MANA_CRYSTAL_OVERLOAD_LOCKED,
    HERO_HEALTH,
    HERO_ARMOR,
    HERO_POWER_PLAYABLE,
    MINION_COUNT,
    MINION_ATTACK,
    MINION_HEALTH,
    MINION_BASE_HEALTH,
    MINION_ATTACKABLE,
    MINION_TAUNT,
    MINION_DIVINE_SHIELD,
    MINION_STEALTH,
    HAND_COUNT,
    HAND_PLAYABLE,
    HAND_COST
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_FIELD_ENUMS_HPP