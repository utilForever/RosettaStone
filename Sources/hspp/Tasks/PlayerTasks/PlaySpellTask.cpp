// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Commons/Constants.hpp>
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

        // Set target by position
        target = GetTargetByPos(player, position);

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

        if (m_target == opponent.GetHero())
        {
            return 8;
        }

        const auto minion = dynamic_cast<Minion*>(m_target);
        if (minion == nullptr)
        {
            return 0;
        }

        auto& myField = player.GetField();
        const auto myMinionPos = myField.FindMinionPos(*minion).value_or(
            std::numeric_limits<std::size_t>::max());
        if (myMinionPos != std::numeric_limits<std::size_t>::max())
        {
            return static_cast<BYTE>(myMinionPos + 1);
        }

        auto& opField = opponent.GetField();
        const auto opMinionPos = opField.FindMinionPos(*minion).value_or(
            std::numeric_limits<std::size_t>::max());
        if (opMinionPos != std::numeric_limits<std::size_t>::max())
        {
            return static_cast<BYTE>(opMinionPos + 9);
        }
    }

    return 0;
}

Character* PlaySpellTask::GetTargetByPos(Player& player, BYTE pos)
{
    if (pos == INDEX_MY_HERO)
    {
        return player.GetHero();
    }

    if (pos >= INDEX_MY_MINION && pos < INDEX_MY_MINION + FIELD_SIZE)
    {
        return player.GetField().GetMinion(pos - 1);
    }

    if (pos == INDEX_OPPONENT_HERO)
    {
        return player.GetOpponent().GetHero();
    }

    if (pos >= INDEX_OPPONENT_MINION &&
        pos < INDEX_OPPONENT_MINION + FIELD_SIZE)
    {
        return player.GetOpponent().GetField().GetMinion(pos - 9);
    }

    return nullptr;
}
}  // namespace Hearthstonepp::PlayerTasks