// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/InputDataConverter.hpp>
#include <NeuralNet/NeuralNetworkImpl.hpp>

#include <torch/torch.h>
#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

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
    // torch::load(m_net, fileName);
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

void NeuralNetworkImpl::Train(const NeuralNetworkInputImpl& input,
                              const NeuralNetworkOutputImpl& output,
                              std::size_t batchSize, std::size_t epochs)
{
    // auto& xData = input.GetData();
    // auto& yData = output.GetData();
    // auto numData = xData.size(0);

    torch::optim::Adam optimizer(m_net->parameters(),
                                 torch::optim::AdamOptions(lr));

    for (std::size_t epoch = 0; epoch < epochs; ++epoch)
    {
        for (std::size_t batchIdx = 0; batchIdx < 0 / batchSize; ++batchIdx)
        {
            // Resets gradients
            optimizer.zero_grad();

            // Executes the model one the input data
            // ! you need to change the parameters, fitted into the model input
            auto prediction = m_net->forward(torch::Tensor(), torch::Tensor(),
                                             torch::Tensor());

            // Computes a loss value to judge the prediction of our model
            // ! you need to change the parameters, fitted into the model input
            auto loss = torch::mse_loss(prediction, torch::Tensor());

            // Do Back-propagation
            loss.backward();

            // Updates the parameters
            optimizer.step();

            // Saves the model
            Save(modelName);
        }
    }
}

std::pair<uint64_t, uint64_t> NeuralNetworkImpl::Verify(
    const NeuralNetworkInputImpl& input, const NeuralNetworkOutputImpl& output)
{
    return { 0, 0 };
}

double NeuralNetworkImpl::Predict(IInputGetter* input)
{
    torch::Tensor hero, minion, standalone;
    InputDataConverter().Convert(input, hero, minion, standalone);
    return Predict(hero, minion, standalone);
}

double NeuralNetworkImpl::Predict(const torch::Tensor& hero,
                                  const torch::Tensor& minion,
                                  const torch::Tensor& standalone)
{
    if (m_isRandom)
    {
        return Random::get<double>(-1.0, 1.0);
    }

    const auto prediction = m_net->forward(hero, minion, standalone);
    return prediction[0][0].item<double>();
}
}  // namespace RosettaTorch::NeuralNet