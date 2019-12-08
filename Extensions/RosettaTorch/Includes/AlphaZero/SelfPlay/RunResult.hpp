// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_RUN_RESULT_HPP
#define ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_RUN_RESULT_HPP

namespace RosettaTorch::AlphaZero::SelfPlay
{
//!
//! \brief RunResult struct.
//!
//! This struct holds the result of the self-play runner.
//!
struct RunResult
{
    //! Operator overloading: operator+=.
    RunResult& operator+=(const RunResult& rhs)
    {
        generatedCount += rhs.generatedCount;
        return *this;
    }

    //! Clears all variables.
    void Clear()
    {
        generatedCount = 0;
    }

    std::size_t generatedCount = 0;
};
}  // namespace RosettaTorch::AlphaZero::SelfPlay

#endif  // ROSETTASTONE_TORCH_ALPHA_ZERO_SELF_PLAY_RUN_RESULT_HPP