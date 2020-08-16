// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_BATTLEGROUNDS_CARDS_GEN_HPP
#define ROSETTASTONE_BATTLEGROUNDS_BATTLEGROUNDS_CARDS_GEN_HPP

#include <Rosetta/Battlegrounds/Cards/CardDef.hpp>

#include <map>
#include <string>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief BattlegroundsCardsGen class.
//!
//! This structure adds BATTLEGROUNDS cards to the data storage with powers.
//!
class BattlegroundsCardsGen
{
 public:
    //! Adds hero cards to \p cards.
    //! \param cards A list of cards to store the data such as powers.
    static void AddHeroes(std::map<std::string, CardDef>& cards);

    //! Adds hero power cards to \p cards.
    //! \param cards A list of cards to store the data such as powers.
    static void AddHeroPowers(std::map<std::string, CardDef>& cards);

    //! Adds tier 1 minion cards that are collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers.
    static void AddTier1Minions(std::map<std::string, CardDef>& cards);

    //! Adds tier 2 minion cards that are collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers.
    static void AddTier2Minions(std::map<std::string, CardDef>& cards);

    //! Adds tier 3 minion cards that are collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers.
    static void AddTier3Minions(std::map<std::string, CardDef>& cards);

    //! Adds tier 4 minion cards that are collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers.
    static void AddTier4Minions(std::map<std::string, CardDef>& cards);

    //! Adds tier 5 minion cards that are collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers.
    static void AddTier5Minions(std::map<std::string, CardDef>& cards);

    //! Adds tier 6 minion cards that are collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers.
    static void AddTier6Minions(std::map<std::string, CardDef>& cards);

    //! Adds token minion cards.
    //! \param cards A list of cards to store the data such as powers.
    static void AddTokenMinions(std::map<std::string, CardDef>& cards);

    //! Adds enchantment cards.
    //! \param cards A list of cards to store the data such as powers.
    static void AddEnchantments(std::map<std::string, CardDef>& cards);

    //! Adds all cards to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddAll(std::map<std::string, CardDef>& cards);
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_BATTLEGROUNDS_CARDS_GEN_HPP
