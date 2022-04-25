// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/DredgeTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DredgeTask::DredgeTask(bool addToStack) : m_addToStack(addToStack)
{
    // Do nothing
}

TaskStatus DredgeTask::Impl(Player* player)
{
    auto deck = player->GetDeckZone();

    if (deck->IsEmpty())
    {
        return TaskStatus::STOP;
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DredgeTask::CloneImpl()
{
    return std::make_unique<DredgeTask>(m_addToStack);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
