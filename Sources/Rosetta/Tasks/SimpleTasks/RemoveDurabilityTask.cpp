#include <Rosetta/Models/Weapon.hpp>
#include <Rosetta/Tasks/SimpleTasks/RemoveDurabilityTask.hpp>

namespace RosettaStone::SimpleTasks
{
RemoveDurabilityTask::RemoveDurabilityTask(int amount, bool isOpponent)
    : m_amount(amount), m_isOpponent(isOpponent)
{
    // Do nothing
}

TaskStatus RemoveDurabilityTask::Impl(Player* player)
{
    if (Weapon* weapon = m_isOpponent ? player->opponent->GetHero()->weapon
                                      : player->GetHero()->weapon;
        weapon != nullptr)
    {
        weapon->RemoveDurability(m_amount);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RemoveDurabilityTask::CloneImpl()
{
    return std::make_unique<RemoveDurabilityTask>(m_amount, m_isOpponent);
}
}  // namespace RosettaStone::SimpleTasks
