// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Policies/Policy.hpp>
#include <hspp/Tasks/PlayerTasks/PlayMinionTask.hpp>
#include <hspp/Tasks/SimpleTasks/ModifyManaTask.hpp>

using namespace Hearthstonepp::SimpleTasks;

namespace Hearthstonepp::PlayerTasks
{
PlayMinionTask::PlayMinionTask(Entity* source, int fieldPos, Entity* target)
    : ITask(source, target), m_fieldPos(fieldPos)
{
    // Do nothing
}

TaskID PlayMinionTask::GetTaskID() const
{
    return TaskID::PLAY_MINION;
}

TaskStatus PlayMinionTask::Impl(Player& player)
{
    BYTE position;

    if (m_fieldPos == -1)
    {
        const auto emptyPos = player.GetField().FindEmptyPos().value_or(
            std::numeric_limits<std::size_t>::max());
        if (emptyPos == std::numeric_limits<std::size_t>::max())
        {
            return TaskStatus::PLAY_MINION_FIELD_IS_FULL;
        }

        position = static_cast<BYTE>(emptyPos);
    }
    else
    {
        TaskMeta req = player.GetPolicy().Require(player, TaskID::PLAY_MINION);

        if (!req.HasObjects())
        {
            return TaskStatus::PLAY_MINION_INVALID_REQUIRE;
        }

        position = req.GetObject<BYTE>();
    }

    // Verify field position
    if (position > player.GetField().GetNumOfMinions())
    {
        return TaskStatus::PLAY_MINION_POSITION_OUT_OF_RANGE;
    }

    // Verify character casting
    const auto character = dynamic_cast<Character*>(m_source);
    if (character == nullptr)
    {
        return TaskStatus::PLAY_MINION_CANNOT_CONVERT_ENTITY;
    }

    // Summon minion
    character->Summon(position);

    // Apply card mechanics tags
    for (const auto tags : m_source->card.mechanics)
    {
        m_source->SetGameTag(tags, 1);
    }

    const auto cost = static_cast<BYTE>(m_source->card.cost);
    const TaskStatus modified =
        ModifyManaTask(ManaOperator::SUB, ManaType::AVAILABLE, cost)
            .Run(player);

    // Process PowerTasks
    for (auto& power : m_source->card.power.GetPowerTask())
    {
        power->Run(player);
    }

    if (modified == TaskStatus::MODIFY_MANA_SUCCESS)
    {
        return TaskStatus::PLAY_MINION_SUCCESS;
    }

    return TaskStatus::PLAY_MINION_MODIFY_MANA_FAIL;
}
}  // namespace Hearthstonepp::PlayerTasks