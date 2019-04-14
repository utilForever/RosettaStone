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
    //! Constructs the embedding table with given \p seed
    // \param seed The seed used when the embedding table is generated.
    GameToVec(size_t seed = 1337);

    //! Constructs the embedding table with given \p seed, weigths
    // \param seed The seed used when the embedding table is generated.
    // \param weight The weight used when the embedding table is initialized.
    GameToVec(size_t seed, torch::Tensor weight);

    //! Default virtual destructor.
    virtual ~GameToVec() = default;

    //! Generates torch tensor from the entity
    //! \param entity The card context.
    //! \return The encoded torch tensor from \p entity.
    virtual torch::Tensor CardToTensor(const Entity* entity);

    //! Generates torch tensor from game context.
    //! \param game The game context.
    //! \return The encoded torch tensor from \p game.
    virtual torch::Tensor GenerateTensor(const Game& game);

    /////////////////////////////////////////////
    static constexpr size_t CardMetaSize = 3;
    static constexpr size_t AbilityVectorSize = 8;
    static constexpr size_t CardVectorSize =
        CardMetaSize + AbilityVectorSize;

    /////////////////////////////////////////////
    static constexpr size_t PlayerMetaSize = 3;
    static constexpr size_t GameVectorSize =
        PlayerMetaSize + (CardVectorSize * (HAND_SIZE + 2 * FIELD_SIZE));

 private:
    size_t m_seed;

    //! embedding table for the card
    torch::nn::Embedding CardVectorTable = nullptr;
};
}  // namespace RosettaTorch

#endif