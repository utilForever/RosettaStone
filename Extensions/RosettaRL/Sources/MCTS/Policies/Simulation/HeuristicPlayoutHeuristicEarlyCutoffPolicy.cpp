// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Policies/Simulation/HeuristicPlayoutHeuristicEarlyCutoffPolicy.hpp>

#include <Rosetta/PlayMode/Actions/ActionParams.hpp>

#include <effolkronium/random.hpp>

#include <tuple>

using Random = effolkronium::random_static;

namespace RosettaTorch::MCTS
{
HeuristicPlayoutHeuristicEarlyCutoffPolicy::
    HeuristicPlayoutHeuristicEarlyCutoffPolicy(const Config& config)
    : m_stateValue(config), m_decisionIdx(0)
{
    // Do nothing
}

bool HeuristicPlayoutHeuristicEarlyCutoffPolicy::IsEnableCutoff()
{
    return true;
}

bool HeuristicPlayoutHeuristicEarlyCutoffPolicy::GetCutoffResult(
    const Board& board, StateValue& stateValue)
{
    const auto val = Random::get<double>(0.0, 1.0);
    if (val >= CUTOFF_PROBABILITY)
    {
        return false;
    }

    stateValue = m_stateValue.GetStateValue(board);
    return true;
}

void HeuristicPlayoutHeuristicEarlyCutoffPolicy::StartAction(
    const Board& board, const ActionValidChecker& checker)
{
    StartNewAction(board, checker);
}

int HeuristicPlayoutHeuristicEarlyCutoffPolicy::GetChoice(
    [[maybe_unused]] const Board& board, const ActionValidChecker& checker,
    [[maybe_unused]] ActionType actionType, const ChoiceGetter& getter)
{
    if constexpr (RANDOMLY_PUT_MINIONS)
    {
        return GetChoiceRandomly(checker, getter);
    }
    else
    {
        return GetChoiceForMainAction(checker, getter);
    }
}

void HeuristicPlayoutHeuristicEarlyCutoffPolicy::StartNewAction(
    const Board& board, const ActionValidChecker& checker)
{
    m_decisionIdx = 0;

    DFSBestStateValue(board, checker);
}

void HeuristicPlayoutHeuristicEarlyCutoffPolicy::DFSBestStateValue(
    const Board& board, const ActionValidChecker& checker)
{
    struct DFSItem
    {
        DFSItem(size_t _choice, size_t _total) : choice(_choice), total(_total)
        {
            // Do nothing
        }

        std::size_t choice;
        std::size_t total;
    };

    class UserChoicePolicy : public ActionParams
    {
     public:
        UserChoicePolicy(std::vector<DFSItem>& dfs,
                         std::vector<DFSItem>::iterator& dfsIter)
            : m_dfs(dfs), m_dfsIter(dfsIter), m_mainOpIdx(-1)
        {
        }

        // TODO: Can we remove this? need special care on main op?
        void SetMainOpIndex(int mainOpIdx)
        {
            m_mainOpIdx = mainOpIdx;
        }

        std::size_t GetNumber(ActionType actionType,
                              ActionChoices& choices) final
        {
            if (actionType == ActionType::MAIN_ACTION)
            {
                return m_mainOpIdx;
            }

            const int total = choices.Size();
            if (total == 1)
            {
                return 0;
            }

            if (actionType == ActionType::RANDOM)
            {
                return Random::get<std::size_t>(0, total - 1);
            }

            if constexpr (RANDOMLY_PUT_MINIONS)
            {
                if (actionType == ActionType::CHOOSE_MINION_PUT_LOCATION)
                {
                    const std::size_t idx =
                        Random::get<std::size_t>(0, total - 1);
                    return choices.Get(idx);
                }
            }

            if (m_dfsIter == m_dfs.end())
            {
                m_dfs.emplace_back(0, static_cast<size_t>(total));
                m_dfsIter = m_dfs.end();
                return choices.Get(0);
            }

            const size_t idx = m_dfsIter->choice;
            ++m_dfsIter;

            return choices.Get(idx);
        }

     private:
        std::vector<DFSItem>& m_dfs;
        std::vector<DFSItem>::iterator& m_dfsIter;
        int m_mainOpIdx;
    };

    std::vector<DFSItem> dfs;
    std::vector<DFSItem>::iterator dfsIter = dfs.begin();

    auto stepNextDFS = [&]() {
        while (!dfs.empty())
        {
            if ((dfs.back().choice + 1) < dfs.back().total)
            {
                break;
            }

            dfs.pop_back();
        }

        if (dfs.empty())
        {
            return false;
        }

        ++dfs.back().choice;
        return true;
    };

    // Need to fix a random sequence for a particular run
    // Since, some callbacks might depend on a random
    // For example, choose one card from randomly-chosen three cards
    UserChoicePolicy userChoice(dfs, dfsIter);
    userChoice.Initialize(
        board.GetCurPlayerStateRefView().GetActionValidGetter());

    auto side = board.GetCurrentPlayer();
    double bestValue = -std::numeric_limits<double>::infinity();

    checker.ForEachMainOp([&](std::size_t mainOpIdx, MainOpType mainOp) {
        userChoice.SetMainOpIndex(static_cast<int>(mainOpIdx));

        while (true)
        {
            Game copiedGame;
            Board copyBoard(copiedGame, board.GetViewType());
            copyBoard.RefCopyFrom(board);

            dfsIter = dfs.begin();
            const auto result = copyBoard.ApplyAction(userChoice);

            auto& [p1Result, p2Result] = result;
            if (p1Result != PlayState::INVALID &&
                p2Result != PlayState::INVALID)
            {
                StateValue stateValue;
                if (p1Result == PlayState::PLAYING &&
                    p2Result == PlayState::PLAYING)
                {
                    stateValue = m_stateValue.GetStateValue(copyBoard);
                }
                else
                {
                    stateValue.SetValue(side->playerType, result);
                }

                const float value = stateValue.GetValue(side->playerType);

                if (m_decision.empty() || value > bestValue)
                {
                    bestValue = value;

                    m_decision.clear();
                    m_decision.push_back(static_cast<int>(mainOpIdx));

                    for (const auto& item : dfs)
                    {
                        m_decision.push_back(static_cast<int>(item.choice));
                    }
                }
            }

            if (!stepNextDFS())
            {
                break;
            }
        }

        return true;
    });
}

int HeuristicPlayoutHeuristicEarlyCutoffPolicy::GetChoiceForMainAction(
    const ActionValidChecker& checker, const ChoiceGetter& getter)
{
    if (m_decisionIdx < m_decision.size())
    {
        return m_decision[m_decisionIdx++];
    }

    // TODO: We fix the random when running DFS search,
    // and in concept, a random might change the best decision.
    // For example, a choose-one with randomly-chosen three cards,
    // we definitely need to re-run the DFS after the random cards are shown.
    // Here, use a pure random choice in these cases.
    return GetChoiceRandomly(checker, getter);
}

int HeuristicPlayoutHeuristicEarlyCutoffPolicy::GetChoiceRandomly(
    [[maybe_unused]] const ActionValidChecker& checker,
    const ChoiceGetter& getter)
{
    const std::size_t count = getter.Size();
    std::size_t idx = 0;
    std::size_t randIdx = Random::get<std::size_t>(0, count - 1);
    int result = -1;

    getter.ForEachChoice([&](int choice) {
        if (idx == randIdx)
        {
            result = choice;
            return false;
        }

        ++idx;
        return true;
    });

    return result;
}
}  // namespace RosettaTorch::MCTS