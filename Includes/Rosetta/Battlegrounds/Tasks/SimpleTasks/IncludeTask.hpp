// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_INCLUDE_TASK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_INCLUDE_TASK_HPP

#include <Rosetta/Common/Enums/TaskEnums.hpp>

#include <vector>

namespace RosettaStone::Battlegrounds
{
class Minion;
class Player;

namespace SimpleTasks
{
//!
//! \brief IncludeTask class.
//!
//! This class represents the task for including minions to be applied by
//! another task.
//!
class IncludeTask
{
 public:
    //! Returns a list of minions based on the type of entity.
    //! \param entityType The type of entity.
    //! \param player The player to get hand or battlefield.
    //! \param source The source that indicates source minion.
    //! \return A list of minions based on the type of entity.
    static std::vector<std::reference_wrapper<Minion>> GetMinions(
        EntityType entityType, Player& player, Minion& source);
};
}  // namespace SimpleTasks
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_INCLUDE_TASK_HPP
