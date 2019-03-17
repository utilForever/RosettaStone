// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_TORCH_POLICY_HPP
#define HEARTHSTONEPP_TORCH_POLICY_HPP

#include <hspp/Policies/BasicPolicy.hpp>
#include <torch/torch.h>

namespace HSppTorch
{
using namespace Hearthstonepp;

class TorchPolicy : public BasicPolicy
{
 public:
    TorchPolicy() = default;

 private:
    //! Method for MulliganTask requirement.
    TaskMeta RequireMulligan(Player& player) override;

    //! Method for PlaySpellTask requirement.
    TaskMeta RequirePlaySpell(Player& player) override;

    //! Method for PlayCardTask requirement.
    TaskMeta RequirePlayCard(Player& player) override;

    //! Method for PlayMinionTask requirement.
    TaskMeta RequirePlayMinion(Player& player) override;

    //! Method for CombatTask requirement.
    TaskMeta RequireCombat(Player& player) override;

    //! Method for OverDraw notifying.
    void NotifyOverDraw(const TaskMeta& meta) override;
};
}  // namespace Hearthstonepp

#endif