// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_HPP
#define ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_HPP

#include <NeuralNet/NeuralNetworkInput.hpp>
#include <NeuralNet/NeuralNetworkOutput.hpp>

#include <string>

namespace RosettaTorch::NeuralNet
{
class NeuralNetworkImpl;

//!
//! \brief NeuralNetwork class.
//!
//! This class is interface between MCTS and PyTorch C++ API.
//!
class NeuralNetwork
{
 public:
    //! Constructor.
    NeuralNetwork();

    //! Destructor.
    ~NeuralNetwork();

    //! Deleted copy constructor.
    NeuralNetwork(const NeuralNetwork&) = delete;

    //! Move constructor.
    NeuralNetwork(NeuralNetwork&&) noexcept;

    //! Deleted copy assignment operator.
    NeuralNetwork& operator=(const NeuralNetwork&) = delete;

    //! Move assignment operator.
    NeuralNetwork& operator=(NeuralNetwork&&) noexcept;

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
    void CopyFrom(const NeuralNetwork& rhs);

    //! Trains neural network model.
    //! \param input The input layer of neural network model.
    //! \param output The output layer of neural network model.
    //! \param batchSize The size of batch.
    //! \param epoch The number of epoch to train for.
    void Train(const NeuralNetworkInput& input,
               const NeuralNetworkOutput& output, std::size_t batchSize,
               std::size_t epoch) const;

    //! Verifies neural network model.
    //! \param input The input layer of neural network model.
    //! \param output The output layer of neural network model.
    //! \return The value of correct and total.
    std::pair<uint64_t, uint64_t> Verify(
        const NeuralNetworkInput& input,
        const NeuralNetworkOutput& output) const;

    //! Predicts neural network model.
    //! \param input The input getter to convert data type to framework's.
    double Predict(IInputGetter* input) const;

 private:
    NeuralNetworkImpl* m_impl = nullptr;
};
}  // namespace RosettaTorch::NeuralNet

#endif  // ROSETTASTONE_TORCH_NEURAL_NET_NEURAL_NETWORK_HPP