// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_SELF_CONDITION_HPP
#define ROSETTASTONE_BATTLEGROUNDS_SELF_CONDITION_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/Common/Enums/TaskEnums.hpp>

#include <functional>

namespace RosettaStone::Battlegrounds
{
class Minion;

//!
//! \brief SelfCondition class.
//!
//! This class is a container for all conditions about the subject entity.
//!
class SelfCondition
{
 public:
    //! Default constructor.
    SelfCondition() = default;

    //! Constructs task with given \p func.
    //! \param func The function to check condition.
    explicit SelfCondition(std::function<bool(Minion&)> func);

 private:
    std::function<bool(Minion&)> m_func;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_SELF_CONDITION_HPP
