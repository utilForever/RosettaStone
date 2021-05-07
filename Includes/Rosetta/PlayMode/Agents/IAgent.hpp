// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_IAGENT_HPP
#define ROSETTASTONE_PLAYMODE_IAGENT_HPP

#include <Rosetta/PlayMode/Games/Game.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief IAgent class.
//!
//! This class is an interface of agent classes.
//!
class IAgent
{
 public:
    //! Default virtual destructor.
    virtual ~IAgent() = default;

    //! Sets a player type.
    //! \param playerType A player type.
    virtual void SetPlayerType(PlayerType playerType) = 0;

    //! Gets an action of agent for mulligan cards.
    //! \param state The current game state.
    //! \return An action of agent for mulligan cards.
    virtual std::vector<int> GetActionForMulligan(Game& state) const = 0;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_IAGENT_HPP
