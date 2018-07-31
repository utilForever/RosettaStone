/*************************************************************************
> File Name: PlaySpell.cpp
> Project Name: Hearthstonepp
> Author: Chan-Ho Chris Ohk
> Purpose: Implement PlaySpell, cast spells
> Created Time: 2018/07/31
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Tasks/BasicTasks/ModifyMana.h>
#include <Tasks/BasicTasks/PlaySpell.h>
#include <Tasks/PowerTask.h>

#include <algorithm>

namespace Hearthstonepp::BasicTasks
{
PlaySpellTask::PlaySpellTask(Entity* entity)
    : m_entity(entity)
{
    // Do Nothing
}

TaskID PlaySpellTask::GetTaskID() const
{
    return TaskID::PLAY_SPELL;
}

MetaData PlaySpellTask::Impl(Player& player1, Player& player2) const
{
    TaskMeta meta;

    using RequireTaskMeta = FlatData::ResponsePlaySpell;
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
    if (std::find(m_entity->card->mechanics.begin(),
                  m_entity->card->mechanics.end(),
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
            PowerTask::ProcessPower(player1, player2, power);
        }
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