// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_POLICY_HPP
#define ROSETTASTONE_POLICY_HPP

#include <Rosetta/Enums/TaskEnums.hpp>
#include <Rosetta/Tasks/TaskMeta.hpp>

namespace RosettaStone
{
class Game;

//!
//! \brief IPolicy class.
//!
//! This class is for abstracting game playing behavior.
//!
class IPolicy
{
 public:
    //! Default constructor.
    IPolicy() = default;

    //! Default virtual destructor.
    virtual ~IPolicy() = default;

    //! Gets next behavior from given \p game.
    //! \param game The current game status.
    //! \return The behavior serialized as TaskMeta.
    virtual TaskMeta Next(Game& game) = 0;

    //! Gets proper requirement with given \p player and \p id.
    //! \param player The player who requests the requirement.
    //! \param id The requested TaskID.
    virtual TaskMeta Require(Player& player, TaskID id) = 0;

    //! Notify serialized data to IPolicy.
    //! \param meta The serialized data.
    virtual void Notify(const TaskMeta& meta) = 0;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_POLICY_HPP
