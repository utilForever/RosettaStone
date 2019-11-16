// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_SELF_PLAYER_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_SELF_PLAYER_HPP

#include <AlphaZero/Logger/ILogger.hpp>

#include <Rosetta/Views/BoardRefView.hpp>

#include <chrono>

namespace RosettaTorch::AlphaZero::SelfPlay
{
//!
//! \brief AgentCallback class.
//!
//! This class is an agent callback for self-play of AlphaZero.
//!
class AgentCallback
{
 public:
    //! Constructs agent callback with given \p logger.
    //! \param logger The logger to write the log.
    AgentCallback(ILogger& logger);

    //! Processes something before calling Think() method.
    //! \param view The board ref view.
    void BeforeThink(const RosettaStone::BoardRefView& view);

    //! Processes something related to agent.
    //! \param view The board ref view.
    //! \param iteration The number of iteration.
    void Think(const RosettaStone::BoardRefView& view, std::uint64_t iteration);

    //! Processes something after calling Think() method.
    //! \param iteration The number of iteration.
    void AfterThink(std::uint64_t iteration);

 private:
    ILogger& m_logger;
    std::chrono::steady_clock::time_point m_nextShow;
    std::chrono::milliseconds m_showInterval;
};
}  // namespace RosettaTorch::AlphaZero::SelfPlay

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_SELF_PLAYER_HPP