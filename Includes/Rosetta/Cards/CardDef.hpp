// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_CARD_DEF_HPP
#define ROSETTASTONE_CARD_DEF_HPP

#include <Rosetta/Enchants/Power.hpp>

#include <map>
#include <vector>

namespace RosettaStone
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
    CardDef(Power _power);

    //! Constructs card def with given \p _power and \p _playReqs.
    //! \param _power The power data.
    //! \param _playReqs The play requirements data.
    CardDef(Power _power, std::map<PlayReq, int> _playReqs);

    //! Constructs card def with given \p _power, \p _playReqs and
    //! \p _entourages.
    //! \param _power The power data.
    //! \param _playReqs The play requirements data.
    //! \param _entourages The entourages data.
    CardDef(Power _power, std::map<PlayReq, int> _playReqs,
            std::vector<std::string> _entourages);

    Power power;
    std::map<PlayReq, int> playReqs;
    std::vector<std::string> entourages;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CARD_DEF_HPP
