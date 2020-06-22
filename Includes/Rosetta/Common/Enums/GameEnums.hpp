// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_GAME_ENUMS_HPP
#define ROSETTASTONE_GAME_ENUMS_HPP

namespace RosettaStone
{
namespace PlayMode
{
//! \brief An enumerator for identifying the player.
enum class PlayerType
{
    INVALID,  //!< The invalid player.
    RANDOM,   //!< The random player.
    PLAYER1,  //!< The first player.
    PLAYER2,  //!< The second player.
};
}  // namespace PlayMode

namespace Battlegrounds
{
//! \brief An enumerator for identifying the phase.
enum class Phase
{
    INVALID,
    SELECT_HERO,
    RECRUIT,
    COMBAT,
    GAMEOVER,
    COMPLETE
};

//! \brief An enumerator for identifying the turn in battle.
enum class Turn
{
    PLAYER1,  //!< The first player.
    PLAYER2,  //!< The second player.
    DONE,     //!< The battle is done.
};

//! \brief An enumerator for identifying the result of battle.
enum class BattleResult
{
    PLAYER1_WIN,  //!< Player 1 win.
    PLAYER2_WIN,  //!< Player 2 win.
    DRAW,         //!< Draw.
};
}  // namespace Battlegrounds
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GAME_ENUMS_HPP
