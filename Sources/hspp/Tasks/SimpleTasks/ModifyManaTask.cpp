// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/ModifyManaTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
ModifyManaTask::ModifyManaTask(ManaOperator numMode, ManaType manaMode,
                               BYTE num)
    : m_numMode(numMode), m_manaMode(manaMode), m_num(num)
{
    // Do Nothing
}

TaskID ModifyManaTask::GetTaskID() const
{
    return TaskID::MODIFY_MANA;
}

MetaData ModifyManaTask::Impl(Player& player)
{
    const auto getMana = [](Player& p, ManaType mode) -> BYTE {
        if (mode == ManaType::AVAILABLE)
        {
            return p.GetAvailableMana();
        }

        if (mode == ManaType::MAXIMUM)
        {
            return p.GetMaximumMana();
        }

        throw std::runtime_error("ModifyMana: Invalid mana mode");
    };

    BYTE mana = getMana(player, m_manaMode);
    switch (m_numMode)
    {
        case ManaOperator::ADD:
            mana += m_num;
            break;
        case ManaOperator::SUB:
            mana = (mana <= m_num) ? 0 : (mana - m_num);
            break;
        case ManaOperator::SET:
            mana = m_num;
            break;
    }

    // Clamps a mana cost to a given range (min:0 ~ max:10)
    mana = std::clamp(mana, static_cast<BYTE>(0), static_cast<BYTE>(10));

    if (m_manaMode == ManaType::AVAILABLE)
    {
        player.SetAvailableMana(mana);
    }

    if (m_manaMode == ManaType::MAXIMUM)
    {
        player.SetMaximumMana(mana);
    }

    return MetaData::MODIFY_MANA_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks