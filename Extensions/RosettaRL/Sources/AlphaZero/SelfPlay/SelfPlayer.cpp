// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/SelfPlay/SelfPlayer.hpp>

#include <Rosetta/Commons/Macros.hpp>

#include <fstream>

#if !defined(ROSETTASTONE_WINDOWS)
#include <stdlib.h>
#include <unistd.h>
#endif

namespace RosettaTorch::AlphaZero::SelfPlay
{
AgentCallback::AgentCallback(ILogger& logger)
    : m_logger(logger), m_showInterval(std::chrono::milliseconds(5000))
{
    // Do nothing
}

void AgentCallback::BeforeThink(const RosettaStone::BoardRefView& view)
{
    m_logger.Info([&](auto& stream) {
        stream << "Start think... Turn: " << view.GetTurn() << ". ";
    });

    m_nextShow = std::chrono::steady_clock::now() + m_showInterval;
}

void AgentCallback::Think(
    [[maybe_unused]] const RosettaStone::BoardRefView& view,
    std::uint64_t iteration)
{
    const auto now = std::chrono::steady_clock::now();

    if (now > m_nextShow)
    {
        m_logger.Info(
            [&](auto& stream) { stream << "Iterations: " << iteration; });

        m_nextShow = now + m_showInterval;
    }
}

void AgentCallback::AfterThink([[maybe_unused]] std::uint64_t iteration)
{
    // Do nothing
}

SelfPlayer::SelfPlayer(ILogger& logger) : m_logger(logger)
{
    // Do nothing
}

SelfPlayer::~SelfPlayer()
{
    RemoveTempFile();
}

void SelfPlayer::BeforeRun(TrainingData& data,
                           const NeuralNet::NeuralNetwork& neuralNet,
                           const RunOptions& config)
{
    m_data = &data;

    RemoveTempFile();
#if defined(ROSETTASTONE_WINDOWS)
    m_tempFile = std::tmpnam(nullptr);
#else
    char tempFile[] = "/tempXXXXXX";
    int fd = mkstemp(tempFile);
    if (fd == -1)
    {
        exit(EXIT_FAILURE);
    }
#endif
    neuralNet.Save(m_tempFile);

    m_result.Clear();

    m_config = config;
    m_config.agentConfig.mcts.neuralNetPath = m_tempFile;
    m_config.agentConfig.mcts.isNeuralNetRandom = neuralNet.IsRandom();
}

RunResult SelfPlayer::AfterRun()
{
    RemoveTempFile();
    return m_result;
}

void SelfPlayer::RemoveTempFile()
{
    if (!m_tempFile.empty())
    {
        std::remove(m_tempFile.c_str());
        m_tempFile.clear();
    }
}

void SelfPlayer::SaveJSON(const nlohmann::json& json)
{
    if (m_config.saveDir.empty())
    {
        return;
    }

    time_t now;
    time(&now);

    struct tm timeinfo
    {
    };
#ifdef _MSC_VER
    localtime_s(&timeinfo, &now);
#else
    localtime_r(&now, &timeinfo);
#endif

    char buffer[80];
    strftime(buffer, 80, "%Y%m%d-%H%M%S", &timeinfo);

    std::ostringstream ss;
    const int postfix = Random::get<int>(0, 89999) + 10000;
    ss << m_config.saveDir << "/" << buffer << "-" << postfix << ".json";
    const std::string fileName = ss.str();

    std::ofstream fs(fileName, std::ofstream::trunc);
    fs << json;
    fs.close();
}
}  // namespace RosettaTorch::AlphaZero::SelfPlay