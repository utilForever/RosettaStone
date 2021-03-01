// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "Console.hpp"

namespace RosettaStone
{
Console::Console(Mode mode) : m_mode{ mode }
{
    // Do nothing
}

void Console::ProcessGame()
{
    switch (m_mode)
    {
        case Mode::STANDARD:
        case Mode::WILD:
            InputDeckCodes();
            break;
        case Mode::BATTLEGROUNDS:
            PlayBattlegrounds();
            break;
    }
}

void Console::InputDeckCodes()
{
}

void Console::PlayBattlegrounds()
{
}
}  // namespace RosettaStone