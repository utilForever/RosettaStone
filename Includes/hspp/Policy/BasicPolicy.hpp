// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_BASIC_POLICY_HPP
#define HEARTHSTONEPP_BASIC_POLICY_HPP

#include <hspp/Policy/Policy.hpp>

namespace Hearthstonepp
{
class BasicPolicy : public IPolicy
{
 public:
    BasicPolicy() = default;

    ~BasicPolicy() = default;

    TaskMeta Next(const Game& game) override;

    TaskMeta Require(Player& player, TaskID id) override;

 private:
    std::map<TaskID, std::function<TaskMeta(const Game& game)>> m_table = {
    };
};
}  // namespace Hearthstonepp

#endif