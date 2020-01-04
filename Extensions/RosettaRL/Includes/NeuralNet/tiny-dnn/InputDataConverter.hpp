// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_NEURAL_NET_INPUT_DATA_CONVERTER_HPP
#define ROSETTASTONE_TORCH_NEURAL_NET_INPUT_DATA_CONVERTER_HPP

#include <NeuralNet/IInputGetter.hpp>

#include <tiny_dnn/tiny_dnn.h>

namespace RosettaTorch::NeuralNet
{
//!
//! \brief InputDataConverter class.
//!
//! This class converts game data such as hero, minion and hand to
//! torch::Tensor using normalize method.
//!
class InputDataConverter
{
 public:
    //! Converts game data to torch::Tensor.
    //! \param getter The input getter to get the value of the field.
    //! \param data The tensor data to store using conversion.
    void Convert(const IInputGetter* getter, tiny_dnn::tensor_t& data);

 private:
    //! Returns the tensor data using conversion.
    //! \param getter The input getter to get the value of the field.
    //! \param data The tensor data to store using conversion.
    void GetInputData(const IInputGetter* getter, tiny_dnn::tensor_t& data) const;

    //! Adds the hero data to the container.
    //! \param side The side of the field.
    //! \param getter The input getter to get the value of the field.
    //! \param data The container to store data.
    void AddHeroData(FieldSide side, const IInputGetter* getter,
                     tiny_dnn::vec_t& data) const;

    //! Adds the minions data to the container.
    //! \param side The side of the field.
    //! \param getter The input getter to get the value of the field.
    //! \param data The container to store data.
    void AddMinionsData(FieldSide side, const IInputGetter* getter,
                        tiny_dnn::vec_t& data) const;

    //! Adds the minion data to the container.
    //! \param side The side of the field.
    //! \param getter The input getter to get the value of the field.
    //! \param minionIdx The index of the minion.
    //! \param data The container to store data.
    void AddMinionData(FieldSide side, const IInputGetter* getter,
                       int minionIdx, tiny_dnn::vec_t& data) const;

    //! Adds the minion placeholder data to the container.
    //! \param data The container to store data.
    void AddMinionPlaceholderData(tiny_dnn::vec_t& data) const;

    //! Adds the standalone data to the container.
    //! \param getter The input getter to get the value of the field.
    //! \param data The container to store data.
    void AddStandaloneData(const IInputGetter* getter,
                           tiny_dnn::vec_t& data) const;

    //! Normalizes the value from uniform distribution.
    //! \param v The value to normalize.
    //! \param min The minimum value of uniform distribution.
    //! \param max The maximum value of uniform distribution.
    //! \return The normalized value.
    float NormalizeFromUniformDist(double v, double min, double max) const;

    //! Normalizes the boolean value.
    //! \param v The value to normalize.
    //! \return The normalized value.
    float NormalizeBool(bool v) const;
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_INPUT_DATA_CONVERTER_HPP