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
#include <Rosetta/Views/Types/UnknownCards.hpp>

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
    int health;
    int maxHealth;
    int armor;
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

    std::string cardID;
    bool isExhausted;
};

//!
//! \brief ManaCrystal struct.
//!
struct ManaCrystal
{
    void Parse(int usedMana, int totalMana, int overloadOwedMana,
               int overloadLockedMana);

    int used;
    int total;
    int overloadOwed;
    int overloadLocked;
};

//!
//! \brief Minion struct.
//!
struct Minion
{
    void Parse(const RosettaStone::Minion& minion);

    std::string cardID;
    int attack;
    int health;
    int maxHealth;
    int spellPower;
    bool isExhausted;
};

//!
//! \brief Minions struct.
//!
struct Minions
{
    void Parse(BoardRefView gameState, PlayerType side);

    std::vector<Minion> minions;
};

//!
//! \brief Player struct.
//!
struct Player
{
    void Parse(BoardRefView gameState, PlayerType side,
               UnknownCardsInfo& unknownCardsInfo);

    Hero hero;
    HeroPower heroPower;
    ManaCrystal manaCrystal;
    Minions minions;
    int fatigue;

    std::vector<CardInfo> hand;
    std::vector<CardInfo> deck;

 private:
    CardInfo ParseCardInfo(const std::string& cardID, int blockID,
                           UnknownCardsInfo& unknownCardsInfo);

    template <class CardsGetter>
    std::size_t GetUnknownCardSetID(int blockIdx, CardsGetter&& cardsGetter,
                                    UnknownCardsInfo& unknownCardsInfo)
    {
        auto& setsIndices = unknownCardsInfo.setsIndices;
        auto iter = setsIndices.find(blockIdx);

        if (iter == setsIndices.end())
        {
            std::size_t setIdx =
                unknownCardsInfo.unknownCardsSets.AddCardsSet(cardsGetter());
            setsIndices.insert(std::make_pair(blockIdx, setIdx));
            return setIdx;
        }

        return iter->second;
    }
};
}  // namespace RosettaStone::Views::Types

#endif  // ROSETTASTONE_VIEWS_TYPES_PLAYER_HPP
