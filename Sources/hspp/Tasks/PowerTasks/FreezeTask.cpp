// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Tasks/PowerTasks/FreezeTask.h>

namespace Hearthstonepp::PowerTask
{
FreezeTask::FreezeTask(Character* target, TargetType type)
    : m_target(target), m_type(type)
{
    // Do nothing
}

TaskID FreezeTask::GetTaskID() const
{
    return TaskID::FREEZE;
}

MetaData FreezeTask::Impl(Player&, Player&)
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

    m_target->SetGameTag(GameTag::FROZEN, 1);

    // Case 1
    if (IsOpponentCharacter())
    {
        m_target->numTurnToUnfreeze = 2;
    }
    // Case 2
    else if (IsMyCharacter())
    {
        // Case 2-1
        if (IsFrozenBeforeAttack())
        {
            m_target->attackableCount = 0;
            m_target->numTurnToUnfreeze = 1;
        }
        // Case 2-2
        else if (IsFrozenAfterAttack())
        {
            m_target->numTurnToUnfreeze = 3;
        }
    }

    return MetaData::FREEZE_SUCCESS;
}

bool FreezeTask::IsMyCharacter() const
{
    return m_type == +TargetType::MY_FIELD || m_type == +TargetType::MY_HERO ||
           m_type == +TargetType::MY_MINION;
}

bool FreezeTask::IsOpponentCharacter() const
{
    return m_type == +TargetType::OPPONENT_FIELD ||
           m_type == +TargetType::OPPONENT_HERO ||
           m_type == +TargetType::OPPONENT_MINION;
}

bool FreezeTask::IsFrozenBeforeAttack() const
{
    if (m_target->attackableCount == 1)
    {
        return true;
    }

    if (m_target->GetGameTag(GameTag::WINDFURY) == 1 &&
        m_target->attackableCount == 2)
    {
        return true;
    }

    return false;
}

bool FreezeTask::IsFrozenAfterAttack() const
{
    if (m_target->attackableCount == 0)
    {
        return true;
    }

    if (m_target->GetGameTag(GameTag::WINDFURY) == 1 &&
        m_target->attackableCount == 1)
    {
        return true;
    }

    return false;
}
}  // namespace Hearthstonepp::PowerTask