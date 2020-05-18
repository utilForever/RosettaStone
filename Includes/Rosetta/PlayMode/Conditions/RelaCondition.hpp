// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_RELA_CONDITION_HPP
#define ROSETTASTONE_PLAYMODE_RELA_CONDITION_HPP

#include <functional>

namespace RosettaStone::PlayMode
{
class Playable;

//!
//! \brief RelaCondition class.
//!
//! This class is a container for all conditions about the relation
//! between 2 entities.
//!
class RelaCondition
{
 public:
    //! Constructs task with given \p func.
    //! \param func The function to check condition.
    explicit RelaCondition(std::function<bool(Playable*, Playable*)> func);

    //! RelaCondition wrapper for checking the entity is friendly.
    //! \return Generated RelaCondition for intended purpose.
    static RelaCondition IsFriendly();

    //! RelaCondition wrapper for checking the entity is positioned side by
    //! side.
    //! \return Generated RelaCondition for intended purpose.
    static RelaCondition IsSideBySide();

    //! Evaluates condition using checking function.
    //! \param owner The owner entity.
    //! \param affected The affected entity.
    //! \return true if the condition is satisfied, false otherwise.
    bool Evaluate(Playable* owner, Playable* affected) const;

 private:
    std::function<bool(Playable*, Playable*)> m_func;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_RELA_CONDITION_HPP
