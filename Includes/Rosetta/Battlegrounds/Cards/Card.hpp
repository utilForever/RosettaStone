// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_CARD_HPP
#define ROSETTASTONE_BATTLEGROUNDS_CARD_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>

#include <map>
#include <string>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Card class.
//!
//! This class stores card information such as attack, health and cost.
//!
class Card
{
 public:
    //! Returns the value of card type.
    //! \return The value of card type.
    CardType GetCardType() const;

    std::string id;
    int dbfID;

    std::string name;
    std::string text;

    std::map<GameTag, int> gameTags;

    bool isCurHero;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_CARD_HPP
