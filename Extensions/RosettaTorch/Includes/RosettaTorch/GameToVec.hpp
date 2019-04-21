// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TORCH_GAME_TO_VEC_HPP
#define ROSETTASTONE_TORCH_GAME_TO_VEC_HPP

#include <Rosetta/Games/Game.hpp>

#include <torch/torch.h>

namespace RosettaTorch
{
using namespace RosettaStone;

//!
//! \brief ActionEncoder struct.
//!
//! This struct generates torch tensor from Game context.
//!
class GameToVec
{
 public:
    //! Constructs the embedding tables.
    GameToVec();

    //! Constructs the embedding tables with given \p seed
    // \param seed The seed used when the embedding table is generated.
    GameToVec(const size_t seed);

    //! Default virtual destructor.
    virtual ~GameToVec() = default;

    //! Generates torch tensor from the effects
    //! \param effects The card effects.
    //! \return The encoded torch tensor from \p effects.
    virtual torch::Tensor EffectsToTensor(std::vector<Effect> effects);

    //! Generates torch tensor from the tasks
    //! \param tasks The card tasks
    //! \return The encoded torch tensor from \p tasks.
    virtual torch::Tensor TasksToTensor(std::vector<ITask*> tasks);

    //! Generates torch tensor from the entity
    //! \param entity The card context.
    //! \return The encoded torch tensor from \p entity.
    virtual torch::Tensor CardToTensor(Entity* entity);

    //! Generates torch tensor from game context.
    //! \param game The game context.
    //! \return The encoded torch tensor from \p game.
    virtual torch::Tensor GenerateTensor(const Game& game);

    /////////////////////////////////////////////
    static constexpr size_t CLIP_CARD_NORM = 64;
    static constexpr size_t CLIP_EFFECT_NORM = 8;

    /////////////////////////////////////////////
    std::vector<GameTag> EffectGameTag = {
        GameTag::INVALID,  GameTag::ATK,       GameTag::HEALTH,
        GameTag::TAUNT,    GameTag::POISONOUS, GameTag::DIVINE_SHIELD,
        GameTag::WINDFURY, GameTag::STEALTH
    };
    std::vector<EffectOperator> EffectOperatorTag = {
        EffectOperator::ADD, EffectOperator::MUL,
        EffectOperator::SET, EffectOperator::SUB
    };
    static constexpr size_t EffectVectorSize = 4;
    static constexpr size_t EffectGameTagSize = 8;
    static constexpr size_t EffectOperationTagSize = 4;
    static constexpr size_t EffectIndexSize = 
        EffectGameTagSize * EffectOperationTagSize;

    static constexpr size_t AuraVectorSize = 5;

    static constexpr size_t EnchantVectorSize = 4;

    static constexpr size_t EntityTypeVectorSize = 4;
    static constexpr size_t EntityTypeIndexSize = 16;
    static constexpr size_t TaskIdVectorSize = 4;
    static constexpr size_t TaskIdIndexSize = 27;
    static constexpr size_t TaskVectorSize = 
        EntityTypeVectorSize + TaskIdVectorSize;

    /////////////////////////////////////////////
    static constexpr size_t CardMetaSize = 3;
    static constexpr size_t AbilityVectorSize = 
        AuraVectorSize + EnchantVectorSize + TaskVectorSize + TaskVectorSize;
    static constexpr size_t CardVectorSize =
        CardMetaSize + AbilityVectorSize;

    /////////////////////////////////////////////
    static constexpr size_t PlayerMetaSize = 3;
    static constexpr size_t GameVectorSize =
        PlayerMetaSize + (CardVectorSize * (HAND_SIZE + 2 * FIELD_SIZE));

 private:
    size_t m_seed;

    //! embedding table for the card
    torch::nn::Embedding EffectEmbeddingTable = nullptr;
    torch::nn::Embedding EntityTypeEmbeddingTable = nullptr;
    torch::nn::Embedding TaskIdEmbeddingTable = nullptr;
};
}  // namespace RosettaTorch

#endif