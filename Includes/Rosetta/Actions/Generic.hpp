// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_GENERIC_HPP
#define ROSETTASTONE_GENERIC_HPP

#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone::Generic
{
//! Takes damage to target character.
//! \param source An entity to give damage.
//! \param target A character to take damage.
//! \param amount A value indicating how much to take damage.
//! \param isSpellDamage true if it is spell damage, and false otherwise.
void TakeDamageToCharacter(Playable* source, Character* target, int amount,
                           bool isSpellDamage);

//! Adds card to hand.
//! \param player The player to add card to hand.
//! \param entity A card to add.
//! \return The flag that indicates a card is successfully added to hand.
bool AddCardToHand(Player* player, Playable* entity);

//! Creates a new enchantment and attaches it to the given target.
//! \param enchantmentCard The base card for the enchantment.
//! \param creator The creator entity.
//! \param target The target entity.
//! \param num1 The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
//! \param num2 The number of GameTag::TAG_SCRIPT_DATA_NUM_2.
//! \param entityID The entity ID to be stored in the enchantment.
void AddEnchantment(Card* enchantmentCard, Playable* creator, Entity* target,
                    int num1 = -1, int num2 = -1, int entityID = 0);

//! Shuffles card into deck.
//! \param player The player to shuffle card into deck.
//! \param entity A card to shuffle into deck.
void ShuffleIntoDeck(Player* player, Playable* entity);

//! Changes mana crystal of the player.
//! \param player The player to change mana crystal.
//! \param amount A value indicating how much to change mana crystal.
//! \param fill true if mana crystal is filled, and false otherwise.
void ChangeManaCrystal(Player* player, int amount, bool fill);

//! Transforms a minion to another.
//! \param player The owner of minion to transform.
//! \param oldMinion An old minion to transform.
//! \param card A new card ID to transform.
void TransformMinion(Player* player, Minion* oldMinion, Card* card);

//! Returns the zone corresponding to the zone type.
//! \param player An owner of zone.
//! \param zoneType The type of zone.
//! \return The zone corresponding to the zone type.
IZone* GetZone(Player* player, ZoneType zoneType);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_GENERIC_HPP
