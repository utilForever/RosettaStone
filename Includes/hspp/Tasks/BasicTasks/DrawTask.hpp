// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_DRAW_TASK_HPP
#define HEARTHSTONEPP_DRAW_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief DrawTask class.
//!
//! This class represents the task for drawing card(s) from deck at random.
//!
class DrawTask : public ITask
{
 public:
    //! Constructs task with given \p agent and \p num.
    //! \param num The number of cards to draw.
    DrawTask(size_t num);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    size_t m_num = 0;
};

//!
//! \brief DrawCardTask class.
//!
//! This class represents the task for drawing specified card from deck.
//!
class DrawCardTask : public ITask
{
 public:
    //! Constructs task with given \p card.
    //! \param card A card to draw from deck (lvalue-ref).
    DrawCardTask(const Card& card);

    //! Constructs task with given \p card.
    //! \param card A card to draw from deck (rvalue-ref).
    DrawCardTask(Card&& card);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    Card m_card;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_DRAW_TASK_HPP
