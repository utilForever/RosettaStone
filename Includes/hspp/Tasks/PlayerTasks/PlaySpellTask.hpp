// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_PLAY_SPELL_TASK_HPP
#define HEARTHSTONEPP_PLAY_SPELL_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::PlayerTasks
{
//!
//! \brief PlaySpellTask class.
//!
//! This class represents the task for playing spell.
//! It specifies target and casts spell to given target.
//!
class PlaySpellTask : public ITask
{
 public:
    //! Constructs task with given \p agent and \p entity.
    //! \param agent The task agent that interacts with game interface.
    //! \param source A pointer to source entity to play card.
    //! \param target A target of the card to receive power.
    PlaySpellTask(Entity* source, Entity* target);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    Entity* m_source = nullptr;
    Entity* m_target = nullptr;
};
}  // namespace Hearthstonepp::PlayerTasks

#endif  // HEARTHSTONEPP_PLAY_SPELL_TASK_HPP
