// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_SELF_CONDITION_HPP
#define ROSETTASTONE_SELF_CONDITION_HPP

#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Enums/GameEnums.hpp>

#include <functional>

namespace RosettaStone
{
class Entity;

//!
//! \brief SelfCondition class.
//!
//! This class is a container for all conditions about the subject entity.
//!
class SelfCondition
{
 public:
    //! Constructs task with given \p func.
    //! \param func The function to check condition.
    explicit SelfCondition(std::function<bool(Entity*)> func);

    //! SelfCondition wrapper for checking an entity is destroyed.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsDead();

    //! SelfCondition wrapper for checking an entity is undamaged.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsUndamaged();

    //! SelfCondition wrapper for checking an hero equips weapon.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsWeaponEquipped();

    //! SelfCondition wrapper for checking race of entity is \p race.
    //! \param race The race for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsRace(Race race);

    //! SelfCondition wrapper for checking there is an entity with a \p race in
    //! field zone.
    //! \param race The race for checking.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsControllingRace(Race race);

    //! SelfCondition wrapper for checking an entity is minion.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsMinion();

    //! SelfCondition wrapper for checking there is an entity that satisfies
    //! condition with \p tag, \p value and \p relaSign.
    //! \param tag A game tag to check condition.
    //! \param value A value to check condition.
    //! \param relaSign A comparer to check condition.
    //! \return Generated SelfCondition for intended purpose.
    static SelfCondition IsTagValue(GameTag tag, int value,
                                    RelaSign relaSign = RelaSign::EQ);

    //! Evaluates condition using checking function.
    //! \param entity An owner entity.
    //! \return true if the condition is satisfied, false otherwise.
    bool Evaluate(Entity* entity) const;

 private:
    std::function<bool(Entity*)> m_func;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SELF_CONDITION_HPP
