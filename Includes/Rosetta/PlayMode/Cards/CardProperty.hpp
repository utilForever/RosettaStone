// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CARD_PROPERTY_HPP
#define ROSETTASTONE_PLAYMODE_CARD_PROPERTY_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/Common/Enums/TaskEnums.hpp>

#include <map>
#include <string>
#include <vector>

namespace RosettaStone::PlayMode
{
//!
//! \brief CardProperty struct.
//!
//! This struct holds all property values for a card.
//!
struct CardProperty
{
    //! Clears card property data.
    void ClearData()
    {
        playReqs.clear();
        chooseCardIDs.clear();
        entourages.clear();
        appendages.clear();
        corruptCardID.clear();
        infusedCardID.clear();
        questProgressTotal = 0;
        heroPowerDbfID = 0;
        numMinionsToInfuse = 0;
    }

    std::map<PlayReq, int> playReqs;
    std::vector<std::string> chooseCardIDs;
    std::vector<std::string> entourages;
    std::vector<std::tuple<std::string, SummonSide>> appendages;
    std::string corruptCardID;
    std::string infusedCardID;
    int questProgressTotal = 0;
    int heroPowerDbfID = 0;
    int numMinionsToInfuse = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_CARD_PROPERTY_HPP
