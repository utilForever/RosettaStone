// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Commons/Constants.hpp>

namespace RosettaStone::Generic
{
void TakeDamageToCharacter(Entity* source, Character* target, int amount,
                           bool isSpellDamage)
{
    if (isSpellDamage)
    {
        amount += static_cast<int>(source->owner->currentSpellPower);
    }

    target->TakeDamage(*source, amount);
}

void AddCardToHand(Player& player, Entity* entity)
{
    // Add card to graveyard if hand is full
    if (player.GetHand().IsFull())
    {
        player.GetGraveyard().AddCard(*entity);
        return;
    }

    // Add card to hand
    player.GetHand().AddCard(*entity);
}

void RemoveCardFromHand(Player& player, Entity* entity)
{
    // Remove card from hand
    player.GetHand().RemoveCard(*entity);
}

void RemoveMinionFromField(Player& player, Minion* minion)
{
    // Remove card from field
    player.GetField().RemoveMinion(*minion);
}

void ChangeManaCrystal(Player& player, int amount, bool fill)
{
    // Available and maximum mana are up to a maximum of 10
    if (player.GetTotalMana() + amount > MANA_UPPER_LIMIT)
    {
        if (!fill)
        {
            player.SetUsedMana(player.GetUsedMana() + MANA_UPPER_LIMIT -
                               player.GetTotalMana());
        }

        player.SetTotalMana(MANA_UPPER_LIMIT);
    }
    // Maximum mana are up to a minimum of 0
    else if (player.GetTotalMana() + amount < 0)
    {
        player.SetTotalMana(0);
    }
    else
    {
        if (!fill)
        {
            player.SetUsedMana(player.GetUsedMana() + amount);
        }

        player.SetTotalMana(player.GetTotalMana() + amount);
    }
}

void TransformMinion(Player& player, Minion* oldMinion, Card&& card)
{
    const auto newMinion =
        dynamic_cast<Minion*>(Entity::GetFromCard(player, std::move(card)));
    if (newMinion == nullptr)
    {
        return;
    }

    player.GetField().ReplaceMinion(*oldMinion, *newMinion);
}
}  // namespace RosettaStone::Generic
