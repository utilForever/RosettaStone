#ifndef HEARTHSTONEPP_MODIFYMANA_H
#define HEARTHSTONEPP_MODIFYMANA_H

#include <Tasks/Tasks.h>

namespace Hearthstonepp
{
enum class NumMode
{
    ADD = 0,
    SUB = 1,
    SET = 2,
};

enum class ManaMode
{
    TOTAL = 0,
    EXIST = 1,
};

namespace BasicTasks
{
MetaData ImplModifyMana(Player &user, NumMode numMode, ManaMode manaMode,
                        BYTE num);

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
