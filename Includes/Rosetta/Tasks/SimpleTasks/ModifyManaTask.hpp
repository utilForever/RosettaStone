// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_MODIFY_MANA_TASK_HPP
#define ROSETTASTONE_MODIFY_MANA_TASK_HPP

#include <Rosetta/Tasks/Tasks.hpp>

namespace RosettaStone::SimpleTasks
{
//! The operator to change mana.
enum class ManaOperator
{
    ADD,  //!< Add mana.
    SUB,  //!< Subtract mana.
    SET   //!< Set mana.
};

//! The type to change mana.
enum class ManaType
{
    AVAILABLE,  //!< Available mana.
    MAXIMUM     //!< Maximum mana.
};

//!
//! \brief ModifyManaTask class.
//!
//! This class represents the task for modifying mana of player.
//!
class ModifyManaTask : public ITask
{
 public:
    //! Constructs task with given \p numMode, \p manaMode and \p num.
    //! \param numMode A value that specifies the operation of \p num.
    //! \param manaMode A value that specifies whether the modified mana is
    //! one-time or permanent.
    //! \param amount A value indicating how much to modify mana.
    ModifyManaTask(ManaOperator numMode, ManaType manaMode, int amount);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player& player) override;

    ManaOperator m_numMode;
    ManaType m_manaMode;
    int m_amount;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_MODIFY_MANA_TASK_HPP
