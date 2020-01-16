// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_INTERNAL_CARD_LOADER_HPP
#define ROSETTASTONE_INTERNAL_CARD_LOADER_HPP

#include <Rosetta/Cards/Card.hpp>

#include <vector>

namespace RosettaStone
{
//!
//! \brief CardInternalLoader class.
//!
//! This class loads internal card data from card data generators.
//! e.g. power and play requirements.
//!
class InternalCardLoader
{
 public:
    //! Loads internal card data from card data generators.
    //! \param cards The data storage to store added cards with power
    //! and play requirements.
    static void Load(std::vector<Card*>& cards);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_INTERNAL_CARD_LOADER_HPP
