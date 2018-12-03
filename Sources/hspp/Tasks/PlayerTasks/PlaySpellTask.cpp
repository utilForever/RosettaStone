// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Enums/TaskEnums.hpp>
#include <hspp/Tasks/PlayerTasks/PlaySpellTask.hpp>
#include <hspp/Tasks/SimpleTasks/ModifyManaTask.hpp>

using namespace Hearthstonepp::SimpleTasks;

namespace Hearthstonepp::PlayerTasks
{
PlaySpellTask::PlaySpellTask(TaskAgent& agent, Entity* source, Entity* target)
    : m_source(source),
      m_requirement(TaskID::SELECT_TARGET, agent),
      m_target(target)
{
    // Do nothing
}

TaskID PlaySpellTask::GetTaskID() const
{
    return TaskID::PLAY_SPELL;
}

MetaData PlaySpellTask::Impl(Player& player)
{
    Power power = m_source->card->power;
    if (power.GetEnchant() == nullptr && power.GetPowerTask().empty())
    {
        return MetaData::PLAY_SPELL_NO_POWER;
    }

    BYTE position = 0;

    if (NeedTarget(power))
    {
        if (m_target != nullptr)
        {
            const auto fieldIter = std::find(player.GetField().begin(),
                                             player.GetField().end(), m_target);
            position = static_cast<BYTE>(
                std::distance(player.GetField().begin(), fieldIter));
        }
        else
        {
            TaskMeta meta;

            // Get position response from GameInterface
            m_requirement.Interact(player.GetID(), meta);

            using ResponsePlaySpell = FlatData::ResponsePlaySpell;
            const auto& buffer = meta.GetBuffer();
            const auto req =
                flatbuffers::GetRoot<ResponsePlaySpell>(buffer.get());

            if (req == nullptr)
            {
                return MetaData::PLAY_SPELL_FLATBUFFER_NULLPTR;
            }

            position = req->position();
        }

        // Verify field position
        if (position > player.GetField().size())
        {
            return MetaData::PLAY_SPELL_POSITION_OUT_OF_RANGE;
        }

        // Verify valid target
        if (player.GetField()[position] == nullptr)
        {
            return MetaData::PLAY_SPELL_INVALID_TARGET;
        }        
    }

    const auto cost = static_cast<BYTE>(m_source->card->cost);
    const MetaData modified =
        ModifyManaTask(ManaOperator::SUB, ManaType::AVAILABLE, cost)
            .Run(player);

    // Process PowerTasks
    for (auto& powerTask : m_source->card->power.GetPowerTask())
    {
        powerTask->SetTarget(player.GetField()[position]);
        powerTask->Run(player);
    }

    if (modified == MetaData::MODIFY_MANA_SUCCESS)
    {
        return MetaData::PLAY_SPELL_SUCCESS;
    }

    return MetaData::PLAY_SPELL_MODIFY_MANA_FAIL;
}

bool PlaySpellTask::NeedTarget(Power& power)
{
    for (auto& powerTask : power.GetPowerTask())
    {
        if (powerTask->GetEntityType() == +EntityType::SOURCE ||
            powerTask->GetEntityType() == +EntityType::TARGET)
        {
            return true;
        }
    }

    return false;
}
}  // namespace Hearthstonepp::PlayerTasks