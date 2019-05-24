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

    //! Constructs the embedding tables with given \p seed.
    //! \param seed The seed used when the embedding table is generated.
    explicit GameToVec(std::size_t seed);

    //! Default virtual destructor.
    virtual ~GameToVec() = default;

    //! Generates torch tensor from the effects.
    //! \param effects The card effects.
    //! \return The encoded torch tensor from \p effects.
    virtual torch::Tensor EffectsToTensor(std::vector<Effect> effects);

    //! Generates torch tensor from a list of card task.
    //! \param tasks The card tasks.
    //! \return The encoded torch tensor from \p tasks.
    virtual torch::Tensor TasksToTensor(std::vector<ITask*> tasks);

    //! Generates torch tensor from the entity.
    //! \param entity The card context.
    //! \return The encoded torch tensor from \p entity.
    virtual torch::Tensor CardToTensor(Entity* entity);

    //! Generates torch tensor from game context.
    //! \param game The game context.
    //! \return The encoded torch tensor from \p game.
    virtual torch::Tensor GenerateTensor(const Game& game);

    //! Returns the effect embedding table.
    //! \return The effect embedding table.
    torch::nn::Embedding GetEffectEmbeddingTable() const;

    //! Returns the entity type embedding table.
    //! \return The entity type embedding table.
    torch::nn::Embedding GetEntityTypeEmbeddingTable();

    //! Returns The task ID embedding table.
    //! \return The task ID embedding table.
    torch::nn::Embedding GetTaskIDEmbeddingTable() const;

    static constexpr size_t CLIP_CARD_NORM = 64;
    static constexpr size_t CLIP_EFFECT_NORM = 8;

    std::vector<GameTag> EffectGameTag = {
        GameTag::INVALID,  GameTag::ATK,       GameTag::HEALTH,
        GameTag::TAUNT,    GameTag::POISONOUS, GameTag::DIVINE_SHIELD,
        GameTag::WINDFURY, GameTag::STEALTH
    };
    std::vector<EffectOperator> EffectOperatorTag = { EffectOperator::ADD,
                                                      EffectOperator::MUL,
                                                      EffectOperator::SET,
                                                      EffectOperator::SUB };
    static constexpr std::size_t EffectVectorSize = 4;
    static constexpr std::size_t EffectGameTagSize = 8;
    static constexpr std::size_t EffectOperationTagSize = 4;
    static constexpr std::size_t EffectIndexSize =
        EffectGameTagSize * EffectOperationTagSize;

    static constexpr std::size_t AuraVectorSize = 5;

    static constexpr std::size_t EnchantVectorSize = 4;

    static constexpr std::size_t EntityTypeVectorSize = 4;
    static constexpr std::size_t EntityTypeIndexSize = 16;
    static constexpr std::size_t TaskIdVectorSize = 4;
    static constexpr std::size_t TaskIdIndexSize = 27;
    static constexpr std::size_t TaskVectorSize =
        EntityTypeVectorSize + TaskIdVectorSize;

    static constexpr std::size_t CardMetaSize = 3;
    static constexpr std::size_t AbilityVectorSize =
        AuraVectorSize + EnchantVectorSize + TaskVectorSize + TaskVectorSize;
    static constexpr std::size_t CardVectorSize =
        CardMetaSize + AbilityVectorSize;

    static constexpr std::size_t PlayerMetaSize = 3;
    static constexpr std::size_t GameVectorSize =
        PlayerMetaSize +
        (CardVectorSize * (MAX_HAND_SIZE + 2 * MAX_FIELD_SIZE));

 private:
    std::size_t m_seed;

    //! Embedding table for the card
    torch::nn::Embedding m_effectEmbeddingTable = nullptr;
    torch::nn::Embedding m_entityTypeEmbeddingTable = nullptr;
    torch::nn::Embedding m_taskIDEmbeddingTable = nullptr;
};
}  // namespace RosettaTorch

#endif