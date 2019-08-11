// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/Simulation/RandomPlayoutsPolicy.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaTorch::MCTS
{
bool RandomPlayoutsPolicy::IsEnableCutoff()
{
    return false;
}

PlayState RandomPlayoutsPolicy::GetCutoffResult(
    [[maybe_unused]] const Board& board,
    [[maybe_unused]] StateValue& stateValue)
{
    return PlayState::PLAYING;
}

void RandomPlayoutsPolicy::StartAction(
    [[maybe_unused]] const Board& board,
    [[maybe_unused]] const ActionValidChecker& checker)
{
    // Do nothing
}

int RandomPlayoutsPolicy::GetChoice(
    [[maybe_unused]] const Board& board,
    [[maybe_unused]] const ActionValidChecker& checker,
    [[maybe_unused]] ActionType actionType, const ChoiceGetter& getter)
{
    const size_t count = getter.Size();
    const auto randIdx = Random::get<size_t>(0, count - 1);
    const int result = getter.Get(randIdx);

    return result;
}
}  // namespace RosettaTorch::MCTS