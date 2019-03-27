// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TORCH_TORCH_POLICY_HPP
#define ROSETTASTONE_TORCH_TORCH_POLICY_HPP

#include <Rosetta/Policies/BasicPolicy.hpp>
#include <RosettaTorch/ModuleBase.hpp>

namespace RosettaTorch
{
using namespace RosettaStone;

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

    //! Method for PlayCardTask requirement.
    TaskMeta RequirePlayCard(Player& player) override;

    //! Method for CombatTask requirement.
    TaskMeta RequireAttack(Player& player) override;

    //! Method for OverDraw notifying.
    void NotifyOverDraw(const TaskMeta& meta) override;
};
}  // namespace HSppTorch

#endif