// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAY_CARD_HPP
#define ROSETTASTONE_PLAY_CARD_HPP

#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Models/Spell.hpp>
#include <Rosetta/Models/Weapon.hpp>

namespace RosettaStone::Generic
{
//! Plays a card from player's hand.
//! \param player The player to play card.
//! \param source A pointer to source entity to play card.
//! \param target A target of the character to receive power.
//! \param fieldPos A value indicating where to place card.
//! \param chooseOne The index of chosen card from two cards.
void PlayCard(Player& player, Entity* source, Character* target = nullptr,
              int fieldPos = -1, int chooseOne = 0);

//! Plays a minion card from player's hand.
//! \param player The player to play minion card.
//! \param minion A pointer to minion card to play.
//! \param target A target of the character to receive power.
//! \param fieldPos A value indicating where to place card.
//! \param chooseOne The index of chosen card from two cards.
void PlayMinion(Player& player, Minion* minion, Character* target = nullptr,
                int fieldPos = -1, int chooseOne = 0);

//! Plays a spell card from player's hand.
//! \param player The player to play spell card.
//! \param spell A pointer to spell card to play.
//! \param target A target of the character to receive power.
//! \param chooseOne The index of chosen card from two cards.
void PlaySpell(Player& player, Spell* spell, Character* target = nullptr,
               int chooseOne = 0);

//! Plays a weapon card from player's hand.
//! \param player The player to play weapon card.
//! \param weapon A pointer to weapon card to play.
//! \param target A target of the character to receive power.
void PlayWeapon(Player& player, Weapon* weapon, Character* target = nullptr);

//! Gets a value indicating whether source entity is playable by player.
//! Dynamic requirements are checked, eg: If a spell costs health instead of
//! mana, this method will return false if the health cost would be higher than
//! the available health.
//! \param player The player to play card.
//! \param source A pointer to source entity to play card.
//! \return true if source entity is playable by player, false otherwise.
bool IsPlayableByPlayer(Player& player, Entity* source);

//! Gets a value indicating whether source entity is playable by player.
//! Dynamic requirements are checked, eg: If a spell costs health instead of
//! mana, this method will return false if the health cost would be higher than
//! the available health.
//! \param player The player to play card.
//! \param source A pointer to source entity to play card.
//! \return true if source entity is playable by player, false otherwise.
bool IsPlayableByPlayer(const Player& player, Entity* source);

//! Gets a value indicating whether source entity is playable by card
//! requirements. Static requirements are checked.
//! \param source A pointer to source entity to play card.
//! \return true if source entity is playable by card requirements, false
//! otherwise.
bool IsPlayableByCardReq(Entity* source);
}  // namespace RosettaStone::Generic

#endif  // ROSETTASTONE_PLAY_CARD_HPP
