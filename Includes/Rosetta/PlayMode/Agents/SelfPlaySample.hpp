// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_SELF_PLAY_SAMPLE_HPP
#define ROSETTASTONE_PLAYMODE_SELF_PLAY_SAMPLE_HPP

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>

#include <array>
#include <cstddef>
#include <cstdint>
#include <span>

namespace RosettaStone::PlayMode
{
class ReplayGame;
struct PUCTNode;

using VisitPolicy = std::array<float, PolicySchema::NUM_ACTIONS>;

//! Normalizes root action counts. Unvisited legal actions stay zero.
//! At least one legal action must have a visit.
VisitPolicy NormalizeVisitCounts(const PolicySchema::LegalMask& legalMask,
                                 std::span<const PUCTNode> rootActions);

//! Labels a decision using the absolute seat saved when it was observed.
//! An ongoing game has no training outcome.
float SelfPlayOutcome(const ReplayGame& game, PlayerType observationPlayer);
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_SELF_PLAY_SAMPLE_HPP
