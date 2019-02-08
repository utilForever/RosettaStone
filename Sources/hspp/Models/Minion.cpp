// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Minion.hpp>
#include <hspp/Models/Player.hpp>

namespace Hearthstonepp
{
Minion::Minion(Game* gameAgent, Card& card) : Character(gameAgent, card)
{
    CheckAbilities();
}

void Minion::Summon(std::size_t pos)
{
    GetOwner().GetField().AddMinion(*this, pos);
}

void Minion::Destroy()
{
    GetOwner().GetField().RemoveMinion(*this);
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