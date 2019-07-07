// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Actions/ActionChoices.hpp>
#include <Rosetta/Actions/ActionParams.hpp>

namespace RosettaStone
{
void ActionParams::Initialize(const Game& game)
{
    m_checker.Check(game);
}

void ActionParams::Initialize(const ActionValidGetter& getter)
{
    m_checker.Check(getter);
}

const ActionValidChecker& ActionParams::GetChecker() const
{
    return m_checker;
}

MainOpType ActionParams::ChooseMainOp()
{
    const auto mainOpsCount = m_checker.GetMainActionsCount();
    const auto& mainOps = m_checker.GetMainActions();
    const int mainOpIdx = GetNumber(ActionType::MAIN_ACTION, mainOpsCount);
    return mainOps[mainOpIdx];
}

int ActionParams::GetMinionPutLocation(int minions)
{
    const int idx =
        GetNumber(ActionType::CHOOSE_MINION_PUT_LOCATION, minions + 1);
    return idx;
}

Character* ActionParams::GetSpecifiedTarget(
    const std::vector<Character*>& targets)
{
    if (targets.empty())
    {
        return nullptr;
    }

    const int size = static_cast<int>(targets.size());
    const int idx = GetNumber(ActionType::CHOOSE_TARGET, size);
    return targets[idx];
}

int ActionParams::ChooseOne(const std::vector<int>& cards)
{
    ActionChoices choices(cards);
    const int val = GetNumber(ActionType::CHOOSE_ONE, choices);
    return val;
}

Entity* ActionParams::ChooseHandCard()
{
    const auto& playableCards = m_checker.GetPlayableCards();
    const int idx = GetNumber(ActionType::CHOOSE_HAND_CARD,
                              static_cast<int>(playableCards.size()));
    return playableCards[idx];
}

Character* ActionParams::GetAttacker()
{
    const auto& attackers = m_checker.GetAttackers();
    const int idx = GetNumber(ActionType::CHOOSE_ATTACKER,
                              static_cast<int>(attackers.size()));
    return attackers[idx];
}

int ActionParams::GetNumber(ActionType actionType, int exclusiveMax)
{
    ActionChoices choices(exclusiveMax);
    return GetNumber(actionType, choices);
}
}  // namespace RosettaStone