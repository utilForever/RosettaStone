// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/PlayCard.hpp>
#include <Rosetta/Tasks/PlayerTasks/PlayCardTask.hpp>

namespace RosettaStone::PlayerTasks
{
PlayCardTask::PlayCardTask(Entity* source, Entity* target, int fieldPos)
    : ITask(source, target), m_fieldPos(fieldPos)
{
    // Do nothing
}

PlayCardTask PlayCardTask::Minion(Player&, Entity* source)
{
    return PlayCardTask(source, nullptr, -1);
}

PlayCardTask PlayCardTask::MinionTarget(Player&, Entity* source,
                                        Entity* target)
{
    return PlayCardTask(source, target, -1);
}

PlayCardTask PlayCardTask::Spell(Player&, Entity* source)
{
    return PlayCardTask(source, nullptr);
}

PlayCardTask PlayCardTask::SpellTarget(Player&, Entity* source, Entity* target)
{
    return PlayCardTask(source, target);
}

PlayCardTask PlayCardTask::Weapon(Player&, Entity* source)
{
    return PlayCardTask(source, nullptr);
}

TaskID PlayCardTask::GetTaskID() const
{
    return TaskID::PLAY_CARD;
}

TaskStatus PlayCardTask::Impl(Player& player)
{
    const auto target = dynamic_cast<Character*>(m_target);
    Generic::PlayCard(player, m_source, target, m_fieldPos);

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::PlayerTasks
