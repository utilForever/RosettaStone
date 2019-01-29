// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_POLICY_HPP
#define HEARTHSTONEPP_POLICY_HPP

#include <hspp/Enums/TaskEnums.hpp>
#include <hspp/Game/Game.hpp>
#include <hspp/Tasks/TaskMeta.hpp>

namespace Hearthstonepp
{
class IPolicy
{
 public:
    IPolicy() = default;

    virtual ~IPolicy() = default;

    virtual TaskMeta Next(const Game& game) = 0;

    virtual TaskMeta Require(Player& player, TaskID id) = 0;
};
}  // namespace Hearthstonepp

#endif