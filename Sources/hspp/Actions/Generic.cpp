// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Actions/Generic.hpp>
#include <hspp/Cards/Minion.hpp>
#include <hspp/Cards/Weapon.hpp>

namespace Hearthstonepp
{
Entity* Generic::DrawCard(Player& player, Card&& card)
{
    auto* pGameAgent = &(player.GetGameAgent());
    Entity* entity;

    switch (card.cardType)
    {
        case +CardType::MINION:
            entity = new Minion(pGameAgent, card);
            break;
        case +CardType::WEAPON:
            entity = new Weapon(pGameAgent, card);
            break;
        default:
            entity = new Entity(pGameAgent, card);
    }

    player.GetHand().emplace_back(entity);

    return entity;
}
}  // namespace Hearthstonepp