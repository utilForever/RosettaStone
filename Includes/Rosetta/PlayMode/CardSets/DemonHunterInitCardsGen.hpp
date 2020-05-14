// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_DEMON_HUNTER_INIT_CARDS_GEN_HPP
#define ROSETTASTONE_PLAYMODE_DEMON_HUNTER_INIT_CARDS_GEN_HPP

#include <Rosetta/PlayMode/Cards/CardDef.hpp>

#include <map>
#include <string>

namespace RosettaStone::PlayMode
{
//!
//! \brief DemonHunterInitCardsGen class.
//!
//! This structure adds DEMON_HUNTER_INITIATE cards to the data storage with
//! powers, play requirements and entourages.
//!
class DemonHunterInitCardsGen
{
 public:
    //! Adds demon hunter cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddDemonHunter(std::map<std::string, CardDef>& cards);

    //! Adds demon hunter cards that are not collectible to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddDemonHunterNonCollect(std::map<std::string, CardDef>& cards);

    //! Adds all cards to \p cards.
    //! \param cards A list of cards to store the data such as powers,
    //! play requirements and entourages.
    static void AddAll(std::map<std::string, CardDef>& cards);
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_DEMON_HUNTER_INIT_CARDS_GEN_HPP
