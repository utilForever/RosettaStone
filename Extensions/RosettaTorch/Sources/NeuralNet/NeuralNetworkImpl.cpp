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
                              size_t batchSize, int epoch)
{
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