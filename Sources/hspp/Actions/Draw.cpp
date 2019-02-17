// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Draw.hpp>

namespace Hearthstonepp::Generic
{
Entity* Draw(Player& player, optional<Entity> card)
{
    (void)card;

    if (player.GetDeck().IsEmpty())
    {
        const std::size_t fatigueDamage =
            player.GetHero()->fatigue == 0 ? 1 : player.GetHero()->fatigue + 1;
        player.GetHero()->TakeDamage(*player.GetHero(), fatigueDamage);

        return nullptr;
    }

    Entity* entity = nullptr;

    // if (card.has_value())
    //{
    //    player.GetDeck().RemoveCard(card);
    //}
    // else
    //{
    //    player.GetDeck().RemoveCard(player.GetDeck().GetTopCard());
    //}

    player.GetHand().AddCard(*entity);

    return entity;
}

Entity* DrawCard(Player& player, Card card)
{
    Entity* entity = Entity::GetFromCard(player, card);
    player.GetHand().AddCard(*entity);

    return entity;
}
}  // namespace Hearthstonepp::Generic