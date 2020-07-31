// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_DAMAGE_HERO_TASK_HPP
#define ROSETTASTONE_BATTLEGROUNDS_DAMAGE_HERO_TASK_HPP

#include <Rosetta/Common/Enums/TaskEnums.hpp>

namespace RosettaStone::Battlegrounds
{
class Card;
class Minion;
class Player;

namespace SimpleTasks
{
//!
//! \brief DamageHeroTask class.
//!
//! This class represents the task for taking damage to the hero.
//!
class DamageHeroTask
{
 public:
    //! Constructs task with given \p damage.
    //! \param damage A value indicating how much to take.
    explicit DamageHeroTask(int damage);

    //! Runs task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \param source The source minion.
    //! \return The result of task processing.
    TaskStatus Run(Player& player, Minion& source);

    //! Runs task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \param source The source minion.
    //! \param target The target minion.
    //! \return The result of task processing.
    TaskStatus Run(Player& player, Minion& source, Minion& target);

 private:
    int m_damage = 0;
};
}  // namespace SimpleTasks
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_DAMAGE_HERO_TASK_HPP
