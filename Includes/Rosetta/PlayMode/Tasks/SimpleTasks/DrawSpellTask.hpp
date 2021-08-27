// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DRAW_SPELL_TASK_HPP
#define ROSETTASTONE_PLAYMODE_DRAW_SPELL_TASK_HPP

#include <Rosetta/Common/Enums/GameEnums.hpp>
#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief DrawSpellTask class.
//!
//! This class represents the task for drawing spell card(s) from the deck.
//!
class DrawSpellTask : public ITask
{
 public:
    //! Constructs task with given \p amount, \p spellSchool and \p addToStack.
    //! \param amount The amount to draw minion card(s).
    //! \param spellSchool The stated school of the spell.
    //! \param addToStack A flag to store card to stack.
    explicit DrawSpellTask(int amount,
                           SpellSchool spellSchool = SpellSchool::NONE,
                           bool addToStack = false);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_amount = 0;
    SpellSchool m_spellSchool = SpellSchool::NONE;
    bool m_addToStack = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_DRAW_SPELL_TASK_HPP
