// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Agents/MCTSAgent.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaTorch::Agents
{
MCTSAgent::MCTSAgent(const MCTSConfig& config, IAgent& agent)
    : m_config(config), m_agent(agent)
{
    // Do nothing
}

void MCTSAgent::Think(const GameConfig& gameConfig)
{
    m_agent.BeforeThink();

    m_controller.reset(new MCTSRunner(m_config));
    m_controller->Run(gameConfig);

    while (true)
    {
        const uint64_t iterations =
            m_controller->GetStatistics().GetSuccededIterates();
        m_agent.Think(iterations);

        if (iterations >= static_cast<uint64_t>(m_config.iterationsPerAction))
        {
            break;
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(m_config.callbackInterval));
    }

    m_controller->WaitUntilStopped();

    m_agent.AfterThink(m_controller->GetStatistics().GetSuccededIterates());

    m_node = m_controller->GetRootNode(gameConfig.startPlayer);
    m_rootNode = m_node;
}

int MCTSAgent::GetAction(ActionType actionType, ActionChoices choices)
{
    if (actionType != ActionType::MAIN_ACTION)
    {
        if (choices.Size() == 1)
        {
            return 0;
        }
    }

    if (!m_node->addon.consistencyChecker.SetAndCheckActionType(actionType))
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

    m_node->children.ForEach([&](int choice, const MCTS::EdgeAddon* edgeAddon,
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

    // If goes here, the only possible reason is we don't have any child nodes
    // no any choice is evaluated. randomly choose one.
    return Random::get<int>(0, choices.Size() - 1);
}
}  // namespace RosettaTorch::Agents