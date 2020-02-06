// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/PlayerTasks/ChooseTask.hpp>

#include <utility>

namespace RosettaStone::PlayerTasks
{
ChooseTask::ChooseTask(std::vector<std::size_t> choices)
    : m_choices(std::move(choices))
{
    // Do nothing
}

ChooseTask ChooseTask::Mulligan(Player*, std::vector<std::size_t> choices)
{
    return ChooseTask(std::move(choices));
}

ChooseTask ChooseTask::Pick(Player*, std::size_t choice)
{
    return ChooseTask({ choice });
}

TaskStatus ChooseTask::Impl(Player* player)
{
    switch (player->choice.value().choiceType)
    {
        case ChoiceType::MULLIGAN:
        {
            Generic::ChoiceMulligan(player, m_choices);
            player->mulliganState = Mulligan::DONE;
            break;
        }
        case ChoiceType::GENERAL:
        {
            if (!Generic::ChoicePick(player, m_choices[0]))
            {
                return TaskStatus::STOP;
            }
            player->game->ProcessTasks();
            player->game->ProcessDestroyAndUpdateAura();
            break;
        }
        default:
            throw std::invalid_argument(
                "ChooseTask::Impl() - Invalid choice type!");
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> ChooseTask::CloneImpl()
{
    return std::make_unique<ChooseTask>(m_choices);
}
}  // namespace RosettaStone::PlayerTasks
