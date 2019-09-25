// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/InputDataConverter.hpp>
#include <NeuralNet/NeuralNetworkImpl.hpp>

#include <Rosetta/Commons/Macros.hpp>

#include <torch/torch.h>
#include <effolkronium/random.hpp>

#if !defined(ROSETTASTONE_WINDOWS)
#include <stdlib.h>
#include <unistd.h>
#endif

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
#if defined(ROSETTASTONE_WINDOWS)
    std::string tempFile = std::tmpnam(nullptr);
#else
    char tempFile[] = "/tempXXXXXX";
    int fd = mkstemp(tempFile);
    if (fd == -1)
    {
        exit(EXIT_FAILURE);
    }
#endif
    torch::save(rhs.m_net, tempFile);
    torch::load(m_net, tempFile);
    m_isRandom = rhs.m_isRandom;
#if defined(ROSETTASTONE_WINDOWS)
    std::remove(tempFile.c_str());
#else
    unlink(tempFile);
#endif
}

void NeuralNetworkImpl::Train(const NeuralNetworkInputImpl& input,
                              const NeuralNetworkOutputImpl& output,
                              std::size_t epochs)
{
    const auto& inputData = input.GetData();
    const auto& outputData = output.GetData();

    torch::optim::Adam optimizer(m_net->parameters(),
                                 torch::optim::AdamOptions(lr));

    for (std::size_t epoch = 0; epoch < epochs; ++epoch)
    {
        for (std::size_t idx = 0; idx < inputData.size(); ++idx)
        {
            const auto outData = const_cast<float*>(std::data(outputData[idx]));
            const auto outDataSize = static_cast<int>(outputData[idx].size());

            // Resets gradients
            optimizer.zero_grad();

            // Executes the model one the input data
            // ! you need to change the parameters, fitted into the model input
            auto prediction = m_net->forward(
                inputData[idx][0], inputData[idx][1], inputData[idx][2]);

            // Computes a loss value to judge the prediction of our model
            // ! you need to change the parameters, fitted into the model input
            auto loss = torch::mse_loss(
                prediction, torch::from_blob(outData, { 1, outDataSize }));

            // Do back-propagation
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
    const auto& inputData = input.GetData();
    const auto& outputData = output.GetData();

    std::uint64_t correct = 0, total = inputData.size();

    for (std::size_t idx = 0; idx < inputData.size(); ++idx)
    {
        auto result = m_net->forward(inputData[idx][0], inputData[idx][1],
                                     inputData[idx][2]);
        bool predictWin = result[0][0].item<double>() > 0.0;
        bool actualWin = outputData[idx][0] > 0.0;

        if (predictWin == actualWin)
        {
            ++correct;
        }
    }

    return { correct, total };
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