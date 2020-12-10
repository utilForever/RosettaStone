// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_COMPLEX_TASK_HPP
#define ROSETTASTONE_PLAYMODE_COMPLEX_TASK_HPP

#include <Rosetta/PlayMode/Tasks/SimpleTasks/DestroyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/FilterStackTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/SummonStackTask.hpp>

namespace RosettaStone::PlayMode
{
using SelfCondList = std::vector<std::shared_ptr<SelfCondition>>;
using TaskList = std::vector<std::shared_ptr<ITask>>;

//!
//! \brief ComplexTask class.
//!
//! This class lists complex tasks such as "Summon a minion from your deck.".
//!
class ComplexTask
{
 public:
    //! Returns a list of task for summoning a minion from your deck.
    static TaskList SummonMinionFromDeck()
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(EntityType::DECK),
            std::make_shared<SimpleTasks::FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsMinion()) }),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK, 1),
            std::make_shared<SimpleTasks::SummonStackTask>(true)
        };
    }

    //! Returns a list of task for destroying random enemy minion(s).
    //! \param num The number of minion(s) to destroy.
    static TaskList DestroyRandomEnemyMinion(int num)
    {
        return TaskList{
            std::make_shared<SimpleTasks::IncludeTask>(
                EntityType::ENEMY_MINIONS),
            std::make_shared<SimpleTasks::FilterStackTask>(SelfCondList{
                std::make_shared<SelfCondition>(SelfCondition::IsNotDead()) }),
            std::make_shared<SimpleTasks::RandomTask>(EntityType::STACK, num),
            std::make_shared<SimpleTasks::DestroyTask>(EntityType::STACK)
        };
    }
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_COMPLEX_TASK_HPP
