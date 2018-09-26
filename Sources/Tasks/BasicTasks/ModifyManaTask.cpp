#include <Tasks/BasicTasks/ModifyManaTask.h>

namespace Hearthstonepp::BasicTasks
{
ModifyManaTask::ModifyManaTask(NumMode numMode, ManaMode manaMode, BYTE num)
    : m_numMode(numMode), m_manaMode(manaMode), m_num(num)
{
    // Do Nothing
}

TaskID ModifyManaTask::GetTaskID() const
{
    return TaskID::MODIFY_MANA;
}

MetaData ModifyManaTask::Impl(Player& player1, Player&)
{
    auto get = [](Player& user, ManaMode mode) -> BYTE& {
        if (mode == ManaMode::EXIST)
            return user.existMana;
        if (mode == ManaMode::TOTAL)
            return user.totalMana;

        throw std::runtime_error("ImplModifyMana : Invalid ManaMode");
    };

    BYTE& mana = get(player1, m_manaMode);
    switch (m_numMode)
    {
        case NumMode::ADD:
            mana += m_num;
            break;
        case NumMode::SUB:
            mana = (mana <= m_num) ? 0 : (mana - m_num);
            break;
        case NumMode::SET:
            mana = m_num;
            break;
    }

    // Clamps a mana cost to a given range (min:0 ~ max:10)
    mana = std::clamp(mana, static_cast<BYTE>(0), static_cast<BYTE>(10));

    return MetaData::MODIFY_MANA_SUCCESS;
}
}  // namespace Hearthstonepp::BasicTasks