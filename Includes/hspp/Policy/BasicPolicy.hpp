// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_BASIC_POLICY_HPP
#define HEARTHSTONEPP_BASIC_POLICY_HPP

#include <hspp/Policy/Policy.hpp>

#include <functional>

namespace Hearthstonepp
{
class BasicPolicy : public IPolicy
{
 public:
    BasicPolicy() = default;

    ~BasicPolicy() = default;

    TaskMeta Next(const Game& game) override;

    TaskMeta Require(Player& player, TaskID id) override;

    void Notify(const TaskMeta& meta) override;

 private:
    virtual TaskMeta RequireMulligan(Player& player) = 0;
    virtual TaskMeta RequirePlaySpell(Player& player) = 0;
    virtual TaskMeta RequirePlayCard(Player& player) = 0;
    virtual TaskMeta RequirePlayMinion(Player& player) = 0;
    virtual TaskMeta RequireCombat(Player& player) = 0;

    virtual void NotifyDraw(const TaskMeta& meta) = 0;

    std::map<TaskID, std::function<TaskMeta(BasicPolicy&, Player&)>> m_require =
        {
            { TaskID::MULLIGAN, &BasicPolicy::RequireMulligan },
            { TaskID::PLAY_SPELL, &BasicPolicy::RequirePlaySpell },
            { TaskID::PLAY_CARD, &BasicPolicy::RequirePlayCard },
            { TaskID::PLAY_MINION, &BasicPolicy::RequirePlayMinion },
            { TaskID::COMBAT, &BasicPolicy::RequireCombat },
        };

    std::map<TaskID, std::function<void(BasicPolicy&, const TaskMeta&)>>
        m_notify = {
            { TaskID::DRAW, &BasicPolicy::NotifyDraw },
        };
};
}  // namespace Hearthstonepp

#endif