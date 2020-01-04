// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/NeuralNetwork.hpp>

#if defined(ROSETTATORCH_ML_LIBRARY_LIBTORCH)
#include <NeuralNet/libtorch/NeuralNetworkImpl.hpp>
#elif defined(ROSETTARL_ML_LIBRARY_TINY_DNN)
#include <NeuralNet/tiny-dnn/NeuralNetworkImpl.hpp>
#endif

namespace RosettaTorch::NeuralNet
{
NeuralNetwork::NeuralNetwork() : m_impl(new NeuralNetworkImpl())
{
    // Do nothing
}

NeuralNetwork::~NeuralNetwork()
{
    delete m_impl;
}

NeuralNetwork::NeuralNetwork(NeuralNetwork&& rhs) noexcept
{
    std::swap(m_impl, rhs.m_impl);
}

NeuralNetwork& NeuralNetwork::operator=(NeuralNetwork&& rhs) noexcept
{
    if (m_impl)
    {
        delete m_impl;
        m_impl = nullptr;
    }

    std::swap(m_impl, rhs.m_impl);
    return *this;
}

void NeuralNetwork::CreateWithRandomWeights(const std::string& fileName)
{
    return NeuralNetworkImpl::CreateWithRandomWeights(fileName);
}

void NeuralNetwork::Save(const std::string& fileName) const
{
    m_impl->Save(fileName);
}

void NeuralNetwork::Load(const std::string& fileName, bool isRandom)
{
    // Reload neural net
    delete m_impl;
    m_impl = new NeuralNetworkImpl();

    m_impl->Load(fileName, isRandom);
}

bool NeuralNetwork::IsRandom() const
{
    return m_impl->IsRandom();
}

void NeuralNetwork::CopyFrom(const NeuralNetwork& rhs)
{
    // Reload neural net
    delete m_impl;
    m_impl = new NeuralNetworkImpl();

    m_impl->CopyFrom(*rhs.m_impl);
}

void NeuralNetwork::Train(const NeuralNetworkInput& input,
                          const NeuralNetworkOutput& output,
                          std::size_t batchSize, std::size_t epoch) const
{
    return m_impl->Train(*input.m_impl, *output.m_impl, batchSize, epoch);
}

std::pair<uint64_t, uint64_t> NeuralNetwork::Verify(
    const NeuralNetworkInput& input, const NeuralNetworkOutput& output) const
{
    return m_impl->Verify(*input.m_impl, *output.m_impl);
}

double NeuralNetwork::Predict(IInputGetter* input) const
{
    return m_impl->Predict(input);
}
}  // namespace RosettaTorch::NeuralNet