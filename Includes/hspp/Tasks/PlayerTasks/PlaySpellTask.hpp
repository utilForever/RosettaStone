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
    //! Constructs task with given \p source and \p target.
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
    TaskStatus Impl(Player& player) override;

    //! Checks that spell card needs target.
    //! \param power A reference to power of the card.
    //! \return true if spell card needs target, and false otherwise.
    static bool NeedTarget(Power& power);

    //! Finds the position of target.
    //! \param player The player to find target.
    //! \return The position of target.
    std::size_t FindTargetPos(Player& player) const;

    //! Returns target at given position.
    //! \param player The player to get target.
    //! \param pos The position of target.
    //! \return Target at given position.
    static Character* GetTargetByPos(Player& player, std::size_t pos);
};
}  // namespace Hearthstonepp::PlayerTasks

#endif  // HEARTHSTONEPP_PLAY_SPELL_TASK_HPP
