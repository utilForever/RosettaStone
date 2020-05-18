// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Actions/ActionTargets.hpp>
#include <Rosetta/PlayMode/Actions/ActionValidGetter.hpp>

namespace RosettaStone::PlayMode
{
ActionTargets::ActionTargets()
{
    Invalidate();
}

void ActionTargets::Analyze(const ActionValidGetter& getter)
{
    Invalidate();

    Fill(PlayerType::PLAYER1, getter);
    Fill(PlayerType::PLAYER2, getter);
}

void ActionTargets::Fill(PlayerType playerType, const ActionValidGetter& getter)
{
    if (playerType == PlayerType::PLAYER1)
    {
        m_targets[0] = getter.GetHero(playerType);

        int minionIdx = 1;
        getter.ForEachMinion(playerType, [&](Minion* minion) {
            m_targets[minionIdx++] = minion;
        });
    }
    else
    {
        m_targets[8] = getter.GetHero(playerType);

        int minionIdx = 9;
        getter.ForEachMinion(playerType, [&](Minion* minion) {
            m_targets[minionIdx++] = minion;
        });
    }
}

void ActionTargets::Invalidate()
{
    for (auto& target : m_targets)
    {
        target = nullptr;
    }
}
}  // namespace RosettaStone::PlayMode