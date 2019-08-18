// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/NeuralNetworkImpl.hpp>

namespace RosettaTorch::NeuralNet
{
void NeuralNetworkImpl::CreateWithRandomWeights(const std::string& fileName)
{
}

void NeuralNetworkImpl::Save(const std::string& fileName) const
{
    torch::save(m_net, fileName);
}

void NeuralNetworkImpl::Load(const std::string& fileName, bool isRandom)
{
    torch::load(m_net, fileName);
    m_isRandom = isRandom;
}

bool NeuralNetworkImpl::IsRandom() const
{
    return m_isRandom;
}

void NeuralNetworkImpl::CopyFrom(const NeuralNetworkImpl& rhs)
{
    std::string tempFile = std::tmpnam(nullptr);
    torch::save(rhs.m_net, tempFile);
    torch::load(m_net, tempFile);
    m_isRandom = rhs.m_isRandom;
    std::remove(tempFile.c_str());
}

void NeuralNetworkImpl::Train(const NeuralNetworkInput& input,
                              const NeuralNetworkOutput& output,
                              size_t batchSize, int epochs)
{
    auto xData = input.GetData();
    auto yData = output.GetData();

    auto numData = xData.shape[0]; // number of data

    for (std::size_t epoch = 0; epoch < epochs; ++epoch)
    {
        for (std::size_t batchIdx = 0; batchIdx < numData / batchSize; ++batchIdx)
        {
            // Resets gradients
            optimizer.zero_grad();

            // Executes the model one the input data 
            auto prediction = m_net.forward(
                xData[:, batchSize * batchIdx:batchSize * (batchIdx + 1)]);

            // Computes a loss value to judge the prediction of our model
            auto loss = torch::mse_loss(
                prediction, 
                yData[:, batchSize * batchIdx:batchSize * (batchIdx + 1)]);

            // Do Back-propagation
            loss.backward();

            // Updates the parameters
            optimizer.step();

            // Saves the model
            Save("model.pt");
        }
    }
}

std::pair<uint64_t, uint64_t> NeuralNetworkImpl::Verify(
    const NeuralNetworkInput& input, const NeuralNetworkOutput& output)
{
    return { 0, 0 };
}

double NeuralNetworkImpl::Predict(IInputGetter* input)
{
    return 0.0;
}

void NeuralNetworkImpl::Predict(const NeuralNetworkInputImpl& input,
                                std::vector<double>& results)
{
}
}  // namespace RosettaTorch::NeuralNet