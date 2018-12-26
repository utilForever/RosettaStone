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
    auto* gameAgent = player.GetGameAgent();
    Entity* entity;

    switch (card.cardType)
    {
        case +CardType::MINION:
            entity = new Minion(gameAgent, card);
            break;
        case +CardType::WEAPON:
            entity = new Weapon(gameAgent, card);
            break;
        default:
            entity = new Entity(gameAgent, card);
    }

    player.GetHand().emplace_back(entity);

    return entity;
}
}  // namespace Hearthstonepp