// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_REVENDRETH_CARDS_GEN_HPP
#define ROSETTASTONE_REVENDRETH_CARDS_GEN_HPP

#include <Rosetta/PlayMode/Cards/CardDef.hpp>

#include <map>
#include <string>

namespace RosettaStone::PlayMode
{
//!
//! \brief RevendrethCardsGen class.
//!
//! This structure adds REVENDRETH cards to the data storage with powers,
//! play requirements and entourages.
//!
class RevendrethCardsGen
{
 public:
    //! Adds hero cards to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddHeroes(std::map<std::string, CardDef>& cards);

    //! Adds hero power cards to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddHeroPowers(std::map<std::string, CardDef>& cards);

    //! Adds druid cards that are collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddDruid(std::map<std::string, CardDef>& cards);

    //! Adds druid cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddDruidNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds hunter cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddHunter(std::map<std::string, CardDef>& cards);

    //! Adds hunter cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddHunterNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds mage cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddMage(std::map<std::string, CardDef>& cards);

    //! Adds mage cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddMageNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds paladin cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddPaladin(std::map<std::string, CardDef>& cards);

    //! Adds paladin cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddPaladinNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds priest cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddPriest(std::map<std::string, CardDef>& cards);

    //! Adds priest cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddPriestNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds rogue cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddRogue(std::map<std::string, CardDef>& cards);

    //! Adds rogue cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddRogueNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds shaman cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddShaman(std::map<std::string, CardDef>& cards);

    //! Adds shaman cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddShamanNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds warlock cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddWarlock(std::map<std::string, CardDef>& cards);

    //! Adds warlock cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddWarlockNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds warrior cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddWarrior(std::map<std::string, CardDef>& cards);

    //! Adds warrior cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddWarriorNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds demon hunter cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddDemonHunter(std::map<std::string, CardDef>& cards);

    //! Adds demon hunter cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddDemonHunterNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds neutral cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddNeutral(std::map<std::string, CardDef>& cards);

    //! Adds neutral cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddNeutralNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds all cards to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddAll(std::map<std::string, CardDef>& cards);
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_REVENDRETH_CARDS_GEN_HPP