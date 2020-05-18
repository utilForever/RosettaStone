// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Actions/ActionApplyHelper.hpp>

namespace RosettaStone::PlayMode
{
ActionApplyHelper::ActionParamsChooser::ActionParamsChooser(
    const std::vector<int>& choices, std::size_t& choicesIdx)
    : m_choices(choices), m_choicesIdx(choicesIdx), m_shouldSkip(false)
{
    // Do nothing
}

bool ActionApplyHelper::ActionParamsChooser::HasFurtherChoices() const
{
    return m_choicesIdx <= m_choices.size();
}

bool ActionApplyHelper::ActionParamsChooser::ShouldSkip() const
{
    return m_shouldSkip;
}

std::size_t ActionApplyHelper::ActionParamsChooser::GetNumber(
    ActionType actionType, ActionChoices& choices)
{
    m_shouldSkip = false;

    if (actionType != ActionType::MAIN_ACTION)
    {
        if (choices.Size() == 1)
        {
            m_shouldSkip = true;
            return 0;
        }
    }

    return GetNextChoice(0, choices.Size());
}

int ActionApplyHelper::ActionParamsChooser::GetNextChoice(
    int min, [[maybe_unused]] int max) const
{
    if (m_choicesIdx >= m_choices.size())
    {
        ++m_choicesIdx;
        return min;
    }

    const int choice = m_choices[m_choicesIdx];
    ++m_choicesIdx;

    return choice;
}

ActionApplyHelper::ActionParamsCallback::ActionParamsCallback(
    const std::vector<int>& choices, std::size_t& choicesIdx,
    CallbackInfo& result)
    : m_result(result), m_choser(choices, choicesIdx)
{
}

void ActionApplyHelper::ActionParamsCallback::Initialize(const Game& game)
{
    m_result = NullInfo();
    m_choser.Initialize(game);
}

MainOpType ActionApplyHelper::ActionParamsCallback::ChooseMainOp()
{
    const auto ret = m_choser.ChooseMainOp();

    if (ShouldRecord())
    {
        m_result = MainOpInfo();
    }

    return ret;
}

Playable* ActionApplyHelper::ActionParamsCallback::ChooseHandCard()
{
    const auto ret = m_choser.ChooseHandCard();

    if (ShouldRecord())
    {
        m_result = ChooseHandCardInfo();
    }

    return ret;
}

Character* ActionApplyHelper::ActionParamsCallback::GetAttacker()
{
    const auto ret = m_choser.GetAttacker();

    if (ShouldRecord())
    {
        m_result = ChooseAttackerInfo();
    }

    return ret;
}

std::size_t ActionApplyHelper::ActionParamsCallback::GetMinionPutLocation(
    int minions)
{
    const auto ret = m_choser.GetMinionPutLocation(minions);

    if (ShouldRecord())
    {
        m_result = MinionPutLocationInfo(minions);
    }

    return ret;
}

Character* ActionApplyHelper::ActionParamsCallback::GetSpecifiedTarget(
    const std::vector<Character*>& targets)
{
    const auto ret = m_choser.GetSpecifiedTarget(targets);

    if (ShouldRecord())
    {
        m_result = GetSpecifiedTargetInfo(targets);
    }

    return ret;
}

std::size_t ActionApplyHelper::ActionParamsCallback::ChooseOne(
    const std::vector<std::size_t>& cards)
{
    const auto ret = m_choser.ChooseOne(cards);

    if (ShouldRecord())
    {
        m_result = ChooseOneInfo(cards);
    }

    return ret;
}

std::size_t ActionApplyHelper::ActionParamsCallback::GetNumber(
    [[maybe_unused]] ActionType actionType,
    [[maybe_unused]] ActionChoices& choices)
{
    return 0;
}

bool ActionApplyHelper::ActionParamsCallback::ShouldRecord() const
{
    if (!std::holds_alternative<NullInfo>(m_result))
    {
        return false;
    }
    if (m_choser.ShouldSkip())
    {
        return false;
    }
    if (m_choser.HasFurtherChoices())
    {
        return false;
    }

    return true;
}

void ActionApplyHelper::AppendChoice(int choice)
{
    m_choices.push_back(choice);
}

void ActionApplyHelper::ClearChoices()
{
    m_choices.clear();
}

ActionApplyHelper::CallbackInfo ActionApplyHelper::ApplyChoices(
    Game& game) const
{
    std::tuple<PlayState, PlayState> result;
    return ApplyChoices(game, result);
}

ActionApplyHelper::CallbackInfo ActionApplyHelper::ApplyChoices(
    Game& game, std::tuple<PlayState, PlayState>& result) const
{
    CallbackInfo info = NullInfo();
    size_t choicesIdx = 0;
    ActionParamsCallback actionCallback(m_choices, choicesIdx, info);

    while (m_choices.size() > choicesIdx)
    {
        actionCallback.Initialize(game);
        result = game.PerformAction(actionCallback);
    }

    return info;
}
}  // namespace RosettaStone::PlayMode
