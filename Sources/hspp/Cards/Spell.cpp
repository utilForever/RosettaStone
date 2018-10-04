// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Spell.h>

namespace Hearthstonepp
{
Spell::Spell(const Spell& spell) : Entity(spell)
{
    // Do nothing
}

Spell* Spell::Clone() const
{
    return new Spell(*this);
}
}  // namespace Hearthstonepp