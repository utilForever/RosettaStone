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

    // Get card to draw
    Entity* entity = &player.GetDeckZone().Remove(
        cardToDraw != nullptr ? *cardToDraw
                              : *player.GetDeckZone().GetTopCard());

    // Add card to hand
    AddCardToHand(player, entity);

    return entity;
}

Entity* DrawCard(Player& player, Card* card)
{
    Entity* entity = Entity::GetFromCard(player, card);
    AddCardToHand(player, entity);

    return entity;
}
}  // namespace RosettaStone::Generic
