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
    TaskMeta serialized;

    using RequireTaskMeta = FlatData::ResponsePlayMinion;
    const auto& buffer = serialized.GetConstBuffer();
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

    if (player1.field[position] != nullptr)
    {
        return MetaData::PLAY_MINION_POSITION_OUT_OF_RANGE;
    }

    // summon minion at field
    player1.field[position] = dynamic_cast<Character*>(m_entity);

    int cost = static_cast<int>(m_entity->card->cost);

    // Summoned minion can't attack right turn
    Character* character = dynamic_cast<Character*>(m_entity);
    player1.attacked.emplace_back(character);
    MetaData modified =
        ModifyManaTask(NumMode::SUB, ManaMode::EXIST, static_cast<BYTE>(cost))
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