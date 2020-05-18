// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Conditions/RelaCondition.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
RelaCondition::RelaCondition(std::function<bool(Playable*, Playable*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

RelaCondition RelaCondition::IsFriendly()
{
    return RelaCondition([=](Playable* me, Playable* other) -> bool {
        return me->player == other->player;
    });
}

RelaCondition RelaCondition::IsSideBySide()
{
    return RelaCondition([=](Playable* me, Playable* other) -> bool {
        return me->GetZoneType() == other->GetZoneType() &&
               std::abs(me->GetZonePosition() - other->GetZonePosition()) == 1;
    });
}

bool RelaCondition::Evaluate(Playable* owner, Playable* affected) const
{
    return m_func(owner, affected);
}
}  // namespace RosettaStone::PlayMode
