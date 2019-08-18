// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_IMPL_HPP
#define ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_IMPL_HPP

#include <NeuralNet/NeuralNetworkInput.hpp>
#include <NeuralNet/NeuralNetworkOutput.hpp>

#include <torch/torch.h>

#include <string>

namespace RosettaTorch::NeuralNet
{
//!
//! \brief NeuralNetworkImpl class.
//!
//! This class is implementation code of NeuralNetwork class.
//!
class NeuralNetworkImpl
{
 public:
    //! Creates neural network model with random weights.
    //! \param fileName The file name of neural network model to save.
    static void CreateWithRandomWeights(const std::string& fileName);

    //! Saves neural network model to \p fileName.
    //! \param fileName The file name of neural network model to save.
    void Save(const std::string& fileName) const;

    //! Loads neural network model from \p fileName.
    //! \param fileName The file name of neural network model to load.
    //! \param isRandom The flag indicates that whether it is random network.
    void Load(const std::string& fileName, bool isRandom = false);

    //! Returns the flag indicates that whether it is random network.
    //! \return The flag indicates that whether it is random network.
    bool IsRandom() const;

    //! Copies the contents from reference \p rhs.
    //! \param rhs The source to copy the content.
    void CopyFrom(const NeuralNetworkImpl& rhs);

    //! Trains neural network model.
    //! \param input The input layer of neural network model.
    //! \param output The output layer of neural network model.
    //! \param batchSize The training batch size.
    //! \param epoch The number of epochs to train for.
    void Train(const NeuralNetworkInput& input,
               const NeuralNetworkOutput& output, size_t batchSize, int epoch);

    //! Verifies neural network model.
    //! \param input The input layer of neural network model.
    //! \param output The output layer of neural network model.
    //! \return The value of correct and total.
    std::pair<uint64_t, uint64_t> Verify(const NeuralNetworkInput& input,
                                         const NeuralNetworkOutput& output);

    //! Predicts neural network model.
    //! \param input The input getter to convert data type to framework's.
    double Predict(IInputGetter* input);

    //! Predicts neural network model.
    //! \param input The implementation of neural network input.
    //! \param results The result of prediction.
    void Predict(const NeuralNetworkInputImpl& input,
                 std::vector<double>& results);

 private:
    std::shared_ptr<torch::nn::Module> m_net = nullptr;
    bool m_isRandom = false;
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_IMPL_HPP