// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CARD_DEF_HPP
#define ROSETTASTONE_PLAYMODE_CARD_DEF_HPP

#include <Rosetta/PlayMode/Cards/CardProperty.hpp>
#include <Rosetta/PlayMode/Enchants/Power.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief CardDef struct.
//!
//! This struct stores card power and property.
//!
struct CardDef
{
    //! Clears power and property data.
    void ClearData()
    {
        power.ClearData();
        property.ClearData();
    }

    Power power;
    CardProperty property;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_CARD_DEF_HPP
