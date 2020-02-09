//// This code is based on Sabberstone project.
//// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
//// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
//// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon
//
//#ifndef ROSETTASTONE_ULDUM_CARDS_GEN_HPP
//#define ROSETTASTONE_ULDUM_CARDS_GEN_HPP
//
//#include <Rosetta/Enchants/Power.hpp>
//
//#include <map>
//#include <string>
//
//namespace RosettaStone
//{
//using PowersType = std::map<std::string, Power>;
//using PlayReqs = std::map<PlayReq, int>;
//using PlayReqsType = std::map<std::string, PlayReqs>;
//using Entourages = std::vector<std::string>;
//using EntouragesType = std::map<std::string, Entourages>;
//
////!
////! \brief UldumCardsGen class.
////!
////! This structure adds ULDUM cards to the data storage with powers,
////! play requirements and entourages.
////!
//class UldumCardsGen
//{
// public:
//    //! Adds hero cards to \p powers, \p playReqs and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddHeroes(PowersType& powers, PlayReqsType& playReqs,
//                          EntouragesType& entourages);
//
//    //! Adds hero power cards to \p powers, \p playReqs and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddHeroPowers(PowersType& powers, PlayReqsType& playReqs,
//                              EntouragesType& entourages);
//
//    //! Adds druid cards that are collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddDruid(PowersType& powers, PlayReqsType& playReqs,
//                         EntouragesType& entourages);
//
//    //! Adds druid cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddDruidNonCollect(PowersType& powers, PlayReqsType& playReqs,
//                                   EntouragesType& entourages);
//
//    //! Adds hunter cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddHunter(PowersType& powers, PlayReqsType& playReqs,
//                          EntouragesType& entourages);
//
//    //! Adds hunter cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddHunterNonCollect(PowersType& powers, PlayReqsType& playReqs,
//                                    EntouragesType& entourages);
//
//    //! Adds mage cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddMage(PowersType& powers, PlayReqsType& playReqs,
//                        EntouragesType& entourages);
//
//    //! Adds mage cards that are not collectible to \p powers and \p playReqs.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddMageNonCollect(PowersType& powers, PlayReqsType& playReqs,
//                                  EntouragesType& entourages);
//
//    //! Adds paladin cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddPaladin(PowersType& powers, PlayReqsType& playReqs,
//                           EntouragesType& entourages);
//
//    //! Adds paladin cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddPaladinNonCollect(PowersType& powers, PlayReqsType& playReqs,
//                                     EntouragesType& entourages);
//
//    //! Adds priest cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddPriest(PowersType& powers, PlayReqsType& playReqs,
//                          EntouragesType& entourages);
//
//    //! Adds priest cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddPriestNonCollect(PowersType& powers, PlayReqsType& playReqs,
//                                    EntouragesType& entourages);
//
//    //! Adds rogue cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddRogue(PowersType& powers, PlayReqsType& playReqs,
//                         EntouragesType& entourages);
//
//    //! Adds rogue cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddRogueNonCollect(PowersType& powers, PlayReqsType& playReqs,
//                                   EntouragesType& entourages);
//
//    //! Adds shaman cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddShaman(PowersType& powers, PlayReqsType& playReqs,
//                          EntouragesType& entourages);
//
//    //! Adds shaman cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddShamanNonCollect(PowersType& powers, PlayReqsType& playReqs,
//                                    EntouragesType& entourages);
//
//    //! Adds warlock cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddWarlock(PowersType& powers, PlayReqsType& playReqs,
//                           EntouragesType& entourages);
//
//    //! Adds warlock cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddWarlockNonCollect(PowersType& powers, PlayReqsType& playReqs,
//                                     EntouragesType& entourages);
//
//    //! Adds warrior cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddWarrior(PowersType& powers, PlayReqsType& playReqs,
//                           EntouragesType& entourages);
//
//    //! Adds warrior cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddWarriorNonCollect(PowersType& powers, PlayReqsType& playReqs,
//                                     EntouragesType& entourages);
//
//    //! Adds neutral cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddNeutral(PowersType& powers, PlayReqsType& playReqs,
//                           EntouragesType& entourages);
//
//    //! Adds neutral cards that are not collectible to \p powers, \p playReqs
//    //! and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddNeutralNonCollect(PowersType& powers, PlayReqsType& playReqs,
//                                     EntouragesType& entourages);
//
//    //! Adds all cards to \p powers, \p playReqs and \p entourages.
//    //! \param powers The data storage to store added cards with powers.
//    //! \param playReqs The data storage to store added cards with
//    //! play requirements.
//    //! \param entourages The data storage to store added cards with entourages.
//    static void AddAll(PowersType& powers, PlayReqsType& playReqs,
//                       EntouragesType& entourages);
//};
//}  // namespace RosettaStone
//
//#endif  // ROSETTASTONE_ULDUM_CARDS_GEN_HPP
