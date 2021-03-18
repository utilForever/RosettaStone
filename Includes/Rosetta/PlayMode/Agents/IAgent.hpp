// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_IAGENT_HPP
#define ROSETTASTONE_PLAYMODE_IAGENT_HPP

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
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_IAGENT_HPP
