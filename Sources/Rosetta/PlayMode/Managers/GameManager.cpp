// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Managers/GameManager.hpp>

namespace RosettaStone::PlayMode
{
void GameManager::ProcessNextStep(Game& game, Step step)
{
    switch (step)
    {
        case Step::BEGIN_FIRST:
            game.step = step;
            game.BeginFirst();
            break;
        case Step::BEGIN_SHUFFLE:
            game.step = step;
            game.BeginShuffle();
            break;
        case Step::BEGIN_DRAW:
            game.step = step;
            game.BeginDraw();
            break;
        case Step::BEGIN_MULLIGAN:
            game.step = step;
            game.BeginMulligan();
            break;
        case Step::MAIN_BEGIN:
            game.step = step;
            game.MainBegin();
            break;
        case Step::MAIN_READY:
            game.step = step;
            game.MainReady();
            break;
        case Step::MAIN_START_TRIGGERS:
            game.step = step;
            game.MainStartTriggers();
            break;
        case Step::MAIN_RESOURCE:
            game.step = step;
            game.MainResource();
            break;
        case Step::MAIN_DRAW:
            game.step = step;
            game.MainDraw();
            break;
        case Step::MAIN_START:
            game.step = step;
            game.MainStart();
            break;
        case Step::MAIN_ACTION:
            game.step = step;
            game.MainAction();
            break;
        case Step::MAIN_COMBAT:
            break;
        case Step::MAIN_END:
            game.step = step;
            game.MainEnd();
            break;
        case Step::MAIN_CLEANUP:
            game.step = step;
            game.MainCleanUp();
            break;
        case Step::MAIN_NEXT:
            game.step = step;
            game.MainNext();
            break;
        case Step::FINAL_WRAPUP:
            game.FinalWrapUp();
            break;
        case Step::FINAL_GAMEOVER:
            game.FinalGameOver();
            break;
        default:
            break;
    }
}
}  // namespace RosettaStone::PlayMode
