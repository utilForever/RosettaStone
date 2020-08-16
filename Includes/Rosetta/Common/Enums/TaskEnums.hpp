// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TASK_ENUMS_HPP
#define ROSETTASTONE_TASK_ENUMS_HPP

namespace RosettaStone
{
//! \brief An enumerator for identifying the result of the task.
enum class TaskStatus : unsigned int
{
    INVALID,
    STOP,
    COMPLETE,

    NUM_TASK_STATUS
};

//! \brief An enumerator for identifying power type.
enum class PowerType
{
    POWER,
    DEATHRATTLE,
    COMBO,
    OUTCAST,
    SPELLBURST,
    START_OF_COMBAT,
};

//! \brief An enumerator for identifying entity type.
enum class EntityType
{
    INVALID,
    SOURCE,
    TARGET,
    ALL,
    ALL_NOSOURCE,
    FRIENDS,
    ENEMIES,
    ENEMIES_NOTARGET,
    HERO,
    ENEMY_HERO,
    HEROES,
    WEAPON,
    ENEMY_WEAPON,
    HAND,
    ENEMY_HAND,
    DECK,
    ENEMY_DECK,
    ALL_MINIONS,
    ALL_MINIONS_NOSOURCE,
    ALL_MINIONS_NOEVENTSOURCE,
    MINIONS,
    MINIONS_NOSOURCE,
    MINIONS_NOEVENTSOURCE,
    ENEMY_MINIONS,
    ENEMY_SECRETS,
    GRAVEYARD,
    STACK,
    STACK_NUM0,
    STACK_NUM1,
    PLAYER,
    ENEMY_PLAYER,
    EVENT_SOURCE,
    EVENT_TARGET,
};

//! \brief An enumerator for evaluating the relation between primitive values
//! during game simulation.
enum class RelaSign
{
    EQ,   //!< Equal.
    GEQ,  //!< Greater equal.
    LEQ   //!< Lesser equal.
};

//! \brief An enumerator for identifying the button of Tavern in Battlegrounds.
enum class TavernButton
{
    UPGRADE,
    REFRESH,
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TASK_ENUMS_HPP
