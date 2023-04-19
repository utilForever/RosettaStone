// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/EnqueueTask.hpp>

#include <utility>

namespace RosettaStone::PlayMode::SimpleTasks
{
EnqueueTask::EnqueueTask(std::vector<std::shared_ptr<ITask>> tasks, int num,
                         bool isSpellDamage)
    : m_tasks(std::move(tasks)), m_num(num), m_isSpellDamage(isSpellDamage)
{
    // Do nothing
}

TaskStatus EnqueueTask::Impl(Player* player)
{
    int times = m_num;

    if (m_isSpellDamage)
    {
        times += m_source->player->GetCurrentSpellPower();

        if (const auto spell = dynamic_cast<Spell*>(m_source); spell)
        {
            const SpellSchool spellSchool = spell->GetSpellSchool();
            times += m_source->player->GetExtraSpellPower(spellSchool);
        }
    }

    for (int i = 0; i < times; ++i)
    {
        for (const auto& task : m_tasks)
        {
            std::unique_ptr<ITask> clonedTask = task->Clone();

            clonedTask->SetPlayer(player);
            clonedTask->SetSource(m_source);
            clonedTask->SetTarget(m_target);

            player->game->taskQueue.Enqueue(std::move(clonedTask));
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> EnqueueTask::CloneImpl()
{
    return std::make_unique<EnqueueTask>(m_tasks, m_num, m_isSpellDamage);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
