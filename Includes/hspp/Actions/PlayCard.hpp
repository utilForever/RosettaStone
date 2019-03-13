// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_PLAY_CARD_HPP
#define HEARTHSTONEPP_PLAY_CARD_HPP

#include <hspp/Models/Player.hpp>

namespace Hearthstonepp::Generic
{
//! Plays a card from player's hand.
//! \param player The player to play card.
//! \param source A pointer to source entity to play card.
//! \param target A target of the card to receive power.
//! \param fieldPos A value indicating where to place card.
void PlayCard(Player& player, Entity* source, Entity* target = nullptr,
              int fieldPos = -1);

//! Plays a minion from player's hand.
//! \param player The player to play card.
//! \param source A pointer to source entity to play card.
//! \param target A target of the card to receive power.
//! \param fieldPos A value indicating where to place card.
void PlayMinion(Player& player, Entity* source, Entity* target = nullptr,
                int fieldPos = -1);

//! Plays a weapon from player's hand.
//! \param player The player to play card.
//! \param source A pointer to source entity to play card.
//! \param target A target of the card to receive power.
void PlayWeapon(Player& player, Entity* source, Entity* target = nullptr);

//! Plays a spell from player's hand.
//! \param player The player to play card.
//! \param source A pointer to source entity to play card.
//! \param target A target of the card to receive power.
void PlaySpell(Player& player, Entity* source, Entity* target = nullptr);
}  // namespace Hearthstonepp::Generic

#endif  // HEARTHSTONEPP_PLAY_CARD_HPP