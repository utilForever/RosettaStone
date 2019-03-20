// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_POWER_LOADER_HPP
#define HEARTHSTONEPP_POWER_LOADER_HPP

#include <Rosetta/Cards/Card.hpp>

#include <vector>

namespace Hearthstonepp
{
//!
//! \brief PowerLoader class.
//!
//! This class loads power data from card data generators.
//!
class PowerLoader
{
 public:
    //! Loads power data from card data generators.
    //! \param cards Data storage to store added cards with power.
    static void Load(std::vector<Card>& cards);
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_POWER_LOADER_HPP