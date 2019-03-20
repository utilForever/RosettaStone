// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Choose.hpp>
#include <hspp/Tasks/PlayerTasks/ChooseTask.hpp>

namespace Hearthstonepp::PlayerTasks
{
ChooseTask::ChooseTask(std::vector<std::size_t> choices) : m_choices(choices)
{
    // Do nothing
}

ChooseTask ChooseTask::Mulligan(Player&, std::vector<std::size_t> choices)
{
    return ChooseTask(choices);
}

TaskID ChooseTask::GetTaskID() const
{
    return TaskID::CHOOSE;
}

TaskStatus ChooseTask::Impl(Player& player)
{
    switch (player.choice.value().choiceType)
    {
        case ChoiceType::MULLIGAN:
            Generic::ChoiceMulligan(player, m_choices);
            player.mulliganState = Mulligan::DONE;
            break;
        case ChoiceType::GENERAL:
            break;
        default:
            throw std::invalid_argument(
                "ChooseTask::Impl() - Invalid choice type!");
    }

    return TaskStatus::COMPLETE;
}
}  // namespace Hearthstonepp::PlayerTasks