// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_IO_POLICY_HPP
#define HEARTHSTONEPP_IO_POLICY_HPP

#include <Rosetta/Policies/BasicPolicy.hpp>

#include <iostream>

namespace Hearthstonepp
{
//!
//! \brief IoPolicy class.
//!
//! This class implement IPolicy for user input policy.
//!
class IoPolicy : public BasicPolicy
{
 public:
    //! Constructs IO policy with given \p out and \p in.
    //! \param out Basic output stream.
    //! \param in Basic input stream.
    IoPolicy(std::ostream& out, std::istream& in);

 private:
    //! Method for MulliganTask requirement.
    TaskMeta RequireMulligan(Player& player) override;

    //! Method for PlayCardTask requirement.
    TaskMeta RequirePlayCard(Player& player) override;

    //! Method for AttackTask requirement.
    TaskMeta RequireAttack(Player& player) override;

    //! Method for OverDraw notifying.
    void NotifyOverDraw(const TaskMeta& meta) override;

    std::ostream& m_out;
    std::istream& m_in;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_IO_POLICY_HPP