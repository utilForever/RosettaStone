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
    //! Constructs embedding tables with given \p seed
    // \param seed The seed used when the embedding tables are generated.
    GameToVec(size_t seed = 13371337);

    //! Default virtual destructor.
    virtual ~GameToVec() = default;

    //! Generates torch tensor from game context.
    //! \param game The game context.
    //! \return The encoded torch tensor from \p game.
    virtual torch::Tensor GenerateTensor(const Game& game);

    /////////////////////////////////////////////
    static constexpr size_t AbilityVectorSize = 16;
    static constexpr size_t CardVectorSize =
        3 + AbilityVectorSize;

    /////////////////////////////////////////////
    static constexpr size_t GameVectorSize =
        3 + 24 * CardVectorSize;

 private:
    size_t m_seed;
};
}  // namespace RosettaTorch

#endif