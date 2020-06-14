// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Battle.hpp>

namespace RosettaStone::Battlegrounds
{
Battle::Battle(Player& player1, Player& player2)
    : m_player1(player1), m_player2(player2)
{
    // Do nothing
}

void Battle::Run()
{
    (void)m_player1;
    (void)m_player2;
}
}  // namespace RosettaStone::Battlegrounds
