// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Generic.hpp>
#include <hspp/Models/Minion.hpp>
#include <hspp/Models/Weapon.hpp>

namespace Hearthstonepp
{
Entity* Generic::DrawCard(Player& player, Card&& card)
{
    auto* game = player.GetGame();
    Entity* entity;

    switch (card.cardType)
    {
        case +CardType::MINION:
            entity = new Minion(game, card);
            break;
        case +CardType::SPELL:
            entity = new Spell(game, card);
            break;
        case +CardType::WEAPON:
            entity = new Weapon(game, card);
            break;
        default:
            throw std::invalid_argument(
                "Generic::DrawCard() - Invalid card type!");
    }

    player.GetHand().AddCard(*entity);

    return entity;
}
}  // namespace Hearthstonepp