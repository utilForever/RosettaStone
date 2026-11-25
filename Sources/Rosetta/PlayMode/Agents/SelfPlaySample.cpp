// Copyright (c) 2026 Chris Ohk

#include <Rosetta/PlayMode/Agents/SelfPlaySample.hpp>

#include <Rosetta/Common/DefaultFloatEnvScope.hpp>
#include <Rosetta/PlayMode/Agents/PUCTSearch.hpp>
#include <Rosetta/PlayMode/Games/ReplayGame.hpp>

#include <algorithm>
#include <cmath>
#include <compare>
#include <limits>
#include <stdexcept>

namespace RosettaStone::PlayMode
{
namespace
{
static_assert(sizeof(float) == 4 && std::numeric_limits<float>::is_iec559);

void CheckMask(const PolicySchema::LegalMask& mask)
{
    if (std::ranges::max(mask) != 1)
    {
        throw std::invalid_argument(
            "Self-play mask must be binary with at least one legal action");
    }
}

// Several root actions can each carry a full size_t visit count.
struct VisitCount
{
    std::size_t high = 0;
    std::size_t low = 0;

    auto operator<=>(const VisitCount&) const = default;

    void Add(VisitCount other)
    {
        low += other.low;
        high += other.high + (low < other.low);
    }
};

float VisitProbability(std::size_t visits, VisitCount total)
{
    constexpr auto leadingBit = 1u << (std::numeric_limits<float>::digits - 1);

    if (total.high == 0 && total.low <= 2 * leadingBit)
    {
        // Both integers are exactly representable in binary32.
        return static_cast<float>(visits) / static_cast<float>(total.low);
    }

    if (visits == 0)
    {
        return 0;
    }

    // Binary long division keeps the exact remainder for the final rounding.
    VisitCount remainder{ 0, visits };
    std::uint32_t significand = 0;

    for (int exponent = 0;; --exponent)
    {
        significand <<= 1;

        if (remainder >= total)
        {
            remainder.high -= total.high + (remainder.low < total.low);
            remainder.low -= total.low;
            ++significand;
        }

        remainder.Add(remainder);

        if (significand >= leadingBit)
        {
            if (remainder > total || (remainder == total && (significand & 1u)))
            {
                ++significand;
            }

            return std::ldexp(static_cast<float>(significand), exponent);
        }
    }
}
}  // namespace

VisitPolicy NormalizeVisitCounts(const PolicySchema::LegalMask& legalMask,
                                 std::span<const PUCTNode> rootActions)
{
    CheckMask(legalMask);

    const DefaultFloatEnvScope environment;
    VisitCount total;
    auto remaining = legalMask;

    for (const auto& action : rootActions)
    {
        const auto index = action.actionIndex;

        if (index >= remaining.size() || !remaining[index])
        {
            throw std::invalid_argument("Expected distinct legal root actions");
        }

        remaining[index] = 0;
        total.Add({ 0, action.visitCount });
    }

    if (total == VisitCount{})
    {
        throw std::invalid_argument(
            "Self-play policy requires an action visit");
    }

    VisitPolicy policy{};

    for (const auto& action : rootActions)
    {
        policy[action.actionIndex] = VisitProbability(action.visitCount, total);
    }

    return policy;
}

float SelfPlayOutcome(const ReplayGame& game, PlayerType observationPlayer)
{
    if (game.GetGame().state != State::COMPLETE)
    {
        throw std::invalid_argument(
            "Self-play outcome requires a finished game");
    }

    return static_cast<float>(game.GetReward(observationPlayer));
}
}  // namespace RosettaStone::PlayMode
