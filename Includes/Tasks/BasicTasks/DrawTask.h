#ifndef HEARTHSTONEPP_DRAW_H
#define HEARTHSTONEPP_DRAW_H

#include <Tasks/TaskAgent.h>
#include <Tasks/Tasks.h>

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
    //! Constructs task with given \p num and \p agent.
    //! \param num The number of cards to draw.
    //! \param agent The task agent that notifies overdrawn cards.
    DrawTask(size_t num, TaskAgent& agent);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    TaskAgent& m_agent;
    size_t m_num;
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
    //! \param card A pointer to card to draw from deck.
    DrawCardTask(const Card* card);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    Entity* m_entity;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_DRAW_H
