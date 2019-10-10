// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_AGENTS_MCTS_AGENT_HPP
#define ROSETTASTONE_TORCH_AGENTS_MCTS_AGENT_HPP

#include <Agents/MCTSConfig.hpp>
#include <Agents/MCTSRunner.hpp>
#include <MCTS/Selection/TreeNode.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaTorch::Agents
{
//!
//! \brief DummyAgentCallback class.
//!
//! This class is dummy class for MCTS agent.
//!
class DummyAgentCallback
{
 public:
    //! Default constructor.
    DummyAgentCallback() = default;

    //! Processes something before calling Think() method.
    void BeforeThink([[maybe_unused]] const BoardRefView& view)
    {
        // Do nothing
    }

    //! Processes something related to agent.
    //! \param iteration The number of iteration.
    void Think([[maybe_unused]] const BoardRefView& view,
               [[maybe_unused]] std::uint64_t iteration)
    {
        // Do nothing
    }

    //! Processes something after calling Think() method.
    //! \param iteration The number of iteration.
    void AfterThink([[maybe_unused]] std::uint64_t iteration)
    {
        // Do nothing
    }
};

//!
//! \brief MCTSAgent class.
//!
//! This class is simple agent to run MCTS runner.
//!
template <class AgentCallback = DummyAgentCallback>
class MCTSAgent
{
 public:
    //! Constructs MCTS agent with given \p config and \p callback.
    //! \param config The MCTS config.
    //! \param callback The agent callback.
    MCTSAgent(const MCTSConfig& config,
              AgentCallback callback = AgentCallback())
        : m_config(config), m_callback(callback)
    {
        // Do nothing
    }

    //! Deleted copy constructor.
    MCTSAgent(const MCTSAgent&) = delete;

    //! Deleted move constructor.
    MCTSAgent(MCTSAgent&&) noexcept = delete;

    //! Deleted copy assignment operator.
    MCTSAgent& operator=(const MCTSAgent&) = delete;

    //! Deleted move assignment operator.
    MCTSAgent& operator=(MCTSAgent&&) noexcept = delete;

    //! Process Think() related methods.
    //! \param gameState The board ref view to set game state.
    void Think(const BoardRefView& gameState)
    {
        m_callback.BeforeThink(gameState);

        m_controller.reset(new MCTSRunner(m_config));
        m_controller->Run(gameState);

        while (true)
        {
            const uint64_t iterations =
                m_controller->GetStatistics().GetSuccededIterates();
            m_callback.Think(gameState, iterations);

            if (iterations >=
                static_cast<uint64_t>(m_config.iterationsPerAction))
            {
                break;
            }

            std::this_thread::sleep_for(
                std::chrono::milliseconds(m_config.callbackInterval));
        }

        m_controller->WaitUntilStopped();

        m_callback.AfterThink(
            m_controller->GetStatistics().GetSuccededIterates());

        m_node = m_controller->GetRootNode(gameState.GetSide());
        m_rootNode = m_node;
    }

    //! Returns action according to \p actionType and \p choices.
    //! \param actionType The type of action.
    //! \param choices The choices of action.
    //! \return The index of chosen action.
    int GetAction(ActionType actionType, ActionChoices choices)
    {
        if (actionType != ActionType::MAIN_ACTION)
        {
            if (choices.Size() == 1)
            {
                return 0;
            }
        }

        if (!m_node->addon.consistencyChecker.LockAndCheckActionType(
                actionType))
        {
            throw std::runtime_error("Action type not match");
        }

        auto canBeChosen = [&](int choice) {
            for (choices.Begin(); !choices.IsEnd(); choices.StepNext())
            {
                if (static_cast<int>(choices.Get()) == choice)
                {
                    return true;
                }
            }

            return false;
        };

        struct Item
        {
            double value;
            int choice;
            const MCTS::TreeNode* node;
        };

        std::vector<Item> items;
        double totalValue = 0.0;

        double temperature = m_config.actionFollowTemperature;
        if (temperature < 0.1)
        {
            temperature = 0.1;
        }

        m_node->children.ForEach([&](int choice,
                                     const MCTS::EdgeAddon* edgeAddon,
                                     MCTS::TreeNode* child) {
            if (!canBeChosen(choice))
            {
                return true;
            }

            auto choiceValue = static_cast<double>(edgeAddon->GetChosenTimes());
            choiceValue = pow(choiceValue, 1.0 / temperature);
            totalValue += choiceValue;

            items.push_back({ choiceValue, choice, child });
            return true;
        });

        // Normalize
        double accumulated = 0.0;
        for (auto& item : items)
        {
            const double normalized = item.value / totalValue;
            accumulated += normalized;
            item.value = accumulated;
        }

        const auto v = Random::get<double>(0.0, accumulated);
        for (const auto& item : items)
        {
            if (v < item.value)
            {
                m_node = item.node;
                return item.choice;
            }
        }

        // If goes here, the only possible reason is we don't have any child
        // nodes no any choice is evaluated. randomly choose one.
        return Random::get<int>(0, choices.Size() - 1);
    }

 private:
    MCTSConfig m_config;
    const MCTS::TreeNode* m_rootNode = nullptr;
    const MCTS::TreeNode* m_node = nullptr;
    std::unique_ptr<MCTSRunner> m_controller = nullptr;
    AgentCallback m_callback;
};
}  // namespace RosettaTorch::Agents

#endif  // ROSETTASTONE_TORCH_AGENTS_MCTS_AGENT_HPP