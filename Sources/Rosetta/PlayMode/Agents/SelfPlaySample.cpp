// Copyright (c) 2026 Chris Ohk

#include <Rosetta/PlayMode/Agents/SelfPlaySample.hpp>

#include <Rosetta/Common/DefaultFloatEnvScope.hpp>
#include <Rosetta/PlayMode/Agents/PUCTSearch.hpp>
#include <Rosetta/PlayMode/Games/ReplayGame.hpp>

#include <algorithm>
#include <bit>
#include <cmath>
#include <compare>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <type_traits>

namespace RosettaStone::PlayMode
{
namespace
{
static_assert(ObservationSchema::VERSION == 1 && PolicySchema::VERSION == 1 &&
              SelfPlaySample::BYTE_SIZE == 26022);
static_assert(sizeof(float) == 4 && std::numeric_limits<float>::is_iec559);

constexpr auto ONE_BITS = std::bit_cast<std::uint32_t>(1.0f);

template <typename Float>
constexpr auto CanonicalBits(Float value)
{
    using Bits =
        std::conditional_t<sizeof(Float) == 4, std::uint32_t, std::uint64_t>;

    const auto bits = std::bit_cast<Bits>(value);
    // A floating zero comparison would also match subnormals when flushing is
    // enabled.
    constexpr auto negativeZero = std::bit_cast<Bits>(-Float{ 0 });

    return bits == negativeZero ? Bits{ 0 } : bits;
}

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

void Validate(const SelfPlaySample& sample)
{
    if (sample.observation.front() != ObservationSchema::VERSION)
    {
        throw std::invalid_argument("Invalid self-play observation version");
    }

    CheckMask(sample.legalMask);

    for (std::size_t i = 0; i < sample.policyTarget.size(); ++i)
    {
        if (!sample.legalMask[i] && CanonicalBits(sample.policyTarget[i]) != 0)
        {
            throw std::invalid_argument(
                "Masked self-play actions must have zero probability");
        }
    }

    if (!IsNormalizedVisitPolicy(sample.policyTarget))
    {
        throw std::invalid_argument(
            "Self-play probabilities must be in [0, 1] and sum to one");
    }

    const auto outcomeMagnitude =
        std::bit_cast<std::uint32_t>(sample.outcome) & 0x7fffffffu;

    if (outcomeMagnitude != 0 && outcomeMagnitude != ONE_BITS)
    {
        throw std::invalid_argument("Self-play outcome must be -1, 0 or +1");
    }
}

std::uint32_t LittleEndian(std::uint32_t word)
{
    static_assert(std::endian::native == std::endian::big ||
                  std::endian::native == std::endian::little);

    if constexpr (std::endian::native == std::endian::big)
    {
        return std::byteswap(word);
    }

    return word;
}

template <typename Float>
bool IsNormalizedRow(std::span<const Float> policy)
{
    if (policy.size() != PolicySchema::NUM_ACTIONS)
    {
        return false;
    }

    // Each bin counts whole multiples of the smallest subnormal times a power
    // of two.
    using Limits = std::numeric_limits<Float>;

    static_assert(Limits::is_iec559 && Limits::radix == 2);

    constexpr auto fractionBits = Limits::digits - 1;
    constexpr auto implicitBit = std::uint64_t{ 1 } << fractionBits;
    constexpr auto oneBits = CanonicalBits(Float{ 1 });

    std::array<std::uint64_t, Limits::digits - Limits::min_exponent> bins{};

    for (const Float p : policy)
    {
        const auto bits = CanonicalBits(p);

        if (bits > oneBits)
        {
            return false;
        }

        auto exponent = static_cast<std::size_t>(bits >> fractionBits);
        auto significand = bits & (implicitBit - 1);

        if (exponent != 0)
        {
            significand |= implicitBit;
            --exponent;
        }

        // With at most 4846 terms, 24-bit pieces keep each scaled bin within
        // uint64.
        while (significand != 0)
        {
            bins[exponent] += significand & 0xffffffu;
            significand >>= 24;
            exponent += 24;
        }
    }

    // Carry in base two to compare sum * 100000 with the two integer bounds.
    constexpr auto scale = SelfPlaySample::POLICY_SUM_SCALE;

    std::uint64_t whole = 0;
    bool fractional = false;

    for (const auto significands : bins)
    {
        whole += significands * scale;
        fractional |= (whole & 1u) != 0;
        whole >>= 1;
    }

    return whole >= scale - 1 &&
           (whole < scale + 1 || (whole == scale + 1 && !fractional));
}
}  // namespace

bool IsNormalizedVisitPolicy(std::span<const float> policy)
{
    return IsNormalizedRow(policy);
}

bool IsNormalizedVisitPolicy(std::span<const double> policy)
{
    return IsNormalizedRow(policy);
}

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

std::string SelfPlaySample::Serialize() const
{
    Validate(*this);

    std::string bytes(MAGIC);
    bytes.reserve(BYTE_SIZE);

    const auto writeWord = [&bytes](auto value) {
        const auto word = LittleEndian(std::bit_cast<std::uint32_t>(value));
        bytes.append(reinterpret_cast<const char*>(&word), sizeof(word));
    };

    writeWord(VERSION);
    writeWord(PolicySchema::VERSION);

    for (auto value : observation)
    {
        writeWord(value);
    }

    bytes.append(reinterpret_cast<const char*>(legalMask.data()),
                 legalMask.size());

    for (auto p : policyTarget)
    {
        writeWord(CanonicalBits(p));
    }

    writeWord(CanonicalBits(outcome));

    return bytes;
}

SelfPlaySample SelfPlaySample::Deserialize(std::string_view bytes)
{
    if (bytes.size() != BYTE_SIZE || !bytes.starts_with(MAGIC))
    {
        throw std::invalid_argument("Invalid self-play sample size or magic");
    }

    bytes.remove_prefix(MAGIC.size());

    const auto readWord = [&bytes]() {
        std::uint32_t word;

        std::memcpy(&word, bytes.data(), sizeof(word));
        bytes.remove_prefix(sizeof(word));

        return LittleEndian(word);
    };

    if (readWord() != VERSION || readWord() != PolicySchema::VERSION)
    {
        throw std::invalid_argument(
            "Unsupported self-play sample or policy version");
    }

    SelfPlaySample sample;

    for (auto& value : sample.observation)
    {
        value = std::bit_cast<std::int32_t>(readWord());
    }

    std::memcpy(sample.legalMask.data(), bytes.data(), sample.legalMask.size());
    bytes.remove_prefix(sample.legalMask.size());

    for (auto& p : sample.policyTarget)
    {
        p = std::bit_cast<float>(readWord());
    }

    sample.outcome = std::bit_cast<float>(readWord());

    Validate(sample);

    return sample;
}
}  // namespace RosettaStone::PlayMode
