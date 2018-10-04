// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Hero.h>

namespace Hearthstonepp
{
Hero::Hero(const Card* pCard) : Character(pCard)
{
    // Do nothing
}

Hero::Hero(const Hero& hero) : Character(hero)
{
    delete weapon;

    if (hero.weapon != nullptr)
    {
        weapon = hero.weapon->Clone();        
    }
}

Hero* Hero::Clone() const
{
    return new Hero(*this);
}
}  // namespace Hearthstonepp