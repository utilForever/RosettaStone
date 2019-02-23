// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/FreezeTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
FreezeTask::FreezeTask(EntityType entityType, Character* target)
    : ITask(entityType, nullptr, target)
{
    // Do nothing
}

TaskID FreezeTask::GetTaskID() const
{
    return TaskID::FREEZE;
}

TaskStatus FreezeTask::Impl(Player& player)
{
    /*
     * The logic of Freeze
     *
     * 1. For enemy characters on your turn, the result is very simple:
     * if you Freeze an enemy character during your turn,
     * it will thaw at the start of your next turn.
     * 2. For friendly characters on your turn, it depends on
     * whether or not they have attacked that turn.
     * 2-1. If a friendly character gets Frozen before attacking,
     * they will thaw at the end of the turn. This includes characters
     * which were unable to attack, such as a 0 Attack minion or hero.
     * 2-2. If a friendly character gets Frozen after attacking, they
     * will thaw at the end of the next turn. This includes characters
     * with Windfury who have only attacked once this turn.
     *
     * Reference: https://hearthstone.gamepedia.com/Freeze
     */

    auto target = dynamic_cast<Character*>(m_target);

    target->SetGameTag(GameTag::FROZEN, 1);

    // Case 1
    if (IsOpCharacter(player))
    {
        target->numTurnToUnfreeze = 2;
    }
    // Case 2
    else if (IsMyCharacter(player))
    {
        // Case 2-1
        if (IsFrozenBeforeAttack())
        {
            target->attackableCount = 0;
            target->numTurnToUnfreeze = 1;
        }
        // Case 2-2
        else if (IsFrozenAfterAttack())
        {
            target->numTurnToUnfreeze = 3;
        }
    }

    return TaskStatus::FREEZE_SUCCESS;
}

bool FreezeTask::IsMyCharacter(Player& player) const
{
    if (m_entityType == +EntityType::SOURCE ||
        m_entityType == +EntityType::TARGET)
    {
        const auto hero = dynamic_cast<Hero*>(m_target);
        if (hero != nullptr && hero == player.GetHero())
        {
            return true;
        }

        const auto minion = dynamic_cast<Minion*>(m_target);
        const auto minionPos =
            player.GetField().FindMinionPos(*minion).value_or(
                std::numeric_limits<std::size_t>::max());
        return minion != nullptr &&
               minionPos != std::numeric_limits<std::size_t>::max();
    }

    return m_entityType == +EntityType::FIELD ||
           m_entityType == +EntityType::HERO ||
           m_entityType == +EntityType::FRIENDS;
}

bool FreezeTask::IsOpCharacter(Player& player) const
{
    if (m_entityType == +EntityType::SOURCE ||
        m_entityType == +EntityType::TARGET)
    {
        const auto hero = dynamic_cast<Hero*>(m_target);
        if (hero != nullptr && hero == player.GetOpponent().GetHero())
        {
            return true;
        }

        const auto minion = dynamic_cast<Minion*>(m_target);
        const auto minionPos =
            player.GetOpponent().GetField().FindMinionPos(*minion).value_or(
                std::numeric_limits<std::size_t>::max());
        return minion != nullptr &&
               minionPos != std::numeric_limits<std::size_t>::max();
    }

    return m_entityType == +EntityType::ENEMY_FIELD ||
           m_entityType == +EntityType::ENEMY_HERO ||
           m_entityType == +EntityType::ENEMIES;
}

bool FreezeTask::IsFrozenBeforeAttack() const
{
    const auto target = dynamic_cast<Character*>(m_target);

    if (target->attackableCount == 1)
    {
        return true;
    }

    if (target->GetGameTag(GameTag::WINDFURY) == 1 &&
        target->attackableCount == 2)
    {
        return true;
    }

    return false;
}

bool FreezeTask::IsFrozenAfterAttack() const
{
    const auto target = dynamic_cast<Character*>(m_target);

    if (target->attackableCount == 0)
    {
        return true;
    }

    if (target->GetGameTag(GameTag::WINDFURY) == 1 &&
        target->attackableCount == 1)
    {
        return true;
    }

    return false;
}
}  // namespace Hearthstonepp::SimpleTasks