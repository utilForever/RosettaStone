// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GENERIC_H
#define HEARTHSTONEPP_GENERIC_H

#include <hspp/Accounts/Player.h>
#include <hspp/Cards/Entity.h>

namespace Hearthstonepp
{
//!
//! \brief Generic class.
//!
class Generic
{
 public:
    static Entity* DrawCard(Player& player, Card card);
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_GENERIC_H
