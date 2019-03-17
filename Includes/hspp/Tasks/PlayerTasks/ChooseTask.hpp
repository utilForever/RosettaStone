// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_CHOOSE_TASK_HPP
#define HEARTHSTONEPP_CHOOSE_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

#include <vector>

namespace Hearthstonepp::PlayerTasks
{
//!
//! \brief ChooseTask class.
//!
//! This class represents the task for choosing cards.
//!
class ChooseTask : public ITask
{
 public:
    //! Construct task with given \p choices.
    //! \param choices A container of card to choose.
    ChooseTask(std::vector<std::size_t> choices);

    //! ChooseTask wrapper for mulligan.
    //! \param player The player to run task.
    //! \param source A pointer to source entity to play card.
    //! \return Generated PlayCardTask for intended purpose.
    static ChooseTask Mulligan(Player& player, std::vector<std::size_t> choices);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    std::vector<std::size_t> m_choices;
};
}  // namespace Hearthstonepp::PlayerTasks

#endif  // HEARTHSTONEPP_CHOOSE_TASK_HPP
