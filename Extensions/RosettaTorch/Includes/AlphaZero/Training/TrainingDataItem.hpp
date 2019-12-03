// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINING_DATA_ITEM_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINING_DATA_ITEM_HPP

#include <Judges/JSON/Reader.hpp>

namespace RosettaTorch::AlphaZero
{
//!
//! \brief TrainingDataItem class.
//!
//! This class holds a item for training data.
//!
class TrainingDataItem
{
 public:
    //! Constructs training data item with given \p input and \p label.
    //! \param input The getter for input of the neural network.
    //! \param label The label of the training data.
    TrainingDataItem(Judges::JSON::NeuralNetInputGetter input, int label);

    //! Gets the getter for input of the neural network.
    //! \return The getter for input of the neural network.
    const Judges::JSON::NeuralNetInputGetter& GetInput() const;

    //! Gets the label of the training data.
    //! \return The label of the training data.
    int GetLabel() const;

 private:
    Judges::JSON::NeuralNetInputGetter m_input;
    int m_label;
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_TRAINING_DATA_ITEM_HPP