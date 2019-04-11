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
using namespace RosettaStone;

//!
//! \brief ActionEncoder struct.
//!
//! This struct generates torch tensor from ActionEncode.
//!
struct ActionEncoder
{
    static constexpr size_t TaskIDSize = 4;

    static constexpr TaskID TaskIDs[TaskIDSize] = {
        TaskID::MULLIGAN, TaskID::END_TURN, TaskID::ATTACK, TaskID::PLAY_CARD
    };

    /////////////////////////////////////////////
    // My hand, my field, your field
    static constexpr size_t TargetPlaceSize = 3;

    static constexpr size_t CurrentHandOffset = 0;

    static constexpr size_t CurrentFieldOffset = 1;

    static constexpr size_t OpponentFieldOffset = 2;

    /////////////////////////////////////////////
    static constexpr size_t MaximumFieldSize = 10;

    static constexpr size_t EntityEncodeSize =
        TargetPlaceSize + MaximumFieldSize;

    /////////////////////////////////////////////
    static constexpr size_t NumSource = 1;

    static constexpr size_t NumTarget = Generic::ActionEncode::NumTarget;

    /////////////////////////////////////////////
    static constexpr size_t ActionTensorSize =
        TaskIDSize + EntityEncodeSize * (NumSource + NumTarget);

    //! Convert ActionEncode to torch::Tensor.
    static torch::Tensor ActionToTensor(const Game& game,
                                        const Generic::ActionEncode& action);
};

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
    TaskMeta Next(const Game& game) override;

 private:
    torch::nn::ModuleHolder<ModuleBase> m_module;
    GameToVec* m_gameToVec;

    Generic::ActionEncode m_action;

    //! Convert ActionEncode to TaskMeta.
    TaskMeta ActionToTaskMeta() const;

    TaskMeta Inference(const Game& game,
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