// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CARD_LOADER_HPP
#define ROSETTASTONE_CARD_LOADER_HPP

#include <Rosetta/Cards/Card.hpp>

#include <json/json.hpp>

#include <vector>

namespace RosettaStone
{
//!
//! \brief CardLoader class.
//!
//! This class loads card data from cards.json.
//!
class CardLoader
{
 public:
    //! Loads card data from cards.json.
    //! \param cards Data storage to store added cards with power.
    static void Load(std::vector<Card>& cards);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CARD_LOADER_HPP
