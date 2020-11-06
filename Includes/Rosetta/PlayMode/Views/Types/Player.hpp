// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_VIEWS_TYPES_PLAYER_HPP
#define ROSETTASTONE_PLAYMODE_VIEWS_TYPES_PLAYER_HPP

#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Views/BoardRefView.hpp>
#include <Rosetta/PlayMode/Views/Types/CardInfo.hpp>
#include <Rosetta/PlayMode/Views/Types/UnknownCards.hpp>

namespace RosettaStone::PlayMode::Views::Types
{
//!
//! \brief Hero struct.
//!
//! This struct stores the information of the hero.
//!
struct Hero
{
    //! Parses the information of the hero.
    //! \param gameState The board ref view.
    //! \param side The side of the hero.
    void Parse(BoardRefView gameState, PlayerType side);

    std::string cardID;
    int attack = 0;
    int damage = 0;
    int baseHealth = 0;
    int armor = 0;
    bool isExhausted = false;

 private:
    //! Parses the information of the hero.
    //! \param hero The hero context.
    void Parse(PlayMode::Hero* hero);
};

//!
//! \brief HeroPower struct.
//!
//! This struct stores the information of the hero power.
//!
struct HeroPower
{
    //! Parses the information of the hero power.
    //! \param gameState The board ref view.
    //! \param side The side of the hero power.
    void Parse(BoardRefView gameState, PlayerType side);

    std::string cardID;
    bool isExhausted = false;
};

//!
//! \brief ManaCrystal struct.
//!
//! This struct stores the information of the mana crystal.
//!
struct ManaCrystal
{
    //! Parses the information of the mana crystal.
    //! \param usedMana The value of the used mana crystal.
    //! \param totalMana The value of the total mana crystal.
    //! \param overloadOwedMana The value of the overload owed mana crystal.
    //! \param overloadLockedMana The value of the overload locked mana crystal.
    void Parse(int usedMana, int totalMana, int overloadOwedMana,
               int overloadLockedMana);

    int used = 0;
    int total = 0;
    int overloadOwed = 0;
    int overloadLocked = 0;
};

//!
//! \brief Minion struct.
//!
//! This struct stores the information of the minion.
//!
struct Minion
{
    //! Parses the information of the minion.
    //! \param minion The minion context.
    void Parse(const PlayMode::Minion& minion);

    std::string cardID;
    int attack = 0;
    int damage = 0;
    int baseHealth = 0;
    int spellPower = 0;
    bool isExhausted = false;
};

//!
//! \brief Minions struct.
//!
//! This struct stores the information of a list of minion.
//!
struct Minions
{
    //! Parses the information of a list of minion.
    //! \param gameState The board ref view.
    //! \param side The side of the a list of minion.
    void Parse(BoardRefView gameState, PlayerType side);

    std::vector<Minion> minions;
};

//!
//! \brief Player struct.
//!
//! This struct stores the information of the player.
//!
struct Player
{
    //! Parses the information of the player.
    //! \param gameState The board ref view.
    //! \param side The side of the player.
    //! \param unknownCardsInfo The information of unknown cards.
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
    //! Parse the information of the card.
    //! \param cardID The card ID.
    //! \param blockID The constant ID to block information.
    //! \param unknownCardsInfo The information of unknown cards.
    //! \return The parsed information of the card.
    CardInfo ParseCardInfo(const std::string& cardID, int blockID,
                           UnknownCardsInfo& unknownCardsInfo);

    //! Returns the unknown card set ID.
    //! \param blockIdx An index to block information.
    //! \param cardsGetter A function to get a list of card.
    //! \param unknownCardsInfo The information of unknown cards.
    //! \return The unknown card set ID.
    template <class CardsGetter>
    std::size_t GetUnknownCardSetID(int blockIdx, CardsGetter&& cardsGetter,
                                    UnknownCardsInfo& unknownCardsInfo)
    {
        auto& setsIndices = unknownCardsInfo.setsIndices;
        const auto iter = setsIndices.find(blockIdx);

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
}  // namespace RosettaStone::PlayMode::Views::Types

#endif  // ROSETTASTONE_PLAYMODE_VIEWS_TYPES_PLAYER_HPP
