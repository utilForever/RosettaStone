// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HSPP_TORCH_TORCH_POLICY_HPP
#define HSPP_TORCH_TORCH_POLICY_HPP

#include <hspp/Policies/BasicPolicy.hpp>
#include <hspp_torch/ModuleBase.hpp>

namespace HSppTorch
{
using namespace Hearthstonepp;

//!
//! \brief TorchPolicy class.
//!
//! This class is interface for Hearthstonepp deep learning policy support.
//!
class TorchPolicy : public BasicPolicy
{
 public:
    //! Constructs torch based policy with given \p module.
    //! \param module The module base for torch deep learning policy.
    TorchPolicy(std::shared_ptr<ModuleBase> module);

 private:
    torch::nn::ModuleHolder<ModuleBase> m_module;

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
}  // namespace HSppTorch

#endif