// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Battlegrounds/Conditions/SelfCondition.hpp>
#include <Rosetta/Battlegrounds/Models/Minion.hpp>

namespace RosettaStone::Battlegrounds
{
SelfCondition::SelfCondition(std::function<bool(Minion&)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

SelfCondition SelfCondition::IsRace(Race race)
{
    return SelfCondition(
        [race](Minion& minion) { return minion.GetRace() == race; });
}

bool SelfCondition::Evaluate(Minion& owner) const
{
    return m_func(owner);
}
}  // namespace RosettaStone::Battlegrounds
