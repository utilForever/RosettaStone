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
    virtual TaskMeta RequireMulligan(Player& player);
    virtual TaskMeta RequirePlaySpell(Player& player);
    virtual TaskMeta RequirePlayCard(Player& player);
    virtual TaskMeta RequirePlayMinion(Player& player);
    virtual TaskMeta RequireCombat(Player& player);

    virtual void NotifyOverDraw(const TaskMeta& meta);

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
            { TaskID::OVERDRAW, &BasicPolicy::NotifyOverDraw },
        };
};
}  // namespace Hearthstonepp

#endif