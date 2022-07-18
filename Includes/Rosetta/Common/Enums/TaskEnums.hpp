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
    FRENZY,
    HONORABLE_KILL,
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
    HERO_POWER,
    WEAPON,
    ENEMY_WEAPON,
    HAND,
    HAND_SPELL,
    ENEMY_HAND,
    DECK,
    ENEMY_DECK,
    ALL_MINIONS,
    ALL_MINIONS_NOSOURCE,
    ALL_MINIONS_NOTARGET,
    ALL_MINIONS_NOEVENTSOURCE,
    MINIONS,
    MINIONS_NOSOURCE,
    MINIONS_NOEVENTSOURCE,
    MINIONS_HAND,
    MINIONS_HAND_DECK_FIELD,
    ENEMY_MINIONS,
    ENEMY_MINIONS_LEFTMOST,
    ENEMY_MINIONS_RIGHTMOST,
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

//! \brief An enumerator for identifying the side of summoned minion.
enum class SummonSide
{
    DEFAULT,             //!< Summoning on the last position on the right side.
    LEFT,                //!< Summoning left of the minion.
    RIGHT,               //!< Summoning right of the minion.
    DEATHRATTLE,         //!< Summoning at the last position of the source.
    NUMBER,              //!< Summoning at a given position in the stack number.
    SPELL,               //!< Summoning by spell, currently like default.
    TARGET,              //!< Summoning right of the target.
    ALTERNATE_FRIENDLY,  //!< Summoning on the right side and left side
                         //!< alternately for friendly.
    ALTERNATE_ENEMY,     //!< Summoning on the right side and left side
                         //!< alternately for opponent.
};

//! \brief An enumerator for identifying the position of putting card(s)
//! on the deck.
enum class DeckPosition
{
    RANDOM,  //! Putting card(s) on the random position.
    TOP,     //! Putting card(s) on the top position.
    BOTTOM,  //! Putting card(s) on the bottom position.
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
