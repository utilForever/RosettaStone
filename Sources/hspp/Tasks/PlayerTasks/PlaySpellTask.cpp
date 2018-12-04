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
    : ITask(source, target), m_requirement(TaskID::SELECT_TARGET, agent)
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

    // NOTE: 0 means my hero, 1 ~ 7 means my minion
    //       8 means opponent hero, 9 ~ 15 means opponent minion
    BYTE position;
    Character* target = nullptr;

    if (NeedTarget(power))
    {
        if (m_target != nullptr)
        {
            position = FindTargetPos(player);
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
        if (position >= 2 * FIELD_SIZE + 2)
        {
            return MetaData::PLAY_SPELL_POSITION_OUT_OF_RANGE;
        }

        if (position == 0)
        {
            target = player.GetHero();
        }
        else if (position >= 1 && position <= 7)
        {
            target = player.GetField()[position - 1];
        }
        else if (position == 8)
        {
            target = player.GetOpponent().GetHero();
        }
        else if (position >= 9 && position <= 15)
        {
            target = player.GetOpponent().GetField()[position - 9];
        }

        // Verify valid target
        if (target == nullptr)
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
        powerTask->SetTarget(target);
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

BYTE PlaySpellTask::FindTargetPos(Player& player) const
{
    if (m_target != nullptr)
    {
        Player& opponent = player.GetOpponent();

        if (m_target == player.GetHero())
        {
            return 0;
        }

        auto myField = player.GetField();
        const auto myFieldIter =
            std::find(myField.begin(), myField.end(), m_target);
        if (myFieldIter != myField.end())
        {
            return static_cast<BYTE>(
                std::distance(myField.begin(), myFieldIter) + 1);
        }

        if (m_target == player.GetHero())
        {
            return 8;
        }

        auto opponentField = opponent.GetField();
        const auto opponentFieldIter =
            std::find(opponentField.begin(), opponentField.end(), m_target);
        if (opponentFieldIter != opponentField.end())
        {
            return static_cast<BYTE>(
                std::distance(opponentField.begin(), opponentFieldIter) + 9);
        }
    }

    return 0;
}
}  // namespace Hearthstonepp::PlayerTasks