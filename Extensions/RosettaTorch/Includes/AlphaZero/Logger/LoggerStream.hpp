// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_LOGGER_STREAM_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_LOGGER_STREAM_HPP

#include <iostream>
#include <string>
#include <utility>

namespace RosettaTorch::AlphaZero
{
//!
//! \brief LoggerStream class.
//!
//! This class is a helper for printing the log and holds prefix and postfix
//! to print before and after stream.
//!
class LoggerStream
{
 public:
    //! Constructs logger stream with given \p stream, \p prefix and \p postfix.
    //! \param stream The stream to print log.
    //! \param prefix The prefix to print before message.
    //! \param postfix The postfix to print after message.
    LoggerStream(std::ostream& stream, std::string prefix, std::string postfix)
        : m_stream(stream),
          m_prefix(std::move(prefix)),
          m_postfix(std::move(postfix))
    {
        m_stream << m_prefix;
    }

    //! Destructor.
    ~LoggerStream()
    {
        m_stream << m_postfix;
    }

    //! Operator overloading: operator<<.
    template <typename T>
    std::ostream& operator<<(T&& msg)
    {
        return m_stream << std::forward<T>(msg);
    }

 private:
    std::ostream& m_stream;
    std::string m_prefix;
    std::string m_postfix;
};
}  // namespace RosettaTorch::AlphaZero

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_LOGGER_STREAM_HPP