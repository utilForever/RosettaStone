// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_PLAY_CARD_TASK_H
#define HEARTHSTONEPP_PLAY_CARD_TASK_H

#include <hspp/Tasks/Requirement.h>
#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp::BasicTasks
{
//!
//! \brief PlayCardTask class.
//!
//! This class represents the task for playing card from hand.
//! Then it runs each task according to the card type.
//!
class PlayCardTask : public ITask
{
 public:
    //! Constructs task with given \p agent.
    //! \param agent The task agent that performs card play.
    //! \param source A pointer to source entity to play card.
    //! \param fieldPos A value indicating where to place card.
    //! \param target A target of the card to receive power.
    PlayCardTask(TaskAgent& agent, Entity* source = nullptr, int fieldPos = -1,
                 Entity* target = nullptr);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    TaskAgent& m_agent;
    Requirement m_requirement;
    Entity* m_source = nullptr;
    int m_fieldPos = -1;
    Entity* m_target = nullptr;
};
}  // namespace Hearthstonepp::BasicTasks

#endif  // HEARTHSTONEPP_PLAY_CARD_TASK_H
