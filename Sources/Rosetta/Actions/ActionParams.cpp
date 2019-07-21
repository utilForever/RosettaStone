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

size_t ActionParams::GetMinionPutLocation(int minions)
{
    const size_t idx =
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
    const size_t idx = GetNumber(ActionType::CHOOSE_TARGET, size);
    return targets[idx];
}

size_t ActionParams::ChooseOne(std::vector<size_t> cards)
{
    ActionChoices choices(std::move(cards));
    const size_t val = GetNumber(ActionType::CHOOSE_ONE, choices);
    return val;
}

Entity* ActionParams::ChooseHandCard()
{
    const auto& playableCards = m_checker.GetPlayableCards();
    const size_t idx =
        GetNumber(ActionType::CHOOSE_HAND_CARD, playableCards.size());
    return playableCards[idx];
}

Character* ActionParams::GetAttacker()
{
    const auto& attackers = m_checker.GetAttackers();
    const size_t idx = GetNumber(ActionType::CHOOSE_ATTACKER, attackers.size());
    return attackers[idx];
}

size_t ActionParams::GetNumber(ActionType actionType, size_t exclusiveMax)
{
    ActionChoices choices(exclusiveMax);
    return GetNumber(actionType, choices);
}
}  // namespace RosettaStone