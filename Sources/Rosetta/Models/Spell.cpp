// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/Spell.hpp>

#include <utility>

namespace RosettaStone
{
Spell::Spell(Player& _owner, Card* _card, std::map<GameTag, int> tags)
    : Entity(_owner, _card, std::move(tags))
{
    // Do nothing
}

bool Spell::IsSecret() const
{
    return GetGameTag(GameTag::SECRET) == 1;
}

bool Spell::IsCountered() const
{
    return GetGameTag(GameTag::CANT_PLAY) == 1;
}
}  // namespace RosettaStone
