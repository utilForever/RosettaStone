// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_FREEZE_TASK_HPP
#define HEARTHSTONEPP_FREEZE_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp::SimpleTasks
{
//!
//! \brief FreezeTask class.
//!
//! This class represents the task for freezing target.
//!
class FreezeTask : public ITask
{
 public:
    //! Constructs task with given \p entityType and \p target.
    //! \param entityType A entity type of the target.
    //! \param target A pointer to attacked character.
    FreezeTask(EntityType entityType, Character* target);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    MetaData Impl(Player& player) override;

    //! Finds out if this character is ours.
    //! \return true if this character is ours, and false otherwise.
    bool IsMyCharacter(Player& player) const;

    //! Finds out if this character is an opponent.
    //! \return true if this character is an opponent, and false otherwise.
    bool IsOpponentCharacter(Player& player) const;

    //! Finds out if this character gets Frozen before attacking.
    //! \return true if this character gets Frozen before attacking, and false
    //! otherwise.
    bool IsFrozenBeforeAttack() const;

    //! Finds out if this character gets Frozen after attacking.
    //! \return true if this character gets Frozen after attacking, and false
    //! otherwise.
    bool IsFrozenAfterAttack() const;
};
}  // namespace Hearthstonepp::SimpleTasks

#endif  // HEARTHSTONEPP_FREEZE_TASK_HPP
