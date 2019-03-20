// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/GameAgent.hpp>

namespace RosettaStone
{
GameAgent::GameAgent(GameConfig& gameConfig, IPolicy* p1Policy,
                     IPolicy* p2Policy)
    : Game(gameConfig)
{
    GetPlayer1().SetPolicy(p1Policy);
    GetPlayer2().SetPolicy(p2Policy);
}

void GameAgent::BeginFirst()
{
    // Do nothing
}

void GameAgent::BeginShuffle()
{
    // Do nothing
}

void GameAgent::BeginDraw()
{
    // Do nothing
}

void GameAgent::BeginMulligan()
{
    // Do nothing
}

void GameAgent::MainBegin()
{
    // Do nothing
}

void GameAgent::MainReady()
{
    // Do nothing
}

void GameAgent::MainStartTriggers()
{
    // Do nothing
}

void GameAgent::MainResource()
{
    // Do nothing
}

void GameAgent::MainDraw()
{
    // Do nothing
}

void GameAgent::MainStart()
{
    // Do nothing
}

void GameAgent::MainEnd()
{
    // Do nothing
}

void GameAgent::MainCleanUp()
{
    // Do nothing
}

void GameAgent::MainNext()
{
    // Do nothing
}

void GameAgent::FinalWrapUp()
{
    // Do nothing
}

void GameAgent::FinalGameOver()
{
    // Do nothing
}
}  // namespace RosettaStone
