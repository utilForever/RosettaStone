// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_PUCT_SEARCH_HPP
#define ROSETTASTONE_PLAYMODE_PUCT_SEARCH_HPP

#include <Rosetta/Common/Enums/GameEnums.hpp>
#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>

#include <optional>
#include <span>

namespace RosettaStone::PlayMode
{
//! Both limits must be positive. Root evaluation counts as one simulation;
//! depth counts actions from the root. Cutoffs reuse the leaf evaluation.
struct PUCTSearchLimits
{
    std::size_t maxSimulations;
    std::size_t maxDepth;
};

//! Statistics use this node's player perspective, including terminal nodes.
//! Child entries are indices into PUCTSearch::GetNodes(), sorted by action.
//! Unevaluated nodes have INVALID player and zero visits/mean value.
struct PUCTNode
{
    std::size_t actionIndex = PolicySchema::NUM_ACTIONS;
    PlayerType player = PlayerType::INVALID;
    double prior = 0.0;
    std::size_t visitCount = 0;
    double totalValue = 0.0;
    double evaluation = 0.0;
    bool expanded = false;
    bool terminal = false;
    std::vector<std::size_t> children;

    double GetMeanValue() const;
};

//! Sequential, backend-independent PUCT mechanics for one root decision.
//! Owns no game state and consumes no randomness. The caller supplies each
//! selected leaf's actor, legal mask, policy weights, and player-relative
//! value.
//! Inputs must describe a deterministic tree; rebuild for each root decision.
//! Selection and backup preserve values for the same player and negate them
//! for the opponent; actions need not alternate players.
class PUCTSearch
{
 public:
    //! Exploration must be finite and nonnegative; invalid inputs throw
    //! std::invalid_argument. Limits are explicit to keep search bounded.
    explicit PUCTSearch(PUCTSearchLimits limits, double exploration = 1.0);

    //! Maximizes Q + exploration * P * sqrt(N_parent) / (1 + N_child).
    //! Q is the child's mean in the parent's perspective (zero if unvisited);
    //! P is its normalized prior. Exact ties use the lowest policy index.
    //! Returns policy indices along the next unevaluated root-to-leaf path.
    //! Decode each index with PolicyActions for that step's state.
    //! The first path is empty (root). Cached terminal/cutoff visits are
    //! backed up internally. Returns nullopt at the budget or a terminal root.
    //! Complete the pending leaf before selecting again (std::logic_error).
    std::optional<std::vector<std::size_t>> SelectLeaf();

    //! Expands the pending leaf using only legal actions, then backs up value.
    //! Priors must have NUM_ACTIONS finite, nonnegative weights. Legal weights
    //! are normalized; all-zero legal weights use a uniform distribution.
    //! Mask entries must be 0/1 with at least one legal action. Player must be
    //! PLAYER1/PLAYER2 and value finite in [-1, 1]. Invalid inputs throw
    //! std::invalid_argument without completing or changing the pending leaf.
    void Expand(PlayerType player, const PolicySchema::LegalMask& legalMask,
                std::span<const float> priors, double value);

    //! Completes the pending leaf with a terminal reward in [-1, 1], relative
    //! to the explicit player (PLAYER1/PLAYER2); no children are created.
    void SetTerminal(PlayerType player, double value);

    //! Most visits, then highest prior, then lowest policy index. No action
    //! before root expansion or at a terminal root. Legal even with no visits.
    std::optional<std::size_t> GetRootAction() const;

    //! Root is index 0. Indices are stable; references may be invalidated by
    //! expansion. Statistics are read-only through this accessor.
    const std::vector<PUCTNode>& GetNodes() const;

 private:
    std::size_t SelectChild(std::size_t parent) const;
    void CheckEvaluation(PlayerType player, double value) const;
    void Backup(double value);

    PUCTSearchLimits m_limits;
    double m_exploration;
    std::vector<PUCTNode> m_nodes{ 1 };
    std::vector<std::size_t> m_path;
    bool m_pending = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_PUCT_SEARCH_HPP
