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
    //! Constructs Battle instance with given game context and players.
    //! \param player1 The first player.
    //! \param player2 The second player.
    Battle(Player& player1, Player& player2);

    //! Initializes something before simulating a battle.
    //! i.e. decide who goes first, run hero powers
    void Initialize();

    //! Simulates a battle.
    void Run();

    //! Attacks one of the opponent minions.
    //! \return The flag that indicates the attacker does attack.
    bool Attack();

    //! Finds the attacker.
    //! \return The positive index if the attacker is found, -1 otherwise.
    int FindAttacker();

    //! Gets a proper target according to \p attacker.
    //! \param attacker The attacker.
    //! \return A proper target.
    Minion& GetProperTarget(Minion& attacker);

    //! Processes a list of minions that are destroyed.
    //! \param beforeAttack The flag that indicates it is called before attack.
    void ProcessDestroy(bool beforeAttack);

    //! Checks it is done.
    //! \return true if it is done, false otherwise.
    bool IsDone() const;

    //! Processes the result.
    void ProcessResult();

    //! Calculates the total damage according to the result.
    //! \return The total damage according to the result.
    int CalculateDamage();

    //! Returns the field zone of player 1.
    //! \return The field zone of player 1.
    const FieldZone& GetPlayer1Field() const;

    //! Returns the field zone of player 2.
    //! \return The field zone of player 2.
    const FieldZone& GetPlayer2Field() const;

    //! Returns the index of next attacker of player 1.
    //! \return The index of next attacker of player 1.
    int GetPlayer1NextAttacker() const;

    //! Returns the index of next attacker of player 2.
    //! \return The index of next attacker of player 2.
    int GetPlayer2NextAttacker() const;

    //! Returns the result of battle.
    //! \return The result of battle.
    BattleResult GetResult() const;

 private:
    Player& m_player1;
    Player& m_player2;
    FieldZone& m_p1Field;
    FieldZone& m_p2Field;

    int m_p1NextAttackerIdx = 0;
    int m_p2NextAttackerIdx = 0;

    Turn m_turn = Turn::DONE;
    BattleResult m_result = BattleResult::DRAW;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_BATTLE_HPP
