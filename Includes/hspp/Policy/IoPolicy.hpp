// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_IO_POLICY_HPP
#define HEARTHSTONEPP_IO_POLICY_HPP

#include <hspp/Policy/BasicPolicy.hpp>

#include <iostream>

namespace Hearthstonepp
{
class IoPolicy : public BasicPolicy
{
 public:
    IoPolicy(std::ostream& out, std::istream& in);

 private:
    TaskMeta RequireMulligan(Player& player) override;
    TaskMeta RequirePlaySpell(Player& player) override;
    TaskMeta RequirePlayCard(Player& player) override;
    TaskMeta RequirePlayMinion(Player& player) override;
    TaskMeta RequireCombat(Player& player) override;

    void NotifyDraw(const TaskMeta& meta) override;

    std::ostream& m_out;
    std::istream& m_in;
};
}  // namespace Hearthstonepp

#endif