// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Enums/TaskEnums.h>
#include <hspp/Tasks/BasicTasks/ModifyManaTask.h>
#include <hspp/Tasks/BasicTasks/PlaySpellTask.h>

namespace Hearthstonepp::BasicTasks
{
PlaySpellTask::PlaySpellTask(TaskAgent& agent, Entity* entity)
    : m_entity(entity), m_requirement(TaskID::SELECT_TARGET, agent)
{
    // Do nothing
}

TaskID PlaySpellTask::GetTaskID() const
{
    return TaskID::PLAY_SPELL;
}

MetaData PlaySpellTask::Impl(Player& player)
{
    TaskMeta meta;

    // Get position response from GameInterface
    m_requirement.Interact(player.id, meta);

    using ResponsePlaySpell = FlatData::ResponsePlaySpell;
    const auto& buffer = meta.GetBuffer();
    const auto req = flatbuffers::GetRoot<ResponsePlaySpell>(buffer.get());

    if (req == nullptr)
    {
        return MetaData::PLAY_SPELL_FLATBUFFER_NULLPTR;
    }

    const EntityType type = EntityType::_from_integral(req->targetType());
    const BYTE position = req->position();

    if (type == +EntityType::FIELD)
    {
        // Verify field position
        if (position > player.field.size())
        {
            return MetaData::PLAY_SPELL_POSITION_OUT_OF_RANGE;
        }

        // Verify valid target
        if (player.field[position] == nullptr)
        {
            return MetaData::PLAY_SPELL_INVALID_TARGET;
        }
    }

    const BYTE cost = static_cast<BYTE>(m_entity->card->cost);
    const MetaData modified =
        ModifyManaTask(ManaOperator::SUB, ManaType::EXIST, cost).Run(player);

    // Process PowerTasks
    if (m_entity->card->power != nullptr)
    {
        for (auto& power : m_entity->card->power->powerTask)
        {
            power->target = player.field[position];
            power->Run(player);
        }
    }

    if (modified == MetaData::MODIFY_MANA_SUCCESS)
    {
        return MetaData::PLAY_SPELL_SUCCESS;
    }

    return MetaData::PLAY_SPELL_MODIFY_MANA_FAIL;
}
}  // namespace Hearthstonepp::BasicTasks