/*************************************************************************
> File Name: PlayMinion.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose:
> Created Time: 2018/07/21
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/BasicTasks/ModifyMana.h>
#include <Tasks/BasicTasks/PlayMinion.h>
#include <Tasks/PowerTask.h>

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

MetaData PlayMinionTask::Impl(Player& player1, Player& player2) const
{
    TaskMeta meta;
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

    auto character = dynamic_cast<Character*>(m_entity);
    if (character == nullptr)
    {
        return MetaData::PLAY_MINION_CANNOT_CONVERT_ENTITY;
    }

    player1.field.insert(player1.field.begin() + position, character);

    // Summoned minion can't attack right turn
    player1.attacked.emplace_back(character);

    BYTE cost = static_cast<BYTE>(m_entity->card->cost);
    MetaData modified = ModifyManaTask(NumMode::SUB, ManaMode::EXIST, cost)
                            .Run(player1, player2);

    for (auto& power : m_entity->card->power->powerTask)
    {
        PowerTask::ProcessPower(player1, player2, power);
    }

    if (modified == MetaData::MODIFY_MANA_SUCCESS)
    {
        return MetaData::PLAY_MINION_SUCCESS;
    }
    else
    {
        return MetaData::PLAY_MINION_MODIFY_MANA_FAIL;
    }
}
}  // namespace Hearthstonepp::BasicTasks