// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_PLAYMODE_PLAYER_ACTION_HPP
#define ROSETTASTONE_PLAYMODE_PLAYER_ACTION_HPP

#include <compare>

namespace RosettaStone::PlayMode
{
//! Semantic decisions, independent of policy indices or runtime pointers.
enum class PlayerActionType
{
    END_TURN,
    PLAY_CARD,
    ATTACK,
    HERO_POWER,
    CHOOSE
};

//! A decision in a particular game state. Entity IDs are local to that game
//! and equivalent replay branches, not card IDs or persistent global IDs.
//! Unused IDs and positions are -1; unused Choose One options are zero.
struct PlayerAction
{
    PlayerActionType type = PlayerActionType::END_TURN;

    int sourceID = -1;
    int targetID = -1;
    //! Zero-based insertion slot for minions and locations; otherwise -1.
    int fieldPos = -1;
    //! One-based Choose One option; zero also represents Choose Both.
    int chooseOne = 0;
    //! Offered entity ID for a pending general choice.
    int choiceID = -1;

    //! Lexicographic comparison by type, sourceID, targetID, fieldPos,
    //! chooseOne, and choiceID.
    auto operator<=>(const PlayerAction&) const = default;
};

}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_PLAYER_ACTION_HPP
