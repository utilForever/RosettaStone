// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_VIEWS_TYPES_PLAYER_HPP
#define ROSETTASTONE_VIEWS_TYPES_PLAYER_HPP

#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Views/BoardRefView.hpp>
#include <Rosetta/Views/Types/CardInfo.hpp>

namespace RosettaStone::Views::Types
{
//!
//! \brief Hero struct.
//!
struct Hero
{
    void Parse(BoardRefView gameState, PlayerType side);

    std::string cardID;
    int attack;
    int armor;
    int damage;
    int maxHealth;
    bool isExhausted;

 private:
    void Parse(RosettaStone::Hero* hero);
};

//!
//! \brief HeroPower struct.
//!
struct HeroPower
{
    void Parse(BoardRefView gameState, PlayerType side);
};

//!
//! \brief ManaCrystal struct.
//!
struct ManaCrystal
{
    void Parse(int remainingMana, int totalMana, int overloadOwedMana,
               int overloadLockedMana);
};

//!
//! \brief Minions struct.
//!
struct Minions
{
    void Parse(BoardRefView gameState, PlayerType side);
};

//!
//! \brief Player struct.
//!
struct Player
{
    void Parse(BoardRefView gameState, PlayerType side);

    Hero hero;
    HeroPower heroPower;
    ManaCrystal manaCrystal;
    Minions minions;
    int fatigue;

    std::vector<CardInfo> hand;
    std::vector<CardInfo> deck;
};
}  // namespace RosettaStone::Views::Types

#endif  // ROSETTASTONE_VIEWS_TYPES_PLAYER_HPP
