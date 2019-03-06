// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_GAME_CONFIG_HPP
#define HEARTHSTONEPP_GAME_CONFIG_HPP

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

    CardClass player1Class;
    CardClass player2Class;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GAME_CONFIG_HPP