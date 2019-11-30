// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/SummonCopyTask.hpp>

namespace RosettaStone::SimpleTasks
{
SummonCopyTask::SummonCopyTask(EntityType entityType, bool randomFlag,
                               bool addToStack, SummonSide side)
    : ITask(entityType),
      m_side(side),
      m_randomFlag(randomFlag),
      m_addToStack(addToStack)
{
    // Do nothing
}

TaskStatus SummonCopyTask::Impl(Player* player)
{
    return TaskStatus::COMPLETE;
}

ITask* SummonCopyTask::CloneImpl()
{
    return new SummonCopyTask(m_entityType, m_randomFlag, m_addToStack, m_side);
}
}  // namespace RosettaStone::SimpleTasks
