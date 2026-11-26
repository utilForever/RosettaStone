// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_SELF_PLAY_SAMPLE_HPP
#define ROSETTASTONE_PLAYMODE_SELF_PLAY_SAMPLE_HPP

#include <Rosetta/PlayMode/Actions/PolicyActions.hpp>

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <span>
#include <string>
#include <string_view>

namespace RosettaStone::PlayMode
{
class ReplayGame;
struct PUCTNode;

using VisitPolicy = std::array<float, PolicySchema::NUM_ACTIONS>;

//! Checks the probability range and exact row sum against the sample v1 bounds.
bool IsNormalizedVisitPolicy(std::span<const float> policy);
bool IsNormalizedVisitPolicy(std::span<const double> policy);

//! Normalizes root action counts. Unvisited legal actions stay zero.
//! At least one legal action must have a visit.
VisitPolicy NormalizeVisitCounts(const PolicySchema::LegalMask& legalMask,
                                 std::span<const PUCTNode> rootActions);

//! Labels a decision using the absolute seat saved when it was observed.
//! An ongoing game has no training outcome.
float SelfPlayOutcome(const ReplayGame& game, PlayerType observationPlayer);

//! One finalized decision. See Documents/RosettaRL.md for the wire layout.
struct SelfPlaySample
{
    static constexpr std::string_view MAGIC = "RSSP";
    static constexpr std::uint32_t VERSION = 1;
    static constexpr std::uint32_t POLICY_SUM_SCALE = 100'000;
    static constexpr double POLICY_SUM_TOLERANCE = 1.0 / POLICY_SUM_SCALE;
    static constexpr std::size_t BYTE_SIZE =
        MAGIC.size() + 2 * 4 + ObservationSchema::FLAT_SIZE * 4 +
        PolicySchema::NUM_ACTIONS * (1 + 4) + 4;

    ObservationSchema::Flat observation{};
    PolicySchema::LegalMask legalMask{};
    VisitPolicy policyTarget{};
    float outcome = std::numeric_limits<float>::quiet_NaN();

    //! Both directions validate before returning, throwing
    //! std::invalid_argument.
    std::string Serialize() const;
    static SelfPlaySample Deserialize(std::string_view bytes);
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_SELF_PLAY_SAMPLE_HPP
