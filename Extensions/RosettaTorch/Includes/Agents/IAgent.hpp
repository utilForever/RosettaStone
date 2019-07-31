// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_AGENTS_IAGENT_HPP
#define ROSETTASTONE_TORCH_AGENTS_IAGENT_HPP

#include <Rosetta/Views/BoardRefView.hpp>

namespace RosettaTorch::Agents
{
//!
//! \brief IAgent class.
//!
//! This class is interface of various agent classes.
//! All classes that inherit from it must implement Think() related methods.
//!
class IAgent
{
 public:
    //! Default virtual destructor.
    virtual ~IAgent() = default;

    //! Processes something before calling Think() method.
    virtual void BeforeThink() = 0;

    //! Processes something related to agent.
    //! \param iteration The number of iteration.
    virtual void Think(uint64_t iteration) = 0;

    //! Processes something after calling Think() method.
    //! \param iteration The number of iteration.
    virtual void AfterThink(uint64_t iteration) = 0;
};
}  // namespace RosettaTorch::Agents

#endif  // ROSETTASTONE_TORCH_AGENTS_IAGENT_HPP