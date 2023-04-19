// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

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
    return RelaCondition(
        [=](const Playable* self, const Playable* other) -> bool {
            return self->player == other->player;
        });
}

RelaCondition RelaCondition::IsSideBySide()
{
    return RelaCondition([=](const Playable* self,
                             const Playable* other) -> bool {
        return self->GetZoneType() == other->GetZoneType() &&
               std::abs(self->GetZonePosition() - other->GetZonePosition()) ==
                   1;
    });
}

bool RelaCondition::Evaluate(Playable* owner, Playable* affected) const
{
    return m_func(owner, affected);
}
}  // namespace RosettaStone::PlayMode
