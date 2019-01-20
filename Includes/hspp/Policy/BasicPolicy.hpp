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

    TaskMeta next(const Game& game) override;

    TaskMeta require(const Game& game, TaskID id) override;

 private:
    TaskMeta PlayerSetting(const Game& game);

    std::map<TaskID, std::function<TaskMeta(const Game& game)>> m_table = {
        { TaskID::PLAYER_SETTING, &BasicPolicy::PlayerSetting }
    };
};
}  // namespace Hearthstonepp

#endif