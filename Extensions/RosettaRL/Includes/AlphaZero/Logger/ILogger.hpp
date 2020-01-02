// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_ILOGGER_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_ILOGGER_HPP

#include <AlphaZero/Logger/LoggerStream.hpp>

#include <functional>
#include <mutex>

namespace RosettaTorch::AlphaZero
{
//!
//! \brief ILogger class.
//!
//! This class is an interface for logger.
//!
class ILogger
{
 public:
    //! Virtual destructor.
    virtual ~ILogger() = default;

    //! Sets the stream and the text of prefix and postfix.
    //! \return The logger stream.
    virtual LoggerStream Info() = 0;

    //! Runs a function with logger stream as argument.
    //! \param func A function to run.
    void Info(const std::function<void(LoggerStream&)>& func)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        LoggerStream stream = Info();
        func(stream);
    }

    //! Prints text message using logger stream.
    //! Note that it is thread-safe, if not using any not-thread-safe interface.
    //! \param msg The text message to print.
    void Info(const std::string& msg)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        Info() << msg;
    }

 private:
    std::mutex m_mutex;
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_ILOGGER_HPP