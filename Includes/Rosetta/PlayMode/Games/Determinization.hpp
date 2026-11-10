// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_DETERMINIZATION_HPP
#define ROSETTASTONE_PLAYMODE_DETERMINIZATION_HPP

#include <Rosetta/PlayMode/Games/Observation.hpp>
#include <Rosetta/PlayMode/Games/ReplayGame.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode
{
//! One public decision, expressed using PolicySchema's visible zone slots.
//! Record publicAfter with EncodePublicObservation after applying the action.
//! Obtain opponent slots/targets from public events, not its legal actions.
struct PublicAction
{
    std::size_t actionIndex = 0;
    Observation publicAfter;
};

//! Knowledge supplied by the caller, not extracted from an omniscient game.
//! Fixed-deck MVP: deterministic history and ordinary top-of-deck draws.
//! Past effects must not depend on still-unknown card identities; inferred
//! constraints such as holding a Dragon are not represented.
struct FixedDeckInformationSet
{
    //! Public initial deck multisets and setup. Deck array order is ignored.
    //! Requires a concrete starting seat, no deck filling, and no mulligan.
    //! The caller is responsible for deck-construction validity.
    GameConfig config;
    //! Absolute seat making the root decision, and its current observation.
    PlayerType actingPlayer = PlayerType::INVALID;
    Observation observation;

    //! Absolute seats [PLAYER1, PLAYER2], then zero-based initial draw order.
    //! Positive dbfID for a known card, zero for unknown. Include all cards
    //! seen by the actor and all public reveals, even cards no longer in hand.
    //! Never populate this from the opponent's hidden hand or a real deck.
    std::array<std::array<int, START_DECK_SIZE>, 2> knownDraws{};
    //! Every decision since startup, in order.
    std::vector<PublicAction> history;
};

//! Samples unknown initial cards without replacement, then replays history.
//! Accepts no real Game, ReplayGame, hidden assignment, or gameplay RNG state.
//! The caller supplies an independent sampling RNG, advanced only on success.
//! Passing the ambient global RNG itself is rejected.
//! Returns a branchable game matching the observation and public checkpoints.
//! Decode search policy indices against the real root before applying them;
//! sampled entity IDs belong only to the sample.
//! Rejects secrets, quests, choices, casts-when-drawn, hand/deck triggers,
//! multi-triggers, new/transformed hand cards (except the startup Coin), and
//! deck additions or changes to remaining deck order or identities.
//! Random history requires outcome replay, deferred to #1070.
//! Throws std::invalid_argument for inconsistent/incomplete knowledge or
//! unsupported history. Does not modify the information set or global RNG.
//! Single-threaded, with the same reproducibility limits as ReplayGame.
std::unique_ptr<ReplayGame> SampleDeterminization(
    const FixedDeckInformationSet& information, Random::engine_type& random);
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_DETERMINIZATION_HPP
