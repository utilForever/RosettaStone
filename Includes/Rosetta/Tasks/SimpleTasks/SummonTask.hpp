// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SUMMON_TASK_HPP
#define ROSETTASTONE_SUMMON_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//! The side of summoned minion.
enum class SummonSide
{
    DEFAULT,      //!< Summoning on the last position on the right side.
    LEFT,         //!< Summoning left of the minion.
    RIGHT,        //!< Summoning right of the minion.
    DEATHRATTLE,  //!< Summoning at the last position of the source.
    NUMBER,       //!< Summoning at a given position in the stack number.
    SPELL,        //!< Summoning by spell, currently like default.
    TARGET,       //!< Summoning right of the target.
};

//!
//! \brief SummonTask class.
//!
//! This class represents the task for summoning minion at battlefield.
//!
class SummonTask : public ITask
{
 public:
    //! Constructs task with given \p side, \p card,
    //! \p removeFromStack, \p addToStack and \p amount.
    //! \param side The side of summoned minion.
    //! \param card The card to summon.
    //! \param removeFromStack The flag that indicates
    //! whether the summon entity should remove from stack.
    //! \param addToStack The flag that indicates
    //! whether the summon entity should add to stack.
    //! \param amount The number of minions to summon.
    explicit SummonTask(SummonSide side = SummonSide::DEFAULT,
                        std::optional<Card*> card = std::nullopt,
                        bool removeFromStack = false, bool addToStack = false, int amount = 1);

    //! Constructs task with given \p cardID, \p side and \p addToStack.
    //! \param cardID The card ID to summon.
    //! \param side The side of summoned minion.
    //! \param addToStack The flag that indicates
    //! whether the summon entity should add to stack.
    explicit SummonTask(const std::string& cardID,
                        SummonSide side = SummonSide::DEFAULT,
                        bool addToStack = false);

    //! Constructs task with given \p cardID, \p amount and \p side.
    //! \param cardID The card ID to summon.
    //! \param amount The number of minions to summon.
    //! \param side The side of summoned minion.
    explicit SummonTask(const std::string& cardID, int amount,
                        SummonSide side = SummonSide::DEFAULT);

    //! Returns the position of minion to summon.
    //! \param source The source entity.
    //! \param side The side of summoned minion.
    //! \return The position of minion to summon.
    static int GetPosition(Entity* source, SummonSide side);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    std::optional<Card*> m_card = std::nullopt;
    SummonSide m_side = SummonSide::DEFAULT;
    int m_amount = 1;
    bool m_removeFromStack = false;
    bool m_addToStack = false;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_SUMMON_TASK_HPP
