// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Games/Game.hpp>
#include <Rosetta/Battlegrounds/Managers/GameManager.hpp>

namespace RosettaStone::Battlegrounds
{
void Game::Start()
{
    // Set next phase
    nextPhase = Phase::SELECT_HERO;
    GameManager::ProcessNextPhase(*this, nextPhase);
}

void Game::SelectHero()
{
}

void Game::Recruit()
{
}

void Game::Combat()
{
    // Set next phase
    nextPhase = Phase::RECRUIT;
    GameManager::ProcessNextPhase(*this, nextPhase);
}

void Game::GameOver()
{
}
}  // namespace RosettaStone::Battlegrounds
