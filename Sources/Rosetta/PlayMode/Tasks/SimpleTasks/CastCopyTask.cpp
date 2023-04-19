// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/CastSpell.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/CastCopyTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
CastCopyTask::CastCopyTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus CastCopyTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    if (playables.empty())
    {
        return TaskStatus::STOP;
    }

    for (auto& playable : playables)
    {
        const auto spell =
            dynamic_cast<Spell*>(Entity::GetFromCard(player, playable->card));

        Generic::CastSpell(player, spell, dynamic_cast<Character*>(m_source),
                           -1);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> CastCopyTask::CloneImpl()
{
    return std::make_unique<CastCopyTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
