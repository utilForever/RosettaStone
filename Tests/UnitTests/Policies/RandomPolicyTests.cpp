// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Policies/RandomPolicy.hpp>
#include <Rosetta/Tasks/PlayerTasks/ChooseTask.hpp>

using namespace RosettaStone;

TEST(RandomPolicy, AutoRun)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::RANDOM;
    config.doShuffle = false;
    config.doFillDecks = false;
    config.skipMulligan = true;
    config.autoRun = true;

    std::array<std::string, START_DECK_SIZE> deck = {
        "CS2_106", "CS2_105", "CS1_112", "CS1_112",  // 1
        "CS1_113", "CS1_113", "CS1_130", "CS1_130",  // 2
        "CS2_007", "CS2_007", "CS2_022", "CS2_022",  // 3
        "CS2_023", "CS2_023", "CS2_024", "CS2_024",  // 4
        "CS2_025", "CS2_025", "CS2_026", "CS2_026",  // 5
        "CS2_027", "CS2_027", "CS2_029", "CS2_029",  // 6
        "CS2_032", "CS2_032", "CS2_033", "CS2_033",  // 7
        "CS2_037", "CS2_037"
    };

    for (size_t i = 0; i < START_DECK_SIZE; ++i)
    {
        config.player1Deck[i] = Cards::GetInstance().FindCardByID(deck[i]);
        config.player2Deck[i] = Cards::GetInstance().FindCardByID(deck[i]);
    }

    Game game(config);

    RandomPolicy policy;
    game.GetPlayer1().policy = &policy;
    game.GetPlayer2().policy = &policy;

    game.StartGame();
}

TEST(RandomPolicy, Mulligan)
{
    for (int i = 0; i < 10; ++i)
    {
        GameConfig config;
        config.player1Class = CardClass::ROGUE;
        config.player2Class = CardClass::PALADIN;
        config.startPlayer = PlayerType::RANDOM;
        config.doShuffle = false;
        config.doFillDecks = false;
        config.skipMulligan = false;
        config.autoRun = true;

        std::array<std::string, START_DECK_SIZE> deck = {
            "CS2_106", "CS2_105", "CS1_112", "CS1_112",  // 1
            "CS1_113", "CS1_113", "CS1_130", "CS1_130",  // 2
            "CS2_007", "CS2_007", "CS2_022", "CS2_022",  // 3
            "CS2_023", "CS2_023", "CS2_024", "CS2_024",  // 4
            "CS2_025", "CS2_025", "CS2_026", "CS2_026",  // 5
            "CS2_027", "CS2_027", "CS2_029", "CS2_029",  // 6
            "CS2_032", "CS2_032", "CS2_033", "CS2_033",  // 7
            "CS2_037", "CS2_037"
        };

        for (size_t j = 0; j < START_DECK_SIZE; ++j)
        {
            config.player1Deck[j] = Cards::GetInstance().FindCardByID(deck[j]);
            config.player2Deck[j] = Cards::GetInstance().FindCardByID(deck[j]);
        }

        Game game(config);

        RandomPolicy policy;
        game.GetPlayer1().policy = &policy;
        game.GetPlayer2().policy = &policy;

        game.PlayPolicy();

        EXPECT_EQ(game.state, State::COMPLETE);
    }
}