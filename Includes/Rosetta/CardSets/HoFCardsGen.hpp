// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_HOF_CARDS_GEN_HPP
#define ROSETTASTONE_HOF_CARDS_GEN_HPP

#include <Rosetta/Enchants/Power.hpp>

#include <map>
#include <string>

namespace RosettaStone
{
using PowersType = std::map<std::string, Power>;
using PlayReqs = std::vector<std::tuple<PlayReq, int>>;
using PlayReqsType = std::map<std::string, PlayReqs>;

//!
//! \brief HoFCardsGen class.
//!
//! This structure adds HOF cards to the data storage with powers
//! and play requirements.
//!
class HoFCardsGen
{
 public:
    //! Adds hero cards to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddHeroes(PowersType& powers, PlayReqsType& playReqs);

    //! Adds hero power cards to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddHeroPowers(PowersType& powers, PlayReqsType& playReqs);

    //! Adds druid cards that are collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddDruid(PowersType& powers, PlayReqsType& playReqs);

    //! Adds druid cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddDruidNonCollect(PowersType& powers, PlayReqsType& playReqs);

    //! Adds hunter cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddHunter(PowersType& powers, PlayReqsType& playReqs);

    //! Adds hunter cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddHunterNonCollect(PowersType& powers, PlayReqsType& playReqs);

    //! Adds mage cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddMage(PowersType& powers, PlayReqsType& playReqs);

    //! Adds mage cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddMageNonCollect(PowersType& powers, PlayReqsType& playReqs);

    //! Adds paladin cards that are not collectible to \p powers and
    //! \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddPaladin(PowersType& powers, PlayReqsType& playReqs);

    //! Adds paladin cards that are not collectible to \p powers and
    //! \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddPaladinNonCollect(PowersType& powers,
                                     PlayReqsType& playReqs);

    //! Adds priest cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddPriest(PowersType& powers, PlayReqsType& playReqs);

    //! Adds priest cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddPriestNonCollect(PowersType& powers, PlayReqsType& playReqs);

    //! Adds rogue cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddRogue(PowersType& powers, PlayReqsType& playReqs);

    //! Adds rogue cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddRogueNonCollect(PowersType& powers, PlayReqsType& playReqs);

    //! Adds shaman cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddShaman(PowersType& powers, PlayReqsType& playReqs);

    //! Adds shaman cards that are not collectible to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddShamanNonCollect(PowersType& powers, PlayReqsType& playReqs);

    //! Adds warlock cards that are not collectible to \p powers and
    //! \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddWarlock(PowersType& powers, PlayReqsType& playReqs);

    //! Adds warlock cards that are not collectible to \p powers and
    //! \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddWarlockNonCollect(PowersType& powers,
                                     PlayReqsType& playReqs);

    //! Adds warrior cards that are not collectible to \p powers and
    //! \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddWarrior(PowersType& powers, PlayReqsType& playReqs);

    //! Adds warrior cards that are not collectible to \p powers and
    //! \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddWarriorNonCollect(PowersType& powers,
                                     PlayReqsType& playReqs);

    //! Adds neutral cards that are not collectible to \p powers and
    //! \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddNeutral(PowersType& powers, PlayReqsType& playReqs);

    //! Adds neutral cards that are not collectible to \p powers and
    //! \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddNeutralNonCollect(PowersType& powers,
                                     PlayReqsType& playReqs);

    //! Adds all cards to \p powers and \p playReqs.
    //! \param powers The data storage to store added cards with powers.
    //! \param playReqs The data storage to store added cards with
    //! play requirements.
    static void AddAll(PowersType& powers, PlayReqsType& playReqs);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_HOF_CARDS_GEN_HPP