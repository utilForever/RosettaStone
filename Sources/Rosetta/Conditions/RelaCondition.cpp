// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Conditions/RelaCondition.hpp>
#include <Rosetta/Games/Game.hpp>

#include <utility>

namespace RosettaStone
{
RelaCondition::RelaCondition(std::function<bool(Entity*, Entity*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

RelaCondition RelaCondition::IsSideBySide()
{
    return RelaCondition([=](Entity* me, Entity* other) -> bool {
        return me->GetZoneType() == other->GetZoneType() &&
               std::abs(me->GetZonePosition() - other->GetZonePosition()) == 1;
    });
}

bool RelaCondition::Evaluate(Entity* owner, Entity* affected) const
{
    return m_func(owner, affected);
}
}  // namespace RosettaStone
