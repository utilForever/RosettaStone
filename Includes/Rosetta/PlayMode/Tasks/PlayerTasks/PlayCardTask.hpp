// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_PLAY_CARD_TASK_HPP
#define ROSETTASTONE_PLAYMODE_PLAY_CARD_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::PlayerTasks
{
//!
//! \brief PlayCardTask class.
//!
//! This class represents the task for playing card from hand.
//! Then it runs each task according to the card type.
//!
class PlayCardTask : public ITask
{
 public:
    //! Constructs task with given \p source, \p fieldPos and \p target.
    //! \param source A pointer to source entity to play card.
    //! \param target A pointer to target entity to receive power.
    //! \param fieldPos A value indicating where to place card.
    //! \param chooseOne The index of chosen card from two cards.
    explicit PlayCardTask(Entity* source, Playable* target = nullptr,
                          int fieldPos = -1, int chooseOne = 0);

    //! PlayCardTask wrapper for minion without target and field position.
    //! \param source A pointer to source entity to play card.
    //! \param chooseOne The index of chosen card from two cards.
    //! \return Generated PlayCardTask for intended purpose.
    static PlayCardTask Minion(Entity* source, int chooseOne = 0);

    //! PlayCardTask wrapper for minion.
    //! \param source A pointer to source entity to play card.
    //! \param target A pointer to target entity to receive power.
    //! \param chooseOne The index of chosen card from two cards.
    //! \return Generated PlayCardTask for intended purpose.
    static PlayCardTask MinionTarget(Entity* source, Playable* target,
                                     int chooseOne = 0);

    //! PlayCardTask wrapper for spell without target.
    //! \param source A pointer to source entity to play card.
    //! \param chooseOne The index of chosen card from two cards.
    //! \return Generated PlayCardTask for intended purpose.
    static PlayCardTask Spell(Entity* source, int chooseOne = 0);

    //! PlayCardTask wrapper for spell.
    //! \param source A pointer to source entity to play card.
    //! \param target A pointer to target entity to receive power.
    //! \param chooseOne The index of chosen card from two cards.
    //! \return Generated PlayCardTask for intended purpose.
    static PlayCardTask SpellTarget(Entity* source, Playable* target,
                                    int chooseOne = 0);

    //! PlayCardTask wrapper for weapon without target.
    //! \param source A pointer to source entity to play card.
    //! \return Generated PlayCardTask for intended purpose.
    static PlayCardTask Weapon(Entity* source);

    //! PlayCardTask wrapper for weapon.
    //! \param source A pointer to source entity to play card.
    //! \param target A pointer to target entity to receive power.
    //! \return Generated PlayCardTask for intended purpose.
    static PlayCardTask WeaponTarget(Entity* source, Playable* target);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    int m_fieldPos = -1;
    int m_chooseOne = 0;
};
}  // namespace RosettaStone::PlayMode::PlayerTasks

#endif  // ROSETTASTONE_PLAYMODE_PLAY_CARD_TASK_HPP
