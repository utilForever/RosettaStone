// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Minion.hpp>

namespace Hearthstonepp
{
Minion::Minion(GameAgent* gameAgent, Card& card) : Character(gameAgent, card)
{
    CheckAbilities();
}

void Minion::SetGameTag(GameTag tag, int value)
{
    Character::SetGameTag(tag, value);

    CheckAbilities();
}

void Minion::CheckAbilities()
{
    if (m_gameTags[GameTag::CHARGE] == 1 && attackableCount == 0)
    {
        attackableCount = 1;
    }
    else if (m_gameTags[GameTag::WINDFURY] == 1 && attackableCount == 1)
    {
        attackableCount = 2;
    }
}
}  // namespace Hearthstonepp