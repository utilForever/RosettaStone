// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Minion.hpp>

#include <utility>

namespace RosettaStone::Battlegrounds
{
Minion::Minion(Card card) : m_card(std::move(card))
{
    // Do nothing
}
}  // namespace RosettaStone::Battlegrounds
