// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_DECKSTRING_HPP
#define ROSETTASTONE_DECKSTRING_HPP

#include <Rosetta/Accounts/DeckInfo.hpp>

#include <string_view>

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
    static DeckInfo ParseFromString(const std::string_view& deckString);

    //! Parse from stream
    //! \param stream Stream to get deck string
    static DeckInfo ParseFromStream(std::istream& stream);
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_DECKSTRING_HPP
