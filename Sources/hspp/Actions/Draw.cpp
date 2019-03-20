// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Draw.hpp>
#include <hspp/Actions/Generic.hpp>
#include <hspp/Models/Player.hpp>

namespace Hearthstonepp::Generic
{
Entity* Draw(Player& player, std::optional<Entity> card)
{
    // Take fatigue damage for player if deck is empty
    if (player.GetDeck().IsEmpty())
    {
        const std::size_t fatigueDamage =
            player.GetHero()->fatigue == 0 ? 1 : player.GetHero()->fatigue + 1;
        player.GetHero()->TakeDamage(*player.GetHero(), fatigueDamage);

        return nullptr;
    }

    Entity* entity;

    // Get card to draw
    if (card.has_value())
    {
        entity = &player.GetDeck().RemoveCard(card.value());
    }
    else
    {
        Entity* topCard = player.GetDeck().GetTopCard();
        if (topCard == nullptr)
        {
            return nullptr;
        }

        entity = &player.GetDeck().RemoveCard(*topCard);
    }

    // Add card to hand
	AddCardToHand(player, entity);

    return entity;
}

Entity* DrawCard(Player& player, Card&& card)
{
    Entity* entity = Entity::GetFromCard(player, std::move(card));
    AddCardToHand(player, entity);

    return entity;
}
}  // namespace Hearthstonepp::Generic