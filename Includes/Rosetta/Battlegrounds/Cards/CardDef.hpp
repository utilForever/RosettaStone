// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_CARD_DEF_HPP
#define ROSETTASTONE_BATTLEGROUNDS_CARD_DEF_HPP

#include <Rosetta/Battlegrounds/Enchants/Power.hpp>
#include <Rosetta/Common/Enums/CardEnums.hpp>

#include <map>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief CardDef class.
//!
//! This class stores the card data such as powers and play requirements.
//!
class CardDef
{
 public:
    //! Default constructor.
    CardDef() = default;

    //! Constructs card def with given \p _power.
    //! \param _power The power data.
    explicit CardDef(Power _power);

    Power power;
    std::map<PlayReq, int> playReqs;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_CARD_DEF_HPP
