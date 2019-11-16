// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <AlphaZero/SelfPlay/SelfPlayer.hpp>

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
}  // namespace RosettaTorch::AlphaZero::SelfPlay