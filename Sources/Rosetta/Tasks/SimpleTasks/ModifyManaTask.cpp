// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/ModifyManaTask.hpp>

#include <algorithm>

namespace RosettaStone::SimpleTasks
{
ModifyManaTask::ModifyManaTask(ManaOperator numMode, ManaType manaMode,
                               int amount)
    : m_numMode(numMode), m_manaMode(manaMode), m_amount(amount)
{
    // Do nothing
}

TaskID ModifyManaTask::GetTaskID() const
{
    return TaskID::MODIFY_MANA;
}

TaskStatus ModifyManaTask::Impl(Player& player)
{
    const auto getMana = [](Player& p, ManaType mode) -> int {
        if (mode == ManaType::AVAILABLE)
        {
            return p.currentMana;
        }

        if (mode == ManaType::MAXIMUM)
        {
            return p.maximumMana;
        }

        throw std::runtime_error("ModifyMana: Invalid mana mode");
    };

    int mana = getMana(player, m_manaMode);
    switch (m_numMode)
    {
        case ManaOperator::ADD:
            mana += m_amount;
            break;
        case ManaOperator::SUB:
            mana = (mana <= m_amount) ? 0 : (mana - m_amount);
            break;
        case ManaOperator::SET:
            mana = m_amount;
            break;
    }

    // Clamps a mana cost to a given range (min:0 ~ max:10)
    mana = std::clamp(mana, MANA_LOWER_LIMIT, MANA_UPPER_LIMIT);

    if (m_manaMode == ManaType::AVAILABLE)
    {
        player.currentMana = mana;
    }

    if (m_manaMode == ManaType::MAXIMUM)
    {
        player.maximumMana = mana;
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
