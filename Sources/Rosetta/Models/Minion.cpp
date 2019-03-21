// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
Minion::Minion(Player& _owner, Card& _card) : Character(_owner, _card)
{
    // Do nothing
}

void Minion::Destroy()
{
    GetOwner().GetField().RemoveMinion(*this);
    GetOwner().GetGraveyard().AddCard(*this);
}
}  // namespace RosettaStone
