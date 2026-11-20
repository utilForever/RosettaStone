// Copyright (c) 2026 Chris Ohk

#ifndef ROSETTASTONE_RL_TESTS_TEMPORARY_ARTIFACT_HPP
#define ROSETTASTONE_RL_TESTS_TEMPORARY_ARTIFACT_HPP

#include <chrono>
#include <filesystem>
#include <string>

namespace RosettaStone::RL::Tests
{
struct TemporaryArtifact
{
    std::filesystem::path path =
        std::filesystem::temp_directory_path() /
        ("rosetta-weights-" +
         std::to_string(
             std::chrono::steady_clock::now().time_since_epoch().count()) +
         ".pt");

    ~TemporaryArtifact()
    {
        std::error_code error;
        std::filesystem::remove(path, error);
    }
};
}  // namespace RosettaStone::RL::Tests

#endif  // ROSETTASTONE_RL_TESTS_TEMPORARY_ARTIFACT_HPP
