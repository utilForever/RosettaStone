// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_GAME_CONFIG_HPP
#define ROSETTASTONE_PLAYMODE_GAME_CONFIG_HPP

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Cards/Card.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>

#include <array>

namespace RosettaStone::PlayMode
{
//!
//! \brief GameConfig struct.
//!
//! This struct holds all configuration values to create a new Game instance.
//!
struct GameConfig
{
    //! Default constructor.
    GameConfig()
    {
        for (int i = 0; i < START_DECK_SIZE; ++i)
        {
            player1Deck[i] = nullptr;
            player2Deck[i] = nullptr;
        }
    }

    FormatType formatType = FormatType::STANDARD;
    PlayerType startPlayer = PlayerType::RANDOM;
    CardClass player1Class = CardClass::INVALID;
    CardClass player2Class = CardClass::INVALID;

    std::array<Card*, START_DECK_SIZE> player1Deck;
    std::array<Card*, START_DECK_SIZE> player2Deck;

    std::array<std::string, 9> fillCardIDs = {
        "UNG_028", "UNG_067", "UNG_116", "UNG_829", "UNG_934",
        "UNG_920", "UNG_940", "UNG_942", "UNG_954"
    };

    bool doFillDecks = false;
    bool doShuffle = true;
    bool skipMulligan = true;
    bool autoRun = true;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_GAME_CONFIG_HPP
