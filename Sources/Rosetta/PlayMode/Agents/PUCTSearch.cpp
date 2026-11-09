// Copyright (c) 2026 Chris Ohk

#include <Rosetta/PlayMode/Agents/PUCTSearch.hpp>

#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

namespace RosettaStone::PlayMode
{
double PUCTNode::GetMeanValue() const
{
    return visitCount == 0 ? 0.0 : totalValue / visitCount;
}

PUCTSearch::PUCTSearch(PUCTSearchLimits limits, double exploration)
    : m_limits(limits), m_exploration(exploration)
{
    if (limits.maxSimulations == 0 || limits.maxDepth == 0 ||
        !std::isfinite(exploration) || exploration < 0.0)
    {
        throw std::invalid_argument(
            "Invalid PUCT search limits or exploration");
    }
}

std::size_t PUCTSearch::SelectChild(std::size_t parent) const
{
    const auto& node = m_nodes[parent];
    const double scale = std::sqrt(static_cast<double>(node.visitCount));
    double bestScore = -std::numeric_limits<double>::infinity();
    std::size_t best = node.children.front();

    for (const auto index : node.children)
    {
        const auto& child = m_nodes[index];
        const double mean = child.GetMeanValue();
        const double q = child.player == node.player ? mean : -mean;
        const double u =
            m_exploration * child.prior * (scale / (1.0 + child.visitCount));
        const double score = q + u;

        if (score > bestScore)
        {
            bestScore = score;
            best = index;
        }
    }

    return best;
}

std::optional<std::vector<std::size_t>> PUCTSearch::SelectLeaf()
{
    if (m_pending)
    {
        throw std::logic_error("Complete the pending PUCT leaf first");
    }

    while (m_nodes[0].visitCount < m_limits.maxSimulations &&
           !m_nodes[0].terminal)
    {
        m_path = { 0 };
        std::vector<std::size_t> actions;

        while (m_nodes[m_path.back()].expanded &&
               !m_nodes[m_path.back()].terminal &&
               actions.size() < m_limits.maxDepth)
        {
            const auto child = SelectChild(m_path.back());

            m_path.push_back(child);
            actions.push_back(m_nodes[child].actionIndex);
        }

        const auto& leaf = m_nodes[m_path.back()];

        if (!leaf.expanded)
        {
            m_pending = true;
            return actions;
        }

        Backup(leaf.evaluation);
    }

    return std::nullopt;
}

void PUCTSearch::CheckEvaluation(PlayerType player, double value) const
{
    if (!m_pending)
    {
        throw std::logic_error("Select a PUCT leaf before completing it");
    }

    if ((player != PlayerType::PLAYER1 && player != PlayerType::PLAYER2) ||
        !std::isfinite(value) || value < -1.0 || value > 1.0)
    {
        throw std::invalid_argument("Invalid PUCT player or value");
    }
}

void PUCTSearch::Expand(PlayerType player,
                        const PolicySchema::LegalMask& legalMask,
                        std::span<const float> priors, double value)
{
    CheckEvaluation(player, value);

    if (priors.size() != PolicySchema::NUM_ACTIONS)
    {
        throw std::invalid_argument("Invalid PUCT policy shape");
    }

    double total = 0.0;
    std::size_t count = 0;

    for (std::size_t action = 0; action < priors.size(); ++action)
    {
        if (legalMask[action] > 1 || !std::isfinite(priors[action]) ||
            priors[action] < 0.0f)
        {
            throw std::invalid_argument("Invalid PUCT mask or prior");
        }

        if (legalMask[action])
        {
            total += priors[action];
            ++count;
        }
    }

    if (count == 0)
    {
        throw std::invalid_argument(
            "A nonterminal PUCT leaf needs legal actions");
    }

    const auto leafIndex = m_path.back();
    std::vector<std::size_t> children;

    if (m_path.size() - 1 < m_limits.maxDepth)
    {
        children.reserve(count);

        for (std::size_t action = 0; action < priors.size(); ++action)
        {
            if (!legalMask[action])
            {
                continue;
            }

            PUCTNode child;
            child.actionIndex = action;
            child.prior = total > 0.0 ? priors[action] / total : 1.0 / count;

            children.push_back(m_nodes.size());
            m_nodes.push_back(std::move(child));
        }
    }

    auto& leaf = m_nodes[leafIndex];
    leaf.player = player;
    leaf.evaluation = value;
    leaf.expanded = true;
    leaf.children = std::move(children);

    Backup(value);
}

void PUCTSearch::SetTerminal(PlayerType player, double value)
{
    CheckEvaluation(player, value);

    auto& leaf = m_nodes[m_path.back()];
    leaf.player = player;
    leaf.evaluation = value;
    leaf.expanded = true;
    leaf.terminal = true;

    Backup(value);
}

void PUCTSearch::Backup(double value)
{
    const auto player = m_nodes[m_path.back()].player;

    for (const auto index : m_path)
    {
        auto& node = m_nodes[index];

        ++node.visitCount;
        node.totalValue += node.player == player ? value : -value;
    }

    m_pending = false;
}

std::optional<std::size_t> PUCTSearch::GetRootAction() const
{
    const auto& children = m_nodes[0].children;

    if (children.empty())
    {
        return std::nullopt;
    }

    auto best = children.front();

    for (const auto index : children)
    {
        const auto& child = m_nodes[index];
        const auto& current = m_nodes[best];

        if (child.visitCount > current.visitCount ||
            (child.visitCount == current.visitCount &&
             child.prior > current.prior))
        {
            best = index;
        }
    }

    return m_nodes[best].actionIndex;
}

const std::vector<PUCTNode>& PUCTSearch::GetNodes() const
{
    return m_nodes;
}
}  // namespace RosettaStone::PlayMode
