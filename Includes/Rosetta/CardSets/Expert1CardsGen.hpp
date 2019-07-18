// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_EXPERT1_CARDS_GEN_HPP
#define ROSETTASTONE_EXPERT1_CARDS_GEN_HPP

#include <Rosetta/Enchants/Power.hpp>

#include <map>
#include <string>

namespace RosettaStone
{
//!
//! \brief Expert1CardsGen class.
//!
//! This structure adds EXPERT1 cards to data storage with power.
//!
class Expert1CardsGen
{
 public:
    //! Adds hero cards to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddHeroes(std::map<std::string, Power>& cards);

    //! Adds hero power cards to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddHeroPowers(std::map<std::string, Power>& cards);

    //! Adds druid cards that are collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddDruid(std::map<std::string, Power>& cards);

    //! Adds druid cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddDruidNonCollect(std::map<std::string, Power>& cards);

    //! Adds hunter cards that are collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddHunter(std::map<std::string, Power>& cards);

    //! Adds hunter cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddHunterNonCollect(std::map<std::string, Power>& cards);

    //! Adds mage cards that are collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddMage(std::map<std::string, Power>& cards);

    //! Adds mage cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddMageNonCollect(std::map<std::string, Power>& cards);

    //! Adds paladin cards that are collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddPaladin(std::map<std::string, Power>& cards);

    //! Adds paladin cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddPaladinNonCollect(std::map<std::string, Power>& cards);

    //! Adds priest cards that are collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddPriest(std::map<std::string, Power>& cards);

    //! Adds priest cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddPriestNonCollect(std::map<std::string, Power>& cards);

    //! Adds rogue cards that are collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddRogue(std::map<std::string, Power>& cards);

    //! Adds rogue cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddRogueNonCollect(std::map<std::string, Power>& cards);

    //! Adds shaman cards that are collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddShaman(std::map<std::string, Power>& cards);

    //! Adds shaman cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddShamanNonCollect(std::map<std::string, Power>& cards);

    //! Adds warlock cards that are collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddWarlock(std::map<std::string, Power>& cards);

    //! Adds warlock cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddWarlockNonCollect(std::map<std::string, Power>& cards);

    //! Adds warrior cards that are collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddWarrior(std::map<std::string, Power>& cards);

    //! Adds warrior cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddWarriorNonCollect(std::map<std::string, Power>& cards);

    //! Adds neutral cards that are collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddNeutral(std::map<std::string, Power>& cards);

    //! Adds neutral cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddNeutralNonCollect(std::map<std::string, Power>& cards);

    //! Adds Adds cards that are not collectible to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddDreamNonCollect(std::map<std::string, Power>& cards);

    //! Adds all cards to \p cards.
    //! \param cards Data storage to store added cards with power.
    static void AddAll(std::map<std::string, Power>& cards);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_EXPERT1_CARDS_GEN_HPP
