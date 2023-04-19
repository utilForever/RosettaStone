// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Agents/RandomAgent.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[RandomAgent] - GetActionForMulligan")
{
    std::unique_ptr<IAgent> agent1 = std::make_unique<RandomAgent>();
    agent1->SetPlayerType(PlayerType::PLAYER1);

    std::unique_ptr<IAgent> agent2 = std::make_unique<RandomAgent>();
    agent2->SetPlayerType(PlayerType::PLAYER2);

    GameConfig gameConfig;
    gameConfig.player1Class = CardClass::DEMONHUNTER;
    gameConfig.player2Class = CardClass::MAGE;
    gameConfig.doFillDecks = true;
    gameConfig.autoRun = true;
    gameConfig.skipMulligan = false;
    gameConfig.startPlayer = PlayerType::RANDOM;

    Game game{ gameConfig };
    game.Start();

    Player* player1 = game.GetPlayer1();
    Player* player2 = game.GetPlayer2();
    CHECK_GE(player1->GetHandZone()->GetCount(), 3);
    CHECK_LE(player1->GetHandZone()->GetCount(), 4);
    CHECK_GE(player2->GetHandZone()->GetCount(), 3);
    CHECK_LE(player2->GetHandZone()->GetCount(), 4);

    const std::vector<int> p1Choices = player1->choice->choices;
    const std::vector<int> p2Choices = player2->choice->choices;
    CHECK_GE(p1Choices.size(), 3);
    CHECK_LE(p1Choices.size(), 4);
    CHECK_GE(p2Choices.size(), 3);
    CHECK_LE(p2Choices.size(), 4);

    const std::vector<int> indices1 = agent1->GetActionForMulligan(game);
    const std::vector<int> indices2 = agent2->GetActionForMulligan(game);
    CHECK_GE(indices1.size(), 0);
    CHECK_LE(indices1.size(), 4);
    CHECK_GE(indices2.size(), 0);
    CHECK_LE(indices2.size(), 4);

    Generic::ChoiceMulligan(game.GetPlayer1(), indices1);
    Generic::ChoiceMulligan(game.GetPlayer2(), indices2);
    CHECK_GE(player1->GetHandZone()->GetCount(), 3);
    CHECK_LE(player1->GetHandZone()->GetCount(), 4);
    CHECK_GE(player2->GetHandZone()->GetCount(), 3);
    CHECK_LE(player2->GetHandZone()->GetCount(), 4);
}