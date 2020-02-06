// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/ChangeAttackingTargetTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::SimpleTasks
{
ChangeAttackingTargetTask::ChangeAttackingTargetTask(EntityType typeA,
                                                     EntityType typeB)
    : m_typeA(typeA), m_typeB(typeB)
{
    // Do nothing
}

TaskStatus ChangeAttackingTargetTask::Impl(Player* player)
{
    auto typeA = IncludeTask::GetEntities(m_typeA, player, m_source, m_target);
    auto typeB = IncludeTask::GetEntities(m_typeB, player, m_source, m_target);

    if (typeA.size() != 1 || typeB.size() != 1)
    {
        return TaskStatus::STOP;
    }

    const auto attacker = dynamic_cast<Character*>(typeA[0]);
    const auto newDefender = dynamic_cast<Character*>(typeB[0]);

    if (attacker == nullptr || newDefender == nullptr)
    {
        return TaskStatus::STOP;
    }

    player->game->currentEventData->eventTarget = newDefender;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ChangeAttackingTargetTask::CloneImpl()
{
    return std::make_unique<ChangeAttackingTargetTask>(m_typeA, m_typeB);
}
}  // namespace RosettaStone::SimpleTasks
