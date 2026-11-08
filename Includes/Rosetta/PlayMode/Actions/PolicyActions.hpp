// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_POLICY_ACTIONS_HPP
#define ROSETTASTONE_PLAYMODE_POLICY_ACTIONS_HPP

#include <Rosetta/PlayMode/Actions/PlayerAction.hpp>
#include <Rosetta/PlayMode/Games/Observation.hpp>

#include <map>

namespace RosettaStone::PlayMode
{
//! Fixed, player-relative policy layout; see Documents/PolicyActions.md.
namespace PolicySchema
{
inline constexpr std::int32_t VERSION = 1;
inline constexpr std::int32_t OBSERVATION_VERSION = 1;
static_assert(ObservationSchema::VERSION == OBSERVATION_VERSION);

inline constexpr std::size_t CHARACTER_SLOTS =
    1 + ObservationSchema::BOARD_SLOTS;
inline constexpr std::size_t TARGET_SLOTS = 1 + 2 * CHARACTER_SLOTS;
inline constexpr std::size_t POSITION_SLOTS = ObservationSchema::BOARD_SLOTS;
inline constexpr std::size_t OPTION_SLOTS = ObservationSchema::CHOICE_SLOTS;

inline constexpr std::size_t END_TURN = 0;
inline constexpr std::size_t PLAY_CARD = END_TURN + 1;
inline constexpr std::size_t ATTACK =
    PLAY_CARD + ObservationSchema::HAND_SLOTS * TARGET_SLOTS * POSITION_SLOTS *
                    OPTION_SLOTS;
inline constexpr std::size_t HERO_POWER =
    ATTACK + CHARACTER_SLOTS * CHARACTER_SLOTS;
inline constexpr std::size_t CHOOSE = HERO_POWER + TARGET_SLOTS;
inline constexpr std::size_t NUM_ACTIONS =
    CHOOSE + ObservationSchema::CHOICE_SLOTS;

using LegalMask = std::array<std::uint8_t, NUM_ACTIONS>;
}  // namespace PolicySchema

//! Immutable mapping for one decision. Rebuild after any game mutation.
//! Retains semantic values, not game pointers; indices use visible slot order.
//! A 1 in the mask means legal. Only exact enumerated actions can be encoded.
class PolicyActions
{
 public:
    //! Enumerates once without executing tasks or advancing the game.
    //! No decision (including terminal/mulligan states) gives an all-zero mask.
    //! Throws std::invalid_argument if legal actions exceed the v1 layout.
    //! This maps Phase 1 actions; it does not validate observation support.
    explicit PolicyActions(const Game& game);

    //! Returns the index of an exact legal semantic action in this snapshot.
    //! Throws std::invalid_argument for illegal/noncanonical actions.
    std::size_t Encode(const PlayerAction& action) const;

    //! Returns the original semantic action, including all game-local IDs.
    //! Throws std::invalid_argument for masked or out-of-range indices.
    PlayerAction Decode(std::size_t index) const;

    //! Returns the fixed-size binary mask in ascending policy-index order.
    const PolicySchema::LegalMask& GetLegalMask() const;

 private:
    std::map<std::size_t, PlayerAction> m_actions;
    PolicySchema::LegalMask m_mask{};
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_POLICY_ACTIONS_HPP
