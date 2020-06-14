// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_BATTLE_HPP
#define ROSETTASTONE_BATTLEGROUNDS_BATTLE_HPP

#include <Rosetta/Battlegrounds/Models/Player.hpp>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Battle class.
//!
//! In the Combat Phase, you enter combat with another player, facing off
//! against their board. There is no player input on this part of the game,
//! simply letting numbers, strategy, and a bit of luck play out.
//!
class Battle
{
 public:
    //! Constructs Battle instance with given \p player1 and \p player2.
    //! \param player1 The first player.
    //! \param player2 The second player.
    Battle(Player& player1, Player& player2);

    //! Simulates a battle.
    void Run();

 private:
    Player& m_player1;
    Player& m_player2;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_BATTLE_HPP
