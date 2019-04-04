// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SELF_CONDITION_HPP
#define ROSETTASTONE_SELF_CONDITION_HPP

#include <Rosetta/Enums/CardEnums.hpp>

#include <functional>

namespace RosettaStone
{
class Entity;

//!
//! \brief SelfCondition class.
//!
//! This class is a container for all conditions about the subject entity.
//!
class SelfCondition
{
 public:
    //! Constructs task with given \p func.
    //! \param func The function to check condition.
    SelfCondition(std::function<bool(Entity*)> func);

    //! SelfCondition wrapper for checking race in battlefield.
    static SelfCondition IsControllingRace(Race race);

    //! Evaluates condition using checking function.
    //! \param entity An owner entity.
    //! \return true if the condition is satisfied, false otherwise.
    bool Evaluate(Entity* entity);

 private:
    std::function<bool(Entity*)> m_func;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SELF_CONDITION_HPP
