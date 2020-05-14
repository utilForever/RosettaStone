// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_MCTS_GAME_DATA_BRIDGE_HPP
#define ROSETTASTONE_TORCH_MCTS_GAME_DATA_BRIDGE_HPP

#include <NeuralNet/IInputGetter.hpp>

#include <Rosetta/PlayMode/Games/Game.hpp>

namespace RosettaTorch::NeuralNet
{
//!
//! \brief GameDataBridge class.
//!
//! This class is bridge class between game and neural network and
//! inherits from IInputGetter class.
//!
class GameDataBridge : public IInputGetter
{
 public:
    //! Clears and initializes member variables.
    //! \param game The game context.
    void Reset(const RosettaStone::PlayMode::Game& game);

    //! Returns the value of the field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldSide The side of the field.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \return The value of the field.
    double GetField(FieldSide fieldSide, FieldType fieldType,
                    int arg = 0) const override;

    //! Returns the value of the side field.
    //! Note that boolean value is 1 for true, 0 for false.
    //! \param fieldType The type of the field.
    //! \param arg The argument such as the index of minion in field zone.
    //! \return The value of the field.
    double GetSideField(FieldType fieldType, int arg,
                        const RosettaStone::PlayMode::Player* player) const;

 private:
    const RosettaStone::PlayMode::Game* m_game = nullptr;
    std::vector<RosettaStone::PlayMode::Entity*> m_playableCards;
    bool m_canUseHeroPower = false;
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_MCTS_GAME_DATA_BRIDGE_HPP
