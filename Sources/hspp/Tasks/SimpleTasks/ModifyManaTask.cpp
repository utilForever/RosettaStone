// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Tasks/SimpleTasks/ModifyManaTask.hpp>

#include <algorithm>

namespace Hearthstonepp::SimpleTasks
{
ModifyManaTask::ModifyManaTask(ManaOperator numMode, ManaType manaMode,
                               std::size_t num)
    : m_numMode(numMode), m_manaMode(manaMode), m_num(num)
{
    // Do nothing
}

TaskID ModifyManaTask::GetTaskID() const
{
    return TaskID::MODIFY_MANA;
}

TaskStatus ModifyManaTask::Impl(Player& player)
{
    const auto getMana = [](Player& p, ManaType mode) -> std::size_t {
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

    std::size_t mana = getMana(player, m_manaMode);
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
    mana = std::clamp(mana, static_cast<std::size_t>(0),
                      static_cast<std::size_t>(10));

    if (m_manaMode == ManaType::AVAILABLE)
    {
        player.currentMana = mana;
    }

    if (m_manaMode == ManaType::MAXIMUM)
    {
        player.maximumMana = mana;
    }

    return TaskStatus::MODIFY_MANA_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks