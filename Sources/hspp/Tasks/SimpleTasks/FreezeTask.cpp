// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

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

MetaData FreezeTask::Impl(Player& player)
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
    if (IsOpponentCharacter(player))
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

    return MetaData::FREEZE_SUCCESS;
}

bool FreezeTask::IsMyCharacter(Player& player) const
{
    if (m_entityType == +EntityType::SOURCE ||
        m_entityType == +EntityType::TARGET)
    {
        return std::find(player.GetField().begin(), player.GetField().end(),
                         m_target) != player.GetField().end();
    }

    return m_entityType == +EntityType::FIELD ||
           m_entityType == +EntityType::HERO ||
           m_entityType == +EntityType::FRIENDS;
}

bool FreezeTask::IsOpponentCharacter(Player& player) const
{
    if (m_entityType == +EntityType::SOURCE ||
        m_entityType == +EntityType::TARGET)
    {
        return std::find(player.GetOpponent().GetField().begin(),
                         player.GetOpponent().GetField().end(),
                         m_target) != player.GetOpponent().GetField().end();
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