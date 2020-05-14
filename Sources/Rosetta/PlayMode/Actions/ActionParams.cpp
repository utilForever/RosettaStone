// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Actions/ActionChoices.hpp>
#include <Rosetta/PlayMode/Actions/ActionParams.hpp>

namespace RosettaStone::PlayMode
{
void ActionParams::Initialize(const Game& game)
{
    m_checker.Check(game);
}

void ActionParams::Initialize(ActionValidGetter& getter)
{
    m_checker.Check(getter);
}

void ActionParams::Initialize(ActionValidGetter&& getter)
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

std::size_t ActionParams::GetMinionPutLocation(int minions)
{
    const std::size_t idx =
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
    const std::size_t idx = GetNumber(ActionType::CHOOSE_TARGET, size);
    return targets[idx];
}

std::size_t ActionParams::ChooseOne(const std::vector<std::size_t>& cards)
{
    ActionChoices choices(cards);
    const std::size_t val = GetNumber(ActionType::CHOOSE_ONE, choices);
    return val;
}

Playable* ActionParams::ChooseHandCard()
{
    const auto& playableCards = m_checker.GetPlayableCards();
    const std::size_t idx =
        GetNumber(ActionType::CHOOSE_HAND_CARD, playableCards.size());
    return playableCards[idx];
}

Character* ActionParams::GetAttacker()
{
    const auto& attackers = m_checker.GetAttackers();
    const std::size_t idx =
        GetNumber(ActionType::CHOOSE_ATTACKER, attackers.size());
    return attackers[idx];
}

std::size_t ActionParams::GetNumber(ActionType actionType, std::size_t max)
{
    ActionChoices choices(max);
    return GetNumber(actionType, choices);
}
}  // namespace RosettaStone::PlayMode