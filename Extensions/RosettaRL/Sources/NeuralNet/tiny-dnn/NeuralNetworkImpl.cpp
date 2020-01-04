// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/tiny-dnn/InputDataConverter.hpp>
#include <NeuralNet/tiny-dnn/NeuralNetworkImpl.hpp>

#include <Rosetta/Commons/Macros.hpp>

#include <tiny_dnn/tiny_dnn.h>
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
    constexpr static int HERO_IN_DIM = 1;
    constexpr static int HERO_OUT_DIM = 1;

    constexpr static int MINION_IN_DIM = 7;
    constexpr static int MINION_OUT_DIM = 3;

    constexpr static int MINION_COUNT = 7;

    constexpr static int STANDALONE_IN_DIM = 17;

    // 2 = my hero, opponent hero
    tiny_dnn::layers::input heroesIn(tiny_dnn::shape3d(HERO_IN_DIM, 2, 1));

    tiny_dnn::layers::conv heroConv1(HERO_IN_DIM, 2, HERO_IN_DIM, 1, 1,
                                     HERO_OUT_DIM);
    // out: 1 * 2 * HERO_OUT_DIM
    heroesIn << heroConv1;

    auto heroConv1a = tiny_dnn::activation::leaky_relu();
    // out: 1 * 2 * HERO_OUT_DIM
    heroConv1 << heroConv1a;

    // MINION_COUNT * 2 = my minions, opponent minions
    tiny_dnn::layers::input minionsIn(
        tiny_dnn::shape3d(MINION_IN_DIM, MINION_COUNT * 2, 1));

    tiny_dnn::layers::conv minionConv1(MINION_IN_DIM, MINION_COUNT * 2,
                                       MINION_IN_DIM, 1, 1, 1 * MINION_OUT_DIM);
    // out: 1 * (MINION_COUNT * 2) * MINION_OUT_DIM
    minionsIn << minionConv1;

    auto minionConv1a = tiny_dnn::activation::leaky_relu();
    // out: 1 * (MINION_COUNT * 2) * MINION_OUT_DIM
    minionConv1 << minionConv1a;

    tiny_dnn::layers::input standaloneIn(
        tiny_dnn::shape3d(1, 1, STANDALONE_IN_DIM));

    // Reshape to 1x1
    auto concat = tiny_dnn::layers::concat(
        { tiny_dnn::shape3d(1, 1, 2 * HERO_OUT_DIM),
          tiny_dnn::shape3d(1, 1, MINION_COUNT * 2 * MINION_OUT_DIM),
          standaloneIn.out_shape()[0] });
    (heroConv1a, minionConv1a, standaloneIn) << concat;

    auto fc1 = tiny_dnn::fully_connected_layer(
        2 * HERO_OUT_DIM + 2 * MINION_COUNT * MINION_OUT_DIM +
            STANDALONE_IN_DIM,
        10);
    concat << fc1;

    auto fc1a = tiny_dnn::activation::leaky_relu();
    auto fc2 = tiny_dnn::fully_connected_layer(10, 1);
    fc1 << fc1a << fc2;

    auto output = tiny_dnn::activation::tanh(1);
    fc2 << output;

    tiny_dnn::network<tiny_dnn::graph> net;
    tiny_dnn::construct_graph(net, { &heroesIn, &minionsIn, &standaloneIn },
                              { &output });

    net.init_weight();

    net.save(fileName);
}

void NeuralNetworkImpl::Save(const std::string& fileName) const
{
    m_net.save(fileName);
}

void NeuralNetworkImpl::Load(const std::string& fileName, bool isRandom)
{
    m_net.load(fileName);
    m_isRandom = isRandom;
}

bool NeuralNetworkImpl::IsRandom() const
{
    return m_isRandom;
}

void NeuralNetworkImpl::CopyFrom(const NeuralNetworkImpl& rhs)
{
#if defined(ROSETTASTONE_WINDOWS)
#pragma warning(push)
#pragma warning(disable: 4996)
    std::string tempFile = std::tmpnam(nullptr);
#pragma warning(pop)
#else
    char tempFile[] = "/tempXXXXXX";
    int fd = mkstemp(tempFile);
    if (fd == -1)
    {
        exit(EXIT_FAILURE);
    }
#endif
    rhs.m_net.save(tempFile);
    m_net.load(tempFile);
    m_isRandom = rhs.m_isRandom;
#if defined(ROSETTASTONE_WINDOWS)
    std::remove(tempFile.c_str());
#else
    unlink(tempFile);
#endif
}

void NeuralNetworkImpl::Train(const NeuralNetworkInputImpl& input,
                              const NeuralNetworkOutputImpl& output,
                              std::size_t batchSize, std::size_t epoch)
{
    tiny_dnn::adam opt;
    m_net.fit<tiny_dnn::mse>(
        opt, input.GetData(), output.GetData(), batchSize, epoch, []() {},
        []() {});
}

std::pair<uint64_t, uint64_t> NeuralNetworkImpl::Verify(
    const NeuralNetworkInputImpl& input, const NeuralNetworkOutputImpl& output)
{
    const auto& inputData = input.GetData();
    const auto& outputData = output.GetData();

    std::uint64_t correct = 0, total = inputData.size();

    for (std::size_t idx = 0; idx < inputData.size(); ++idx)
    {
        auto result = m_net.predict(inputData[idx]);
        const bool predictWin = result[0][0] > 0.0;
        const bool actualWin = outputData[idx][0] > 0.0;

        if (predictWin == actualWin)
        {
            ++correct;
        }
    }

    return { correct, total };
}

double NeuralNetworkImpl::Predict(IInputGetter* input)
{
    tiny_dnn::tensor_t data;
    InputDataConverter().Convert(input, data);
    return Predict(data);
}

double NeuralNetworkImpl::Predict(const tiny_dnn::tensor_t& data)
{
    if (m_isRandom)
    {
        return Random::get<double>(-1.0, 1.0);
    }

    return m_net.predict(data)[0][0];
}

void NeuralNetworkImpl::Predict(const NeuralNetworkInputImpl* input,
                                std::vector<double>& results)
{
    const auto& inputData = input->GetData();
    results.clear();
    results.reserve(inputData.size());

    for (std::size_t idx = 0; idx < inputData.size(); ++idx)
    {
        results.push_back(Predict(inputData[0]));
    }
}
}  // namespace RosettaTorch::NeuralNet