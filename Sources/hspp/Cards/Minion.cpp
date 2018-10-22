// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Minion.h>

namespace Hearthstonepp
{
Minion::Minion(Card& card) : Character(card)
{
    // Do nothing
}

void Minion::SetAbility(GameTag tag, bool flag)
{
    Character::SetAbility(tag, flag);

    if (gameTags[GameTag::CHARGE] == 1)
    {
        attackableCount = 1;
    }
}
}  // namespace Hearthstonepp