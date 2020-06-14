// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Battle.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::Battlegrounds
{
Battle::Battle(Player& player1, Player& player2)
    : m_player1(player1),
      m_player2(player2),
      m_p1Field(m_player1.recruitFieldZone),
      m_p2Field(m_player2.recruitFieldZone)
{
    // Do nothing
}

void Battle::Initialize()
{
    // Determine the player attacks first
    // NOTE: The player with the greater number of minions attacks first.
    // If the number of minions is equal for both players, one of the players
    // is randomly selected to attack first.
    const int p1NumMinions = m_p1Field.GetCount();
    const int p2NumMinions = m_p2Field.GetCount();

    if (p1NumMinions > p2NumMinions)
    {
        m_turn = Turn::PLAYER1;
    }
    else if (p1NumMinions < p2NumMinions)
    {
        m_turn = Turn::PLAYER2;
    }
    else
    {
        m_turn = static_cast<Turn>(Random::get<std::size_t>(0, 1));
    }
}

void Battle::Run()
{
    Initialize();
}

bool Battle::IsDone() const
{
    return m_p1Field.IsEmpty() || m_p2Field.IsEmpty() || m_turn == Turn::DONE;
}
}  // namespace RosettaStone::Battlegrounds
