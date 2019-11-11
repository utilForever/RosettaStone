// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_TYPES_HPP
#define ROSETTASTONE_TORCH_MCTS_TYPES_HPP

#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Enums/GameEnums.hpp>

using namespace RosettaStone;

namespace RosettaTorch::MCTS
{
//!
//! \brief StateValue class.
//!
//! This class stores value that indicates which player won.
//! If player 1 won the game, the value is 1.0.
//! If player 1 lose the game, the value is -1.0.
//! If player 1 drew the game, the value is 0.0.
//!
class StateValue
{
 public:
    //! Returns the value that indicates player won.
    //! \param type The type of the player.
    //! \return The value that indicates player won.
    float GetValue(PlayerType type) const;

    //! Sets the value that indicates player won.
    //! \param valueForCurPlayer The value for current player.
    //! \param type The type of the player.
    void SetValue(float valueForCurPlayer, PlayerType type);

    //! Sets the value that indicates player won.
    //! \param type The type of the player.
    //! \param state The play state of the game.
    void SetValue(PlayerType type, PlayState state);

 private:
    float m_value = 0.0f;
};
}  // namespace RosettaTorch::MCTS

#endif  // ROSETTASTONE_TORCH_MCTS_TYPES_HPP