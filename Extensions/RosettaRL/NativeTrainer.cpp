// Copyright (c) 2026 Chris Ohk

#include <RosettaRL/NativeTrainer.hpp>

#include <Rosetta/PlayMode/Agents/SelfPlaySample.hpp>

#include <torch/serialize.h>

#include <bit>
#include <chrono>
#include <cmath>
#include <fstream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

namespace RosettaStone::RL
{
namespace
{
void CheckTarget(const torch::Tensor& target, const torch::Tensor& prediction,
                 const char* name)
{
    TORCH_CHECK(target.defined() && target.sizes() == prediction.sizes(), name,
                " must have shape ", prediction.sizes());
    TORCH_CHECK(target.layout() == torch::kStrided &&
                    target.scalar_type() == prediction.scalar_type() &&
                    target.device() == prediction.device(),
                name,
                " must be a dense tensor with the model's dtype and device");
}

template <typename Float>
bool HasNormalizedCpuRows(const torch::Tensor& rows)
{
    constexpr auto width = PlayMode::PolicySchema::NUM_ACTIONS;
    const auto* row = rows.const_data_ptr<Float>();

    for (std::int64_t i = 0; i < rows.size(0); ++i, row += width)
    {
        if (!PlayMode::IsNormalizedVisitPolicy({ row, width }))
        {
            return false;
        }
    }

    return true;
}

std::int64_t OneBits(bool binary32)
{
    return binary32 ? std::bit_cast<std::int32_t>(1.0f)
                    : std::bit_cast<std::int64_t>(1.0);
}

torch::Tensor ValidationValues(const torch::Tensor& target)
{
    TORCH_CHECK(target.is_floating_point(),
                "Training targets must be real floating-point tensors");

    const auto dtype = target.scalar_type() == torch::kFloat64
                           ? torch::kFloat64
                           : torch::kFloat32;
    return target.detach().resolve_neg().to(dtype).contiguous();
}

bool HasNormalizedPolicyRows(const torch::Tensor& policy)
{
    constexpr auto tolerance = PlayMode::SelfPlaySample::POLICY_SUM_TOLERANCE;

    if (policy.dim() != 2 ||
        policy.size(1) != PlayMode::PolicySchema::NUM_ACTIONS)
    {
        return false;
    }

    auto rows = ValidationValues(policy);
    const bool binary32 = rows.scalar_type() == torch::kFloat32;

    if (rows.is_cuda())
    {
        // Float64 reduction error for 4846 nonnegative terms near one is <
        // 1e-12. Only rows outside this safe interior need an exact CPU check.
        const auto bits = rows.view(binary32 ? torch::kInt32 : torch::kInt64);
        const auto inRange =
            bits.ge(0).logical_and(bits.le(OneBits(binary32))).all(1);
        const auto interior =
            (rows.sum(1, false, torch::kFloat64) - 1).abs().lt(tolerance / 2);

        rows = rows.index({ inRange.logical_and(interior).logical_not() });
    }

    rows = rows.cpu();
    return binary32 ? HasNormalizedCpuRows<float>(rows)
                    : HasNormalizedCpuRows<double>(rows);
}

bool HasValidOutcomes(const torch::Tensor& outcomes)
{
    const auto values = ValidationValues(outcomes);
    const bool binary32 = values.scalar_type() == torch::kFloat32;
    const auto bits = values.view(binary32 ? torch::kInt32 : torch::kInt64);
    const auto mask = binary32 ? std::numeric_limits<std::int32_t>::max()
                               : std::numeric_limits<std::int64_t>::max();
    const auto magnitude = bits.bitwise_and(mask);

    return magnitude.eq(0)
        .logical_or(magnitude.eq(OneBits(binary32)))
        .all()
        .item<bool>();
}
}  // namespace

NativeTrainer::NativeTrainer(PolicyValueNetwork model)
    : m_model(std::move(model)), m_optimizer(m_model->parameters(), 0.01)
{
    // Do nothing
}

std::array<torch::Tensor, 3> ComputeTrainingLosses(
    const PolicyValueNetworkImpl& model,
    const std::pair<torch::Tensor, torch::Tensor>& predictions,
    const torch::Tensor& policyTargets, const torch::Tensor& outcomes)
{
    const auto& [logits, values] = predictions;

    TORCH_CHECK(values.numel() > 0, "Training requires a nonempty batch");
    CheckTarget(policyTargets, logits, "Policy targets");
    CheckTarget(outcomes, values, "Outcomes");
    TORCH_CHECK(
        HasNormalizedPolicyRows(policyTargets),
        "Policy targets must be finite, nonnegative and sum to one per row");
    TORCH_CHECK(HasValidOutcomes(outcomes),
                "Outcomes must be -1 (loss), 0 (draw) or +1 (win)");

    auto policy = policyTargets.detach();

    if (policy.is_inference() && logits.requires_grad())
    {
        // Backward needs a version counter on the saved policy target.
        policy = policy.clone();
    }

    const auto policyLoss = -(policy * logits.log_softmax(1)).sum(1).mean();
    const auto valueLoss = (values - outcomes.detach()).square().mean();
    auto totalLoss = policyLoss + valueLoss;

    for (const auto& parameter : model.parameters())
    {
        totalLoss = totalLoss + 1e-4 * parameter.square().sum();
    }

    TORCH_CHECK(std::isfinite(totalLoss.item<double>()),
                "Non-finite training loss");

    return { policyLoss, valueLoss, totalLoss };
}

TrainingStep NativeTrainer::TrainBatch(const torch::Tensor& observations,
                                       const torch::Tensor& policyTargets,
                                       const torch::Tensor& outcomes)
{
    m_model->train();

    const auto [policyLoss, valueLoss, totalLoss] = ComputeTrainingLosses(
        *m_model, m_model->forward(observations), policyTargets, outcomes);
    const TrainingStep result{ m_steps + 1, policyLoss.item<double>(),
                               valueLoss.item<double>(),
                               totalLoss.item<double>() };

    m_optimizer.zero_grad();
    totalLoss.backward();
    m_optimizer.step();

    m_steps = result.step;
    return result;
}

std::vector<torch::Tensor> ReadTrainingBatch(std::istream& input)
{
    using PlayMode::SelfPlaySample;

    if (input.peek() == SelfPlaySample::MAGIC.front())
    {
        std::string bytes(SelfPlaySample::BYTE_SIZE, '\0');
        input.read(bytes.data(), static_cast<std::streamsize>(bytes.size()));

        TORCH_CHECK(
            input && input.rdbuf()->sgetc() == std::char_traits<char>::eof(),
            "Expected one complete self-play sample");

        const auto sample = SelfPlaySample::Deserialize(bytes);

        return { torch::tensor(at::ArrayRef(sample.observation), torch::kInt32)
                     .unsqueeze(0),
                 torch::tensor(at::ArrayRef(sample.policyTarget),
                               torch::kFloat32)
                     .unsqueeze(0),
                 torch::tensor({ sample.outcome }, torch::kFloat32) };
    }

    std::vector<torch::Tensor> batch;

    torch::load(batch, input, torch::kCPU);

    TORCH_CHECK(
        batch.size() == 3,
        "Expected observations, policy targets and outcomes in training batch");

    return batch;
}

TrainingStep NativeTrainer::TrainBatch(std::istream& input)
{
    const auto batch = ReadTrainingBatch(input);
    return TrainBatch(batch[0], batch[1], batch[2]);
}

void SaveTrainingCheckpoint(const PolicyValueNetworkImpl& model,
                            const std::filesystem::path& weights)
{
    auto target = weights;

    while (std::filesystem::is_symlink(target))
    {
        if (std::filesystem::exists(target))
        {
            target = std::filesystem::canonical(target);
            break;
        }

        // A link may name the file that the first checkpoint will create.
        target = target.parent_path() / std::filesystem::read_symlink(target);
    }

    const auto temporary =
        target.parent_path() /
        (".rosetta-weights-" +
         std::to_string(
             std::chrono::steady_clock::now().time_since_epoch().count()) +
         ".tmp");

    TORCH_CHECK(std::ofstream(temporary, std::ios::noreplace).is_open(),
                "Cannot create temporary checkpoint");

    try
    {
        const auto destination = std::filesystem::status(target);

        if (std::filesystem::exists(destination))
        {
            std::filesystem::permissions(temporary, destination.permissions());
        }

        model.SaveWeights(temporary);
        std::filesystem::rename(temporary, target);
    }
    catch (...)
    {
        std::error_code error;
        std::filesystem::remove(temporary, error);
        throw;
    }
}

void NativeTrainer::SaveCheckpoint(const std::filesystem::path& weights) const
{
    SaveTrainingCheckpoint(*m_model, weights);
}
}  // namespace RosettaStone::RL
