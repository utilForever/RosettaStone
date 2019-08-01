// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_DECKSTRING_HPP
#define ROSETTASTONE_DECKSTRING_HPP

#include <Rosetta/Accounts/DeckInfo.hpp>

namespace RosettaStone
{
class DeckString
{
 public:
    //! Deck string version
    static constexpr int DECKSTRING_VERSION = 1;

 public:
    //! Parse from string
    //! \param deckString Deck String
    static DeckInfo ParseFromString(const std::string& deckString);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_DECKSTRING_HPP
