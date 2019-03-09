// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Games/GameManager.hpp>

namespace Hearthstonepp
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
        default:
            break;
    }
}
}  // namespace Hearthstonepp