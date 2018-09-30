// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_MODIFY_MANA_TASK_H
#define HEARTHSTONEPP_MODIFY_MANA_TASK_H

#include <hspp/Tasks/Tasks.h>

namespace Hearthstonepp
{
//! Num mode to change mana.
// TODO: We'll refactor later.
enum class NumMode
{
    ADD = 0,  //!< Add mana.
    SUB = 1,  //!< Subtract mana.
    SET = 2,  //!< Set mana.
};

//! Mana mode to change mana.
// TODO: We'll refactor later.
enum class ManaMode
{
    TOTAL = 0,  //!< Total mana.
    EXIST = 1,  //!< Temporary mana.
};

namespace BasicTasks
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
    ModifyManaTask(NumMode numMode, ManaMode manaMode, BYTE num);

    //! Returns task ID.
    //! \return Task ID.
    TaskID GetTaskID() const override;

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player1 The first player.
    //! \param player2 The second player.
    //! \return The result of task processing.
    MetaData Impl(Player& player1, Player& player2) override;

    NumMode m_numMode;
    ManaMode m_manaMode;
    BYTE m_num;
};
};  // namespace BasicTasks
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_MODIFYMANA_H
