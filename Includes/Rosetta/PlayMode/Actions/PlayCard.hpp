// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_PLAY_CARD_HPP
#define ROSETTASTONE_PLAYMODE_PLAY_CARD_HPP

#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Models/Weapon.hpp>

namespace RosettaStone::PlayMode::Generic
{
//! Plays a card from player's hand.
//! \param player The player to play card.
//! \param source A pointer to source entity to play card.
//! \param target A target of the character to receive power.
//! \param fieldPos A value indicating where to place card.
//! \param chooseOne The index of chosen card from two cards.
void PlayCard(Player* player, Playable* source, Character* target = nullptr,
              int fieldPos = -1, int chooseOne = 0);

//! Plays a hero card from player's hand.
//! \param player The player to play hero card.
//! \param hero A pointer to hero card to play.
//! \param target A target of the character to receive power.
//! \param chooseOne The index of chosen card from two cards.
void PlayHero(Player* player, Hero* hero, Character* target = nullptr,
              int chooseOne = 0);

//! Plays a minion card from player's hand.
//! \param player The player to play minion card.
//! \param minion A pointer to minion card to play.
//! \param target A target of the character to receive power.
//! \param fieldPos A value indicating where to place card.
//! \param chooseOne The index of chosen card from two cards.
void PlayMinion(Player* player, Minion* minion, Character* target = nullptr,
                int fieldPos = -1, int chooseOne = 0);

//! Plays a spell card from player's hand.
//! \param player The player to play spell card.
//! \param spell A pointer to spell card to play.
//! \param target A target of the character to receive power.
//! \param chooseOne The index of chosen card from two cards.
void PlaySpell(Player* player, Spell* spell, Character* target = nullptr,
               int chooseOne = 0);

//! Plays a weapon card from player's hand.
//! \param player The player to play weapon card.
//! \param weapon A pointer to weapon card to play.
//! \param target A target of the character to receive power.
void PlayWeapon(Player* player, Weapon* weapon, Character* target = nullptr);
}  // namespace RosettaStone::PlayMode::Generic

#endif  // ROSETTASTONE_PLAYMODE_PLAY_CARD_HPP
