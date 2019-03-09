// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_GAME_CONFIG_HPP
#define HEARTHSTONEPP_GAME_CONFIG_HPP

#include <hspp/Cards/Card.hpp>
#include <hspp/Commons/Constants.hpp>

#include <array>

namespace Hearthstonepp
{
//!
//! \brief GameConfig struct.
//!
//! This struct holds all configuration values to create a new Game instance.
//!
struct GameConfig
{
    PlayerType startPlayer = PlayerType::RANDOM;

    CardClass player1Class = CardClass::MAGE;
    CardClass player2Class = CardClass::WARLOCK;

    std::array<Card, START_DECK_SIZE> player1Deck;
    std::array<Card, START_DECK_SIZE> player2Deck;

    bool doShuffle = true;
    bool skipMulligan = true;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_CONFIG_HPP