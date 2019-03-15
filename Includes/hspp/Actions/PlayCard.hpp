// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_PLAY_CARD_HPP
#define HEARTHSTONEPP_PLAY_CARD_HPP

#include <hspp/Models/Minion.hpp>
#include <hspp/Models/Player.hpp>
#include <hspp/Models/Spell.hpp>
#include <hspp/Models/Weapon.hpp>

namespace Hearthstonepp::Generic
{
//! Plays a card from player's hand.
//! \param player The player to play card.
//! \param source A pointer to source entity to play card.
//! \param target A target of the character to receive power.
//! \param fieldPos A value indicating where to place card.
void PlayCard(Player& player, Entity* source, Character* target = nullptr,
              int fieldPos = -1);

//! Plays a minion card from player's hand.
//! \param player The player to play minion card.
//! \param minion A pointer to minion card to play.
//! \param target A target of the character to receive power.
//! \param fieldPos A value indicating where to place card.
void PlayMinion(Player& player, Minion* minion, Character* target = nullptr,
                int fieldPos = -1);

//! Plays a spell card from player's hand.
//! \param player The player to play spell card.
//! \param spell A pointer to spell card to play.
//! \param target A target of the character to receive power.
void PlaySpell(Player& player, Spell* spell, Character* target = nullptr);

//! Plays a weapon card from player's hand.
//! \param player The player to play weapon card.
//! \param weapon A pointer to weapon card to play.
//! \param target A target of the character to receive power.
void PlayWeapon(Player& player, Weapon* weapon, Character* target = nullptr);
}  // namespace Hearthstonepp::Generic

#endif  // HEARTHSTONEPP_PLAY_CARD_HPP