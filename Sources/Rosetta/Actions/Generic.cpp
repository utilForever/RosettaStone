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
    if (player.GetHandZone().IsFull())
    {
        player.GetGraveyardZone().Add(*entity);
        return;
    }

    // Add card to hand
    player.GetHandZone().Add(*entity);
}

void ShuffleIntoDeck(Player& player, Entity* entity)
{
    // Add card to graveyard if deck is full
    if (player.GetDeckZone().IsFull())
    {
        return;
    }

    // Add card into deck and shuffle it
    player.GetDeckZone().Add(*entity);
    player.GetDeckZone().Shuffle();
}

void ChangeManaCrystal(Player& player, int amount, bool fill)
{
    // Available and maximum mana are up to a maximum of 10
    if (player.GetTotalMana() + amount > MANA_UPPER_LIMIT)
    {
        // Add mana crystal when fill is true
        if (!fill)
        {
            player.SetUsedMana(player.GetUsedMana() + MANA_UPPER_LIMIT -
                               player.GetTotalMana());
        }
        else
        {
            player.SetUsedMana(player.GetUsedMana() + MANA_UPPER_LIMIT -
                               player.GetTotalMana() - amount);
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

void TransformMinion(Player& player, Minion* oldMinion, Card* card)
{
    const auto newMinion =
        dynamic_cast<Minion*>(Entity::GetFromCard(player, card));
    if (newMinion == nullptr)
    {
        return;
    }

    player.GetFieldZone().Replace(*oldMinion, *newMinion);
}

IZone* GetZone(Player& player, ZoneType zoneType)
{
    switch (zoneType)
    {
        case ZoneType::PLAY:
            return &player.GetFieldZone();
        case ZoneType::DECK:
            return &player.GetDeckZone();
        case ZoneType::HAND:
            return &player.GetHandZone();
        case ZoneType::GRAVEYARD:
            return &player.GetGraveyardZone();
        case ZoneType::SETASIDE:
            return &player.GetSetasideZone();
        case ZoneType::SECRET:
            return &player.GetSecretZone();
        case ZoneType::INVALID:
        case ZoneType::REMOVEDFROMGAME:
            return nullptr;
    }

    return nullptr;
}
}  // namespace RosettaStone::Generic
