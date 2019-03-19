// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Models/Minion.hpp>
#include <hspp/Models/Player.hpp>

namespace Hearthstonepp
{
Minion::Minion(Player& _owner, Card& _card) : Character(_owner, _card)
{
    // Do nothing
}

void Minion::Destroy()
{
    GetOwner().GetField().RemoveMinion(*this);
}
}  // namespace Hearthstonepp