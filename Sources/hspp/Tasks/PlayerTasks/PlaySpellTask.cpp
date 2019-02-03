// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Enums/TaskEnums.hpp>
#include <hspp/Policy/Policy.hpp>
#include <hspp/Tasks/PlayerTasks/PlaySpellTask.hpp>
#include <hspp/Tasks/SimpleTasks/ModifyManaTask.hpp>

#include <algorithm>

using namespace Hearthstonepp::SimpleTasks;

namespace Hearthstonepp::PlayerTasks
{
PlaySpellTask::PlaySpellTask(Entity* source, Entity* target)
    : ITask(source, target)
{
    // Do nothing
}

TaskID PlaySpellTask::GetTaskID() const
{
    return TaskID::PLAY_SPELL;
}

TaskStatus PlaySpellTask::Impl(Player& player)
{
    BYTE position;

    if (m_target != nullptr)
    {
        const auto fieldIter = std::find(player.GetField().begin(),
                                         player.GetField().end(), m_target);
        position = static_cast<BYTE>(
            std::distance(player.GetField().begin(), fieldIter));
    }
    else
    {
        TaskMeta req = player.GetPolicy().Require(player, TaskID::PLAY_SPELL);
        if (!req.HasObjects())
        {
            return TaskStatus::PLAY_SPELL_FLATBUFFER_NULLPTR;
        }
        position = req.GetObject<BYTE>();
    }

    // Verify field position
    if (position > player.GetField().size())
    {
        return TaskStatus::PLAY_SPELL_POSITION_OUT_OF_RANGE;
    }

    // Verify valid target
    if (player.GetField()[position] == nullptr)
    {
        return TaskStatus::PLAY_SPELL_INVALID_TARGET;
    }

    const auto cost = static_cast<BYTE>(m_source->card->cost);
    const TaskStatus modified =
        ModifyManaTask(ManaOperator::SUB, ManaType::AVAILABLE, cost)
            .Run(player);

    // Process PowerTasks
    if (m_source->card->power != nullptr)
    {
        for (auto& power : m_source->card->power->GetPowerTask())
        {
            power->SetTarget(player.GetField()[position]);
            power->Run(player);
        }
    }

    if (modified == TaskStatus::MODIFY_MANA_SUCCESS)
    {
        return TaskStatus::PLAY_SPELL_SUCCESS;
    }

    return TaskStatus::PLAY_SPELL_MODIFY_MANA_FAIL;
}
}  // namespace Hearthstonepp::PlayerTasks