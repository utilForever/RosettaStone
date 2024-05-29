// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Managers/GameManager.hpp>

namespace RosettaStone::Battlegrounds
{
void GameManager::ProcessNextPhase(Game& game, Phase phase)
{
    game.GetGameState().phase = phase;

    switch (phase)
    {
        case Phase::SELECT_HERO:
            game.SelectHero();
            break;
        case Phase::RECRUIT:
            game.Recruit();
            break;
        case Phase::COMBAT:
            game.Combat();
            break;
        case Phase::GAMEOVER:
            game.GameOver();
            break;
        default:
            break;
    }
}
}  // namespace RosettaStone::Battlegrounds
