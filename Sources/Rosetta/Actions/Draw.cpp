// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone::Generic
{
Entity* Draw(Player& player, Entity* cardToDraw)
{
    // Take fatigue damage for player if deck is empty
    if (player.GetDeckZone().IsEmpty())
    {
        const int fatigueDamage =
            player.GetHero()->fatigue == 0 ? 1 : player.GetHero()->fatigue + 1;
        player.GetHero()->TakeDamage(*player.GetHero(), fatigueDamage);

        return nullptr;
    }

    Entity* entity;

    // Get card to draw
    if (cardToDraw)
    {
        entity = &player.GetDeckZone().RemoveCard(*cardToDraw);
    }
    else
    {
        Entity* topCard = player.GetDeckZone().GetTopCard();
        if (topCard == nullptr)
        {
            return nullptr;
        }

        entity = &player.GetDeckZone().RemoveCard(*topCard);
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
}  // namespace RosettaStone::Generic
