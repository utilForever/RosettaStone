// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TORCH_TORCH_POLICY_HPP
#define ROSETTASTONE_TORCH_TORCH_POLICY_HPP

#include <Rosetta/Actions/AvailableActions.hpp>
#include <Rosetta/Policies/BasicPolicy.hpp>
#include <RosettaTorch/GameToVec.hpp>
#include <RosettaTorch/ModuleBase.hpp>

namespace RosettaTorch
{
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
    //! \param gameToVec The generator for converting game to numeric vector.
    TorchPolicy(std::shared_ptr<ModuleBase> module, GameToVec* gameToVec);

    //! Gets next behavior from given \p game.
    //! \param game The current game status.
    //! \return The behavior serialized as TaskMeta.
    TaskMeta Next(Game& game) override;

 private:
    torch::nn::ModuleHolder<ModuleBase> m_module;
    GameToVec* m_gameToVec;

    Generic::ActionEncode m_action;

    //! Convert ActionEncode to TaskMeta.
    TaskMeta ActionToTaskMeta() const;

    TaskMeta Inference(Game& game,
                       const std::vector<Generic::ActionEncode>& actions);

    //! Method for MulliganTask requirement.
    TaskMeta RequireMulligan(Player& player) override;

    //! Method for PlayCardTask requirement.
    TaskMeta RequirePlayCard(Player& player) override;

    //! Method for CombatTask requirement.
    TaskMeta RequireAttack(Player& player) override;
};
}  // namespace RosettaTorch

#endif