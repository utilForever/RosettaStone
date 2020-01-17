// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_REPLACE_HERO_TASK_HPP
#define ROSETTASTONE_REPLACE_HERO_TASK_HPP

#include <Rosetta/Tasks/ITask.hpp>

namespace RosettaStone::SimpleTasks
{
//!
//! \brief ReplaceHeroTask class.
//!
//! This class represents the task for replacing the hero.
//!
class ReplaceHeroTask : public ITask
{
 public:
    //! Constructs task with given \p heroCard, \p heroPowerCard
    //! and \p weaponCard.
    //! \param heroCard The hero card to replace.
    //! \param heroPowerCard The hero power card to replace.
    //! \param weaponCard The weapon card to equip.
    explicit ReplaceHeroTask(const std::string_view& heroCard,
                             const std::string_view& heroPowerCard,
                             const std::string_view& weaponCard = "");

    //! Constructs task with given \p heroCard, \p heroPowerCard
    //! and \p weaponCard.
    //! \param heroCard The hero card to replace.
    //! \param heroPowerCard The hero power card to replace.
    //! \param weaponCard The weapon card to equip.
    explicit ReplaceHeroTask(Card* heroCard, Card* heroPowerCard,
                             Card* weaponCard);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    Card* m_heroCard = nullptr;
    Card* m_heroPowerCard = nullptr;
    Card* m_weaponCard = nullptr;
};
}  // namespace RosettaStone::SimpleTasks

#endif  // ROSETTASTONE_REPLACE_HERO_TASK_HPP
