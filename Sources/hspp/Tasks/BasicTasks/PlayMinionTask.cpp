// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/ModifyManaTask.h>
#include <hspp/Tasks/BasicTasks/PlayMinionTask.h>

namespace Hearthstonepp::BasicTasks
{
PlayMinionTask::PlayMinionTask(TaskAgent& agent, Entity* entity)
    : m_entity(entity), m_requirement(TaskID::SELECT_POSITION, agent)
{
    // Do nothing
}

TaskID PlayMinionTask::GetTaskID() const
{
    return TaskID::PLAY_MINION;
}

MetaData PlayMinionTask::Impl(Player& player)
{
    TaskMeta meta;

    // Get position response from GameInterface
    m_requirement.Interact(player.id, meta);

    using RequireTaskMeta = FlatData::ResponsePlayMinion;
    const auto& buffer = meta.GetBuffer();
    const auto req = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

    if (req == nullptr)
    {
        return MetaData::PLAY_MINION_FLATBUFFER_NULLPTR;
    }

    const BYTE position = req->position();

    // Verify field position
    if (position > player.field.size())
    {
        return MetaData::PLAY_MINION_POSITION_OUT_OF_RANGE;
    }

    // Verify character casting
    const auto character = dynamic_cast<Character*>(m_entity);
    if (character == nullptr)
    {
        return MetaData::PLAY_MINION_CANNOT_CONVERT_ENTITY;
    }

    // Summon minion
    if (player.field.empty())
    {
        player.field.emplace_back(character);
    }
    else
    {
        player.field.insert(player.field.begin() + position, character);
    } 

    // Apply card mechanics tags
    for (const auto tags : m_entity->card->mechanics)
    {
        m_entity->SetGameTag(tags, 1);
    }

    const auto cost = static_cast<BYTE>(m_entity->card->cost);
    const MetaData modified =
        ModifyManaTask(ManaOperator::SUB, ManaType::EXIST, cost).Run(player);

    // Process PowerTasks
    if (m_entity->card->power != nullptr)
    {
        for (auto& power : m_entity->card->power->powerTask)
        {
            power->Run(player);
        }
    }

    if (modified == MetaData::MODIFY_MANA_SUCCESS)
    {
        return MetaData::PLAY_MINION_SUCCESS;
    }

    return MetaData::PLAY_MINION_MODIFY_MANA_FAIL;
}
}  // namespace Hearthstonepp::BasicTasks