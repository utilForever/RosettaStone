// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Agents/RandomAgent.hpp>

#include <effolkronium/random.hpp>

#include <cassert>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode
{
void RandomAgent::SetPlayerType(PlayerType playerType)
{
    m_playerType = playerType;
}

std::vector<int> RandomAgent::GetActionForMulligan(Game& state) const
{
    assert(m_playerType == PlayerType::PLAYER1 ||
           m_playerType == PlayerType::PLAYER2);

    const Player* player = m_playerType == PlayerType::PLAYER1
                               ? state.GetPlayer1()
                               : state.GetPlayer2();

    std::vector<int> indices;
    for (std::size_t i = 0; i < player->choice->choices.size(); ++i)
    {
        if (Random::get<std::size_t>(0, 1) == 1)
        {
            indices.emplace_back(i);
        }
    }

    return indices;
}
}  // namespace RosettaStone::PlayMode