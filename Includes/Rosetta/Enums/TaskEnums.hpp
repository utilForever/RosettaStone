// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TASK_ENUMS_HPP
#define ROSETTASTONE_TASK_ENUMS_HPP

namespace RosettaStone
{
//! \brief An enumerator for identifying each task.
enum class TaskID
{
    INVALID,
    DRAW,
    DRAW_OP,
    OVERDRAW,
    MANA_CRYSTAL,
    DAMAGE,
    MULLIGAN,
    PLAY_CARD,
    ADD_ENCHANTMENT,
    REMOVE_ENCHANTMENT,
    DESTROY,
    DISCARD,
    HEAL_FULL,
    POISONOUS,
    FREEZE,
    HEAL,
    INCLUDE,
    CONTROL,
    END_TURN,
    CHOOSE,
    ATTACK,
    GET_GAME_TAG,
    SET_GAME_TAG,
    ENQUEUE,
    RANDOM,
    SUMMON,
    TRANSFORM,
    CONDITION,
    FLAG,
    ARMOR,
    RETURN_HAND,
    TEMP_MANA,
    WEAPON,
    FUNC_NUMBER,
    HERO_POWER,
    COPY,
    ADD_STACK_TO,
    COUNT,
    MATH_SUB,
    FILTER_STACK,
    RANDOM_ENTOURAGE,

    NUM_TASK_ID
};

//! \brief An enumerator for identifying entity type.
enum class EntityType
{
    EMPTY,
    SOURCE,
    TARGET,
    ALL,
    FRIENDS,
    ENEMIES,
    ENEMIES_NOTARGET,
    HERO,
    ENEMY_HERO,
    WEAPON,
    ENEMY_WEAPON,
    HAND,
    ENEMY_HAND,
    ALL_MINIONS,
    MINIONS,
    MINIONS_NOSOURCE,
    ENEMY_MINIONS,
    STACK
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TASK_ENUMS_HPP
