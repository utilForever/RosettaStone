// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/BasicTasks/ModifyManaTask.h>
#include <hspp/Tasks/BasicTasks/PlayMinionTask.h>

namespace Hearthstonepp::BasicTasks
{
PlayMinionTask::PlayMinionTask(TaskAgent& agent, Entity* source, int fieldPos,
                               Entity* target)
    : ITask(source, target),
      m_requirement(TaskID::SELECT_POSITION, agent),
      m_fieldPos(fieldPos)
{
    // Do nothing
}

TaskID PlayMinionTask::GetTaskID() const
{
    return TaskID::PLAY_MINION;
}

MetaData PlayMinionTask::Impl(Player& player)
{
    BYTE position;

    if (m_fieldPos == -1)
    {
        const auto fieldIter =
            std::find(player.field.begin(), player.field.end(), nullptr);
        position =
            static_cast<BYTE>(std::distance(player.field.begin(), fieldIter));
    }
    else
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

        position = req->position();
    }

    // Verify field position
    if (position > player.field.size())
    {
        return MetaData::PLAY_MINION_POSITION_OUT_OF_RANGE;
    }

    // Verify character casting
    const auto character = dynamic_cast<Character*>(m_source);
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
    for (const auto tags : m_source->card->mechanics)
    {
        m_source->SetGameTag(tags, 1);
    }

    const auto cost = static_cast<BYTE>(m_source->card->cost);
    const MetaData modified =
        ModifyManaTask(ManaOperator::SUB, ManaType::EXIST, cost).Run(player);

    // Process PowerTasks
    if (m_source->card->power != nullptr)
    {
        for (auto& power : m_source->card->power->powerTask)
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