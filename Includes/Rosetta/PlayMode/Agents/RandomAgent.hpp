// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_RANDOM_AGENT_HPP
#define ROSETTASTONE_PLAYMODE_RANDOM_AGENT_HPP

#include <Rosetta/PlayMode/Agents/IAgent.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief RandomAgent class.
//!
//! This class is an agent that plays an action at random.
//!
class RandomAgent final : public IAgent
{
 public:
    //! Default virtual destructor.
    ~RandomAgent() override = default;

    //! Sets a player type.
    //! \param playerType A player type.
    void SetPlayerType(PlayerType playerType) override;

    //! Gets an action of agent for mulligan cards.
    //! \param state The current game state.
    //! \return An action of agent for mulligan cards.
    std::vector<int> GetActionForMulligan(Game& state) const override;

 private:
    PlayerType m_playerType = PlayerType::INVALID;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_RANDOM_AGENT_HPP
