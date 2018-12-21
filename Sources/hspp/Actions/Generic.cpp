// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

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