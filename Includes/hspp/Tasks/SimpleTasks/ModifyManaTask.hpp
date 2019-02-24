// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_MODIFY_MANA_TASK_HPP
#define HEARTHSTONEPP_MODIFY_MANA_TASK_HPP

#include <hspp/Tasks/Tasks.hpp>

namespace Hearthstonepp
{
//! The operator to change mana.
enum class ManaOperator
{
    ADD = 0,  //!< Add mana.
    SUB = 1,  //!< Subtract mana.
    SET = 2,  //!< Set mana.
};

//! The type to change mana.
enum class ManaType
{
    AVAILABLE = 0,  //!< Available mana.
    MAXIMUM = 1,    //!< Maximum mana.
};

namespace SimpleTasks
{
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
    //! \param num A value indicating how much to modify mana.
    ModifyManaTask(ManaOperator numMode, ManaType manaMode, std::size_t num);

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
    std::size_t m_num;
};
}  // namespace SimpleTasks
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_MODIFY_MANA_TASK_HPP
