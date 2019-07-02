// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Actions/ActionTargets.hpp>

namespace RosettaStone
{
ActionTargets::ActionTargets()
{
    Invalidate();
}

void ActionTargets::Analyze(const ActionChecker& checker)
{
    Invalidate();

    Fill(PlayerType::PLAYER1, checker);
    Fill(PlayerType::PLAYER2, checker);
}

void ActionTargets::Fill(PlayerType playerType, const ActionChecker& checker)
{
    //m_targets[0] = checker.GetHero(playerType);

    //checker.ForEachMinion(playerType, [&](Minion* minion) {

    //});
}

void ActionTargets::Invalidate()
{
    for (auto& target : m_targets)
    {
        target = nullptr;
    }
}
}  // namespace RosettaStone