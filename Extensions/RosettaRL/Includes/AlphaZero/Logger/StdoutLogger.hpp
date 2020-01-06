// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_STDOUT_LOGGER_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_STDOUT_LOGGER_HPP

#include <AlphaZero/Logger/ILogger.hpp>

namespace RosettaTorch::AlphaZero
{
//!
//! \brief ILogger class.
//!
//! This class is a logger that uses std::cout.
//!
class StdoutLogger : public ILogger
{
 public:
    LoggerStream Info() override
    {
        return LoggerStream(std::cout, "[INFO] ", "\n");
    }
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_STDOUT_LOGGER_HPP