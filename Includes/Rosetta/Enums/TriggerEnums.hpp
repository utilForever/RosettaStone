// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TRIGGER_ENUMS_HPP
#define ROSETTASTONE_TRIGGER_ENUMS_HPP

namespace RosettaStone
{
//! \brief An enumerator for identifying trigger type.
enum class TriggerType
{
    NONE,        //!< The effect has nothing.
    TURN_START,  //!< The effect will be triggered at the start of turn.
    TURN_END,    //!< The effect will be triggered at the end of turn.
    HEAL,        //!< The effect will be triggered when characters are healed.
    ATTACK,      //!< The effect will be triggered when characters attack.
    SUMMON,      //!< The effect will be triggered whenever a minion is summoned.
};

//! \brief An enumerator for identifying trigger source.
enum class TriggerSource
{
    NONE,
    HERO,
    ALL_MINIONS,
};

//! \brief An enumerator for identifying sequence type.
enum class SequenceType
{
    NONE,
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_ENUMS_HPP
