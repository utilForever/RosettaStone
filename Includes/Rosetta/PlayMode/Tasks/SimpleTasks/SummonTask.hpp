// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_SUMMON_TASK_HPP
#define ROSETTASTONE_PLAYMODE_SUMMON_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
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
    //! \param addToStack The flag that indicates
    //! whether the summon entity should add to stack.
    explicit SummonTask(const std::string& cardID, int amount,
                        SummonSide side = SummonSide::DEFAULT,
                        bool addToStack = false);

    //! Returns the position of minion to summon.
    //! \param source The source entity.
    //! \param side The side of summoned minion.
    //! \param target The target entity.
    //! \param alternateCount The count for SummonSide::ALTERNATE.
    //! \return The position of minion to summon.
    static int GetPosition(Entity* source, SummonSide side, Entity* target,
                           int& alternateCount);

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
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_SUMMON_TASK_HPP
