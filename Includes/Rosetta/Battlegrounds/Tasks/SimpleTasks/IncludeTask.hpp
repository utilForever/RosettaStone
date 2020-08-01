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
    //! Constructs task with given \p entityType.
    //! \param entityType The entity type of target to include.
    explicit IncludeTask(EntityType entityType);

    //! Returns a list of minions based on the type of entity.
    //! \param entityType The type of entity.
    //! \param player The player to get hand or battlefield.
    //! \param source The source that indicates source minion.
    //! \return A list of minions based on the type of entity.
    static std::vector<std::reference_wrapper<Minion>> GetMinions(
        EntityType entityType, Player& player, Minion& source);

    //! Returns a list of minions based on the type of entity.
    //! \param entityType The type of entity.
    //! \param player The player to get hand or battlefield.
    //! \param source The source that indicates source minion.
    //! \param target The source that indicates target minion.
    //! \return A list of minions based on the type of entity.
    static std::vector<std::reference_wrapper<Minion>> GetMinions(
        EntityType entityType, Player& player, Minion& source, Minion& target);

    //! Runs task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \param source The source minion.
    //! \return The result of task processing.
    TaskStatus Run(Player& player, Minion& source);

    //! Runs task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \param source The source minion.
    //! \param target The target minion.
    //! \return The result of task processing.
    TaskStatus Run(Player& player, Minion& source, Minion& target);

 private:
    EntityType m_entityType = EntityType::INVALID;
};
}  // namespace SimpleTasks
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_INCLUDE_TASK_HPP
