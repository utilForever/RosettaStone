// Copyright (c) 2026 Chris Ohk

#include <Rosetta/PlayMode/Agents/InformationSetSearch.hpp>

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace RosettaStone::PlayMode
{
namespace
{
struct ObservedStep
{
    PlayerType player;
    Observation observation;
    std::array<std::vector<int>, 2> graveyards;
    std::size_t action = PolicySchema::NUM_ACTIONS;
    int playedCard = 0;

    bool operator==(const ObservedStep&) const = default;
};

struct Decision
{
    PlayerType player;
    std::vector<ObservedStep> history;
    EvaluationInput input;
    double value;
    std::size_t visits = 0;
    std::vector<PUCTNode> actions;
};

std::unique_ptr<Decision> Expand(PlayerType player,
                                 const std::vector<ObservedStep>& history,
                                 EvaluationInput input,
                                 BatchedEvaluator& evaluator)
{
    const auto result = evaluator.Evaluate({ &input, 1 }).front();
    auto decision = std::make_unique<Decision>();

    decision->player = player;
    decision->history = history;
    decision->input = std::move(input);
    decision->value = result.value;

    for (std::size_t index = 0; index < PolicySchema::NUM_ACTIONS; ++index)
    {
        if (decision->input.legalMask[index])
        {
            PUCTNode statistics;
            statistics.actionIndex = index;
            statistics.player = player;
            statistics.prior = result.priors[index];

            decision->actions.push_back(statistics);
        }
    }

    return decision;
}
}  // namespace

std::optional<std::size_t> InformationSetSearchResult::GetRootAction() const
{
    if (actions.empty())
    {
        return std::nullopt;
    }

    const auto best = std::ranges::max_element(
        actions, [](const auto& left, const auto& right) {
            if (left.visitCount != right.visitCount)
            {
                return left.visitCount < right.visitCount;
            }

            if (left.prior != right.prior)
            {
                return left.prior < right.prior;
            }

            return left.actionIndex > right.actionIndex;
        });

    return best->actionIndex;
}

InformationSetSearchResult SearchInformationSet(
    const FixedDeckInformationSet& information, BatchedEvaluator& evaluator,
    PUCTSearchLimits limits, unsigned int seed, double exploration)
{
    if (limits.maxSimulations == 0 || limits.maxDepth == 0 ||
        !std::isfinite(exploration) || exploration < 0.0)
    {
        throw std::invalid_argument(
            "Invalid PUCT search limits or exploration");
    }

    Random::engine_type seeds(seed);
    std::array<std::vector<std::unique_ptr<Decision>>, 2> trees;
    Decision* root = nullptr;

    for (std::size_t simulation = 0; simulation < limits.maxSimulations;
         ++simulation)
    {
        Random::engine_type sampling(seeds());

        auto game = SampleDeterminization(information, sampling);
        std::vector<Decision*> decisions;
        std::vector<PUCTNode*> actions;
        std::array<std::vector<ObservedStep>, 2> histories;
        PlayerType valuePlayer = information.actingPlayer;
        double value = 0.0;

        for (std::size_t depth = 0;; ++depth)
        {
            if (game->GetOutcome(information.actingPlayer) !=
                PlayState::PLAYING)
            {
                value = game->GetReward(information.actingPlayer);
                break;
            }

            const auto player = game->GetCurrentPlayer()->playerType;
            const PolicyActions policy(game->GetGame());
            EvaluationInput input{ EncodeObservation(game->GetGame()),
                                   policy.GetLegalMask() };
            const auto publicState =
                EncodePublicAction(game->GetGame(), PolicySchema::END_TURN);
            const std::size_t seat = player == PlayerType::PLAYER1 ? 0 : 1;

            // Each player's tree remembers only that player's private views.
            histories[seat].push_back(
                { player, input.observation, publicState.graveyardsAfter });
            histories[1 - seat].push_back({ player, publicState.publicAfter,
                                            publicState.graveyardsAfter });

            const auto matches = [&](const auto& decision) {
                return decision->history == histories[seat] &&
                       decision->input.legalMask == input.legalMask;
            };

            if (depth == 0 && root &&
                (root->player != player ||
                 root->input.observation != input.observation ||
                 root->input.legalMask != input.legalMask))
            {
                throw std::invalid_argument(
                    "Determinizations disagree on the root decision");
            }

            auto& tree = trees[seat];
            const auto found = std::ranges::find_if(tree, matches);
            const bool expanded = found == tree.end();
            Decision* decision;

            if (expanded)
            {
                tree.push_back(Expand(player, histories[seat], std::move(input),
                                      evaluator));
                decision = tree.back().get();
            }
            else
            {
                decision = found->get();
            }

            if (depth == 0)
            {
                root = decision;
            }

            decisions.push_back(decision);

            if (expanded || depth == limits.maxDepth)
            {
                valuePlayer = player;
                value = decision->value;
                break;
            }

            const auto best = std::ranges::max_element(
                decision->actions, [&](const auto& left, const auto& right) {
                    return left.GetSelectionScore(player, decision->visits,
                                                  exploration) <
                           right.GetSelectionScore(player, decision->visits,
                                                   exploration);
                });

            actions.push_back(&*best);

            const auto action = policy.Decode(best->actionIndex);
            const auto* card =
                action.type == PlayerActionType::PLAY_CARD
                    ? game->GetGame().entityList.at(action.sourceID)->card
                    : nullptr;
            const int playedCard = card && !card->IsSecret() ? card->dbfID : 0;

            for (auto& history : histories)
            {
                history.back().action = best->actionIndex;
                history.back().playedCard = playedCard;
            }

            game->ApplyAction(action);
        }

        for (auto* decision : decisions)
        {
            ++decision->visits;
        }

        for (auto* action : actions)
        {
            auto& statistics = *action;
            ++statistics.visitCount;
            statistics.totalValue +=
                statistics.player == valuePlayer ? value : -value;
        }
    }

    if (!root)
    {
        throw std::logic_error("Information-set search has no root decision");
    }

    InformationSetSearchResult result;
    result.visitCount = root->visits;
    result.actions = std::move(root->actions);

    return result;
}
}  // namespace RosettaStone::PlayMode
