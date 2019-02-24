// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Spell.hpp>

namespace Hearthstonepp
{
Spell::Spell(Player& _owner, Card& _card) : Entity(_owner, _card)
{
    // Do nothing
}

void Spell::Destroy()
{
    // Do nothing
}
}  // namespace Hearthstonepp