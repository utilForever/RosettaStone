// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CARD_DEF_HPP
#define ROSETTASTONE_PLAYMODE_CARD_DEF_HPP

#include <Rosetta/PlayMode/Enchants/Power.hpp>

#include <map>
#include <vector>

namespace RosettaStone::PlayMode
{
//!
//! \brief CardDef class.
//!
//! This class stores the card data such as powers and play requirements.
//!
class CardDef
{
 public:
    Power power;
    std::map<PlayReq, int> playReqs;
    std::vector<std::string> chooseCardIDs;
    std::vector<std::string> entourages;
    std::string corruptCardID;
    int questProgressTotal = 0;
    int heroPowerDbfID = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_CARD_DEF_HPP
