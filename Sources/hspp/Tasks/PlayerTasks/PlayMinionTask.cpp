// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/PlayerTasks/PlayMinionTask.hpp>
#include <hspp/Tasks/SimpleTasks/ModifyManaTask.hpp>

using namespace Hearthstonepp::SimpleTasks;

namespace Hearthstonepp::PlayerTasks
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
        const auto fieldIter = std::find(player.GetField().begin(),
                                         player.GetField().end(), nullptr);
        position = static_cast<BYTE>(
            std::distance(player.GetField().begin(), fieldIter));
    }
    else
    {
        TaskMeta meta;

        // Get position response from GameInterface
        m_requirement.Interact(player.GetID(), meta);

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
    if (position > player.GetField().size())
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
    if (player.GetField().empty())
    {
        player.GetField().emplace_back(character);
        character->SetField(player.GetField());
    }
    else
    {
        player.GetField().insert(player.GetField().begin() + position,
                                 character);
        character->SetField(player.GetField());
    }

    // Apply card mechanics tags
    for (const auto tags : m_source->card->mechanics)
    {
        m_source->SetGameTag(tags, 1);
    }

    const auto cost = static_cast<BYTE>(m_source->card->cost);
    const MetaData modified =
        ModifyManaTask(ManaOperator::SUB, ManaType::AVAILABLE, cost)
            .Run(player);

    // Process PowerTasks
    if (m_source->card->power != nullptr)
    {
        for (auto& power : m_source->card->power->GetPowerTask())
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
}  // namespace Hearthstonepp::PlayerTasks