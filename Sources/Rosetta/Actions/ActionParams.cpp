// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Actions/ActionParams.hpp>

namespace RosettaStone
{
void ActionParams::Initialize(const Game& game)
{
    m_checker.Check(game);
}

void ActionParams::Initialize(const ActionChecker& checker)
{
    m_checker.Check(checker);
}
}  // namespace RosettaStone