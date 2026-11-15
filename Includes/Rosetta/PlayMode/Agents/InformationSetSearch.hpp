// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_INFORMATION_SET_SEARCH_HPP
#define ROSETTASTONE_PLAYMODE_INFORMATION_SET_SEARCH_HPP

#include <Rosetta/PlayMode/Agents/BatchedEvaluator.hpp>
#include <Rosetta/PlayMode/Agents/PUCTSearch.hpp>
#include <Rosetta/PlayMode/Games/Determinization.hpp>

namespace RosettaStone::PlayMode
{
//! Root statistics in the root actor's perspective, sorted by policy index.
//! Actions aggregate all sampled outcomes; their children are not exported
//! and terminal/evaluation/expanded fields are unused. The initial root
//! evaluation counts as a visit but does not visit an action.
struct InformationSetSearchResult
{
    std::size_t visitCount = 0;
    std::vector<PUCTNode> actions;

    //! Most visits, then highest prior, then lowest policy index.
    std::optional<std::size_t> GetRootAction() const;
};

//! Sequential root-sampling search.
//! Each simulation samples one hidden assignment and follows one outcome of
//! each random effect. Each player has a tree keyed by their own observation
//! history, public actions, graveyards and legal masks. Opponent private
//! observations never enter that player's tree. No actual Game or hidden
//! assignment is accepted as input. Uses the same PUCT score, limits and tie
//! rules as PUCTSearch. Evaluation uses singleton batches; terminal rewards
//! bypass the evaluator. Same-player actions preserve values, while opponent
//! decisions negate them on backup. A seed generator advances once per
//! simulation; sampling and gameplay use simulation-local engines. Neither can
//! consume another simulation's stream. Root indices must be decoded against
//! the real decision before application. Rebuild for each decision.
//! FixedDeckInformationSet and observation/policy restrictions apply;
//! unsupported states throw, without returning a result. Single-threaded, with
//! ReplayGame's same-build reproducibility limits and a deterministic
//! evaluator.
InformationSetSearchResult SearchInformationSet(
    const FixedDeckInformationSet& information, BatchedEvaluator& evaluator,
    PUCTSearchLimits limits, unsigned int seed, double exploration = 1.0);
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_INFORMATION_SET_SEARCH_HPP
