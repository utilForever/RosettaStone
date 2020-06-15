// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_BATTLE_HPP
#define ROSETTASTONE_BATTLEGROUNDS_BATTLE_HPP

#include <Rosetta/Battlegrounds/Models/Player.hpp>
#include <Rosetta/Common/Enums/GameEnums.hpp>

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

    //! Initializes something before simulating a battle.
    //! i.e. decide who goes first, run hero powers
    void Initialize();

    //! Simulates a battle.
    void Run();

    //! Checks it is done.
    //! \return true if it is done, false otherwise.
    bool IsDone() const;

 private:
    Player& m_player1;
    Player& m_player2;
    FieldZone m_p1Field;
    FieldZone m_p2Field;

    std::size_t m_p1NextAttackerIdx = 0;
    std::size_t m_p2NextAttackerIdx = 0;

    Turn m_turn = Turn::DONE;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_BATTLE_HPP
