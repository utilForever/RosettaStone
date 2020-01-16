// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <MCTS/Inspector/InteractiveShell.hpp>

#include <Rosetta/Actions/ActionApplyHelper.hpp>

#include <tuple>

namespace RosettaTorch::MCTS
{
InteractiveShell::InteractiveShell(Agents::MCTSRunner* controller,
                                   StartBoardGetter startBoardGetter)
    : m_controller(controller),
      m_startBoardGetter(startBoardGetter),
      m_node(nullptr)
{
    // Do nothing
}

void InteractiveShell::SetController(Agents::MCTSRunner* controller)
{
    m_controller = controller;
}

void InteractiveShell::SetConfig(const Agents::MCTSConfig& config)
{
    try
    {
        m_stateValue.reset(new NeuralNetworkStateValue(config.mcts));
    }
    catch (...)
    {
        m_stateValue.reset(nullptr);
    }
}

void InteractiveShell::SetStartBoardGetter(StartBoardGetter startBoardGetter)
{
    m_startBoardGetter = std::move(startBoardGetter);
}

void InteractiveShell::DoCommand(std::istream& is, std::ostream& os)
{
    std::string cmd;
    is >> cmd;

    if (cmd == "h" || cmd == "help")
    {
        os << "Commands: " << std::endl
           << "h or help: show this message" << std::endl
           << "b or best: show the best action to do (add -v for verbose)"
           << std::endl
           << "root (1 or 2): set node to root node of player 1 or 2"
           << std::endl
           << "node (addr): set node to specified address." << std::endl;
    }
    else if (cmd == "b" || cmd == "best")
    {
        DoBest(is, os);
    }
    else if (cmd == "root")
    {
        DoRoot(is, os);
    }
    else if (cmd == "node")
    {
        std::uint64_t v = 0;
        is >> std::hex >> v >> std::dec;
        m_node = reinterpret_cast<TreeNode*>(v);
        os << "Node set to: " << m_node << std::endl;
    }
    else
    {
        os << "Unknown command. Type 'h' or 'help' for usage help."
           << std::endl;
    }
}

double InteractiveShell::GetStateValue(const Game& game) const
{
    if (!m_stateValue)
    {
        return std::numeric_limits<double>::quiet_NaN();
    }

    return m_stateValue->GetStateValue(game).GetValue(PlayerType::PLAYER1);
}

std::string InteractiveShell::GetChoiceSuggestionRate(
    const TreeNode* node, int choice, std::uint64_t totalChosenTimes)
{
    const auto* edgeAddon = node->children.GetEdgeAddon(choice);
    const auto chosenTimes = edgeAddon->GetChosenTimes();
    const double chosenPercent = 100.0 * chosenTimes / totalChosenTimes;

    std::stringstream ss;
    ss << chosenPercent << "% (" << chosenTimes << "/" << totalChosenTimes
       << ")";
    return ss.str();
}

std::string InteractiveShell::GetTargetString(Character* character)
{
    Game game = m_startBoardGetter();

    if (game.GetPlayer1()->GetHero() == character)
    {
        return "Your Hero";
    }
    if (game.GetPlayer2()->GetHero() == character)
    {
        return "Opponent Hero";
    }

    const auto FindInMinions = [&](const std::vector<Minion*>& minions) -> int {
        for (std::size_t i = 0; i < minions.size(); ++i)
        {
            if (minions[i] == character)
            {
                return static_cast<int>(i);
            }
        }

        return -1;
    };

    int idx = FindInMinions(game.GetPlayer1()->GetFieldZone()->GetAll());
    if (idx >= 0)
    {
        std::stringstream ss;
        ss << "Your " << (idx + 1) << "th minion";
        return ss.str();
    }

    idx = FindInMinions(game.GetPlayer2()->GetFieldZone()->GetAll());
    if (idx >= 0)
    {
        std::stringstream ss;
        ss << "Opponent's " << (idx + 1) << "th minion";
        return ss.str();
    }

    return "[UNKNOWN TARGET]";
}

void InteractiveShell::ShowBestNodeInfo(
    std::ostream& os, const TreeNode* mainNode,
    const ActionValidChecker& actionChecker, const TreeNode* node,
    const ActionApplyHelper& actionInfoGetter, int indent,
    bool onlyShowBestChoice)
{
    std::string indentPadding;
    for (int i = 0; i < indent; ++i)
    {
        indentPadding.append("   ");
    }

    std::int64_t totalChosenTime = 0;
    int bestChoice = -1;
    std::int64_t bestChoiceChosenTimes = 0;

    node->children.ForEach([&](int choice, const EdgeAddon* edgeAddon,
                               [[maybe_unused]] TreeNode* child) {
        if (edgeAddon)
        {
            const auto chosenTimes = edgeAddon->GetChosenTimes();
            totalChosenTime += chosenTimes;

            if (chosenTimes > bestChoiceChosenTimes)
            {
                bestChoiceChosenTimes = chosenTimes;
                bestChoice = choice;
            }
        }

        return true;
    });

    node->children.ForEach([&](int choice, const EdgeAddon* edgeAddon,
                               TreeNode* child) {
        if (onlyShowBestChoice)
        {
            if (choice != bestChoice)
            {
                return true;
            }
        }

        os << indentPadding << "Choice " << choice << ": "
           << GetChoiceString(mainNode, actionChecker, node, choice,
                              actionInfoGetter)
           << " " << GetChoiceSuggestionRate(node, choice, totalChosenTime)
           << std::endl;

        ActionApplyHelper newGetter = actionInfoGetter;
        newGetter.AppendChoice(choice);

        return ShowBestSubNodeInfo(os, mainNode, actionChecker, node, choice,
                                   totalChosenTime, edgeAddon, child, newGetter,
                                   indent + 1, onlyShowBestChoice);
    });
}

bool InteractiveShell::ShowBestSubNodeInfo(
    std::ostream& os, const TreeNode* mainNode,
    const ActionValidChecker& actionChecker,
    [[maybe_unused]] const TreeNode* node, [[maybe_unused]] int choice,
    [[maybe_unused]] std::uint64_t totalChosenTimes, const EdgeAddon* edgeAddon,
    TreeNode* child, const ActionApplyHelper& actionInfoGetter, int indent,
    bool onlyShowBestChoice)
{
    std::string indentPadding;
    for (int i = 0; i < indent; ++i)
    {
        indentPadding.append("   ");
    }

    if (!edgeAddon)
    {
        os << "[ERROR] Children of main action should with edge addon"
           << std::endl;
        return false;
    }

    if (!onlyShowBestChoice)
    {
        os << indentPadding
           << "Estimated win rate: " << edgeAddon->GetAverageCredit() * 100.0
           << "%" << std::endl;
    }

    if (child)
    {
        ShowBestNodeInfo(os, mainNode, actionChecker, child, actionInfoGetter,
                         indent, onlyShowBestChoice);
    }
    else
    {
        if (!onlyShowBestChoice)
        {
            Game game = m_startBoardGetter();
            std::tuple<PlayState, PlayState> result;
            auto dummyInfo = actionInfoGetter.ApplyChoices(game, result);

            auto& [p1Result, p2Result] = result;
            if (p1Result == PlayState::PLAYING ||
                p2Result == PlayState::PLAYING)
            {
                const double v = GetStateValue(game);
                os << indentPadding << "State-value: " << v << std::endl;
            }
        }
    }

    return true;
}

std::string InteractiveShell::GetChoiceString(
    [[maybe_unused]] const TreeNode* mainNode,
    const ActionValidChecker& actionChecker, const TreeNode* node, int choice,
    const ActionApplyHelper& actionInfoGetter)
{
    auto actionType = node->addon.consistencyChecker.GetActionType();
    if (actionType == ActionType::MAIN_ACTION)
    {
        auto op = actionChecker.GetMainOpType(choice);
        return GetMainOpString(op);
    }

    if (actionType == ActionType::CHOOSE_HAND_CARD)
    {
        const auto& playableCards = actionChecker.GetPlayableCards();
        return playableCards[choice]->card->id;
    }

    if (actionType == ActionType::CHOOSE_MINION_PUT_LOCATION)
    {
        auto v = actionInfoGetter.ApplyChoices(
            [&]() { return m_startBoardGetter(); });
        auto info = std::get<ActionApplyHelper::MinionPutLocationInfo>(v);
        std::stringstream ss;
        ss << "Put minion before index " << choice << " (total " << info.minions
           << ")";
        return ss.str();
    }

    if (actionType == ActionType::CHOOSE_ATTACKER)
    {
        std::stringstream ss;
        ss << "Attacker: " << choice;
        return ss.str();
    }

    if (actionType == ActionType::CHOOSE_TARGET)
    {
        auto v = actionInfoGetter.ApplyChoices(
            [&]() { return m_startBoardGetter(); });
        auto info = std::get<ActionApplyHelper::GetSpecifiedTargetInfo>(v);
        std::stringstream ss;
        ss << "Target at [" << GetTargetString(info.targets[choice]) << "]";
        return ss.str();
    }

    return "(unknown)";
}

void InteractiveShell::DoBest(std::istream& is, std::ostream& os)
{
    std::string verboseStr;
    if (is)
    {
        is >> verboseStr;
    }

    bool verbose;
    if (verboseStr == "-v")
    {
        verbose = true;
    }
    else if (verboseStr.empty())
    {
        verbose = false;
    }
    else
    {
        os << "Unknown option: " << verboseStr;
        return;
    }

    os << "Best action: " << std::endl;

    const Game game = m_startBoardGetter();
    ActionValidChecker checker;
    checker.Check(game);

    if (verbose)
    {
        double v = GetStateValue(game);
        os << "State-value: " << v << std::endl;
    }

    const auto node = m_controller->GetRootNode(PlayerType::PLAYER1);
    if (!node)
    {
        os << "[ERROR] no root node exists." << std::endl;
        return;
    }

    if (!node->addon.consistencyChecker.CheckActionType(
            ActionType::MAIN_ACTION))
    {
        os << "[ERROR] root node should be with type 'kMainAction'"
           << std::endl;
        return;
    }

    const ActionApplyHelper actionInfoGetter;
    ShowBestNodeInfo(os, node, checker, node, actionInfoGetter, 0, !verbose);
}

void InteractiveShell::DoRoot(std::istream& is, std::ostream& os)
{
    int v = 0;
    is >> v;

    PlayerType side;
    if (v == 1)
    {
        side = PlayerType::PLAYER1;
    }
    else if (v == 2)
    {
        side = PlayerType::PLAYER2;
    }
    else
    {
        os << "Invalid input" << std::endl;
        return;
    }

    m_node = m_controller->GetRootNode(side);
    os << "Current node set to: " << m_node << std::endl;
}
}  // namespace RosettaTorch::MCTS