// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Actions/Generic.h>
#include <hspp/Cards/Minion.h>
#include <hspp/Cards/Weapon.h>

namespace Hearthstonepp
{
Entity* Generic::DrawCard(Player& player, Card&& card)
{
    Entity* entity;

    switch (card.cardType)
    {
        case +CardType::MINION:
            entity = new Minion(card);
            break;
        case +CardType::WEAPON:
            entity = new Weapon(card);
            break;
        default:
            entity = new Entity(card);
    }

    player.GetHand().emplace_back(entity);

    return entity;
}
}  // namespace Hearthstonepp