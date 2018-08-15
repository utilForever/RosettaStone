/*************************************************************************
> File Name: PlayMinion.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Implement PlayMinion, Summon Minion and Process PowerTasks
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/ModifyManaTask.h>
#include <Tasks/BasicTasks/PlayMinionTask.h>

#include <algorithm>

namespace Hearthstonepp::BasicTasks
{
PlayMinionTask::PlayMinionTask(TaskAgent& agent, Entity* entity)
    : m_entity(entity), m_requirement(TaskID::SELECT_POSITION, agent)
{
    // Do Nothing
}

TaskID PlayMinionTask::GetTaskID() const
{
    return TaskID::PLAY_MINION;
}

MetaData PlayMinionTask::Impl(Player& player1, Player& player2)
{
    TaskMeta meta;
    // Get Position Response from GameInterface
    m_requirement.Interact(player1.id, meta);

    using RequireTaskMeta = FlatData::ResponsePlayMinion;
    const auto& buffer = meta.GetConstBuffer();
    auto req = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

    if (req == nullptr)
    {
        return MetaData::PLAY_MINION_FLATBUFFER_NULLPTR;
    }

    BYTE position = req->position();

    // Field Position Verification
    if (position > player1.field.size())
    {
        return MetaData::PLAY_MINION_POSITION_OUT_OF_RANGE;
    }

    // Character Casting Verification
    auto character = dynamic_cast<Character*>(m_entity);
    if (character == nullptr)
    {
        return MetaData::PLAY_MINION_CANNOT_CONVERT_ENTITY;
    }

    // Summon
    player1.field.insert(player1.field.begin() + position, character);

    // Summoned minion can't attack right turn
    auto cardMechanics = m_entity->card->mechanics;
    if (std::find(cardMechanics.begin(), cardMechanics.end(),
                  +GameTag::CHARGE) == m_entity->card->mechanics.end())
    {
        player1.attacked.emplace_back(character);
    }

    BYTE cost = static_cast<BYTE>(m_entity->card->cost);
    MetaData modified = ModifyManaTask(NumMode::SUB, ManaMode::EXIST, cost)
                            .Run(player1, player2);

    // Process PowerTasks
    if (m_entity->card->power != nullptr)
    {
        for (auto& power : m_entity->card->power->powerTask)
        {
            power->Run(player1, player2);
        }
    }

    if (modified == MetaData::MODIFY_MANA_SUCCESS)
    {
        return MetaData::PLAY_MINION_SUCCESS;
    }

    return MetaData::PLAY_MINION_MODIFY_MANA_FAIL;
}
}  // namespace Hearthstonepp::BasicTasks