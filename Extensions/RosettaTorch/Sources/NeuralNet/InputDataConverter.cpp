// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/InputDataConverter.hpp>

namespace RosettaTorch::NeuralNet
{
void InputDataConverter::Convert(const IInputGetter* getter,
                                 torch::Tensor& hero, torch::Tensor& minion,
                                 torch::Tensor& standalone)
{
    GetInputData(getter, hero, minion, standalone);
}

void InputDataConverter::GetInputData(const IInputGetter* getter,
                                      torch::Tensor& hero,
                                      torch::Tensor& minion,
                                      torch::Tensor& standalone) const
{
    std::vector<float> input1;
    AddHeroData(FieldSide::CURRENT, getter, input1);
    AddHeroData(FieldSide::OPPONENT, getter, input1);

    const torch::Tensor tensor1 = torch::empty(input1.size(), torch::kFloat32);
    for (std::size_t i = 0; i < input1.size(); ++i)
    {
        tensor1[i] = input1[i];
    }

    std::vector<float> input2;
    AddMinionsData(FieldSide::CURRENT, getter, input2);
    AddMinionsData(FieldSide::OPPONENT, getter, input2);

    const torch::Tensor tensor2 = torch::empty(input2.size(), torch::kFloat32);
    for (std::size_t i = 0; i < input2.size(); ++i)
    {
        tensor2[i] = input2[i];
    }

    std::vector<float> input3;
    AddStandaloneData(getter, input3);

    const torch::Tensor tensor3 = torch::empty(input3.size(), torch::kFloat32);
    for (std::size_t i = 0; i < input3.size(); ++i)
    {
        tensor3[i] = input3[i];
    }

    hero = tensor1;
    minion = tensor2;
    standalone = tensor3;
}

void InputDataConverter::AddHeroData(FieldSide side, const IInputGetter* getter,
                                     std::vector<float>& data) const
{
    const double hp = getter->GetField(side, FieldType::HERO_HEALTH) +
                      getter->GetField(side, FieldType::HERO_ARMOR);
    data.push_back(NormalizeFromUniformDist(hp, 0.0, 30.0));
}

void InputDataConverter::AddMinionsData(FieldSide side,
                                        const IInputGetter* getter,
                                        std::vector<float>& data) const
{
    int rest = 7;
    const auto minionCount = static_cast<std::size_t>(
        getter->GetField(side, FieldType::MINION_COUNT));

    for (std::size_t i = 0; i < minionCount; ++i)
    {
        if (rest <= 0)
        {
            throw std::runtime_error("Too many minions");
        }

        AddMinionData(side, getter, i, data);
        --rest;
    }

    while (rest > 0)
    {
        AddMinionPlaceholderData(data);
        --rest;
    }
}

void InputDataConverter::AddMinionData(FieldSide side,
                                       const IInputGetter* getter,
                                       int minionIdx,
                                       std::vector<float>& data) const
{
    data.push_back(NormalizeFromUniformDist(
        getter->GetField(side, FieldType::MINION_HEALTH, minionIdx), 1.0, 7.0));
    data.push_back(NormalizeFromUniformDist(
        getter->GetField(side, FieldType::MINION_MAX_HEALTH, minionIdx), 1.0,
        7.0));
    data.push_back(NormalizeFromUniformDist(
        getter->GetField(side, FieldType::MINION_ATTACK, minionIdx), 0.0, 7.0));
    data.push_back(NormalizeBool(static_cast<bool>(
        getter->GetField(side, FieldType::MINION_ATTACKABLE, minionIdx))));
    data.push_back(NormalizeBool(static_cast<bool>(
        getter->GetField(side, FieldType::MINION_TAUNT, minionIdx))));
    data.push_back(NormalizeBool(static_cast<bool>(
        getter->GetField(side, FieldType::MINION_DIVINE_SHIELD, minionIdx))));
    data.push_back(NormalizeBool(static_cast<bool>(
        getter->GetField(side, FieldType::MINION_STEALTH, minionIdx))));
}

void InputDataConverter::AddMinionPlaceholderData(
    std::vector<float>& data) const
{
    data.push_back(0.0);
    data.push_back(0.0);
    data.push_back(0.0);
    data.push_back(NormalizeBool(false));
    data.push_back(NormalizeBool(false));
    data.push_back(NormalizeBool(false));
    data.push_back(NormalizeBool(false));
}

void InputDataConverter::AddStandaloneData(const IInputGetter* getter,
                                           std::vector<float>& data) const
{
    data.push_back(NormalizeFromUniformDist(
        getter->GetField(FieldSide::CURRENT, FieldType::MANA_CRYSTAL_CURRENT),
        0, 10));
    data.push_back(NormalizeFromUniformDist(
        getter->GetField(FieldSide::CURRENT, FieldType::MANA_CRYSTAL_TOTAL), 0,
        10));
    data.push_back(NormalizeFromUniformDist(
        getter->GetField(FieldSide::CURRENT,
                         FieldType::MANA_CRYSTAL_OVERLOAD_LOCKED),
        0, 10));

    const auto curHandCount = static_cast<int>(
        getter->GetField(FieldSide::CURRENT, FieldType::HAND_COUNT));
    data.push_back(NormalizeFromUniformDist(curHandCount, 0, 10));

    int curHandPlayable = 0;
    for (int i = 0; i < curHandCount; ++i)
    {
        const auto playable = static_cast<bool>(
            getter->GetField(FieldSide::CURRENT, FieldType::HAND_PLAYABLE, i));
        if (playable)
        {
            ++curHandPlayable;
        }
    }
    data.push_back(NormalizeFromUniformDist(curHandPlayable, 0, 10));

    int handCards = 0;
    for (int i = 0; i < curHandCount; ++i)
    {
        data.push_back(NormalizeFromUniformDist(
            getter->GetField(FieldSide::CURRENT, FieldType::HAND_COST, i), 0,
            10));
        ++handCards;
    }

    while (handCards < 10)
    {
        data.push_back(NormalizeFromUniformDist(-1, 0, 10));
        ++handCards;
    }

    const auto opHandCount = static_cast<int>(
        getter->GetField(FieldSide::OPPONENT, FieldType::HAND_COUNT));
    data.push_back(NormalizeFromUniformDist(opHandCount, 0, 10));

    data.push_back(NormalizeBool(static_cast<bool>(
        getter->GetField(FieldSide::CURRENT, FieldType::HERO_POWER_PLAYABLE))));
}

float InputDataConverter::NormalizeFromUniformDist(double v, double min,
                                                   double max) const
{
    // Normalize to mean = 0, var = 1.0
    // Uniform dist is with variance = (max-min)^2 / 12
    // -> So we should have (max-min)^2 / 12 = 1.0
    // -> (max-min)^2 = 12.0
    // -> (max-min) = sqrt(12.0)
    static double sqrt_12 = std::sqrt(12.0);

    const double mean = (min + max) / 2;
    const double range = (max - min);
    const double scale = sqrt_12 / range;

    const double ret = (v - mean) * scale;
    return static_cast<float>(ret);
}

float InputDataConverter::NormalizeBool(bool v) const
{
    double vv;

    if (v)
    {
        vv = 1.0;
    }
    else
    {
        vv = -1.0;
    }

    const double ret = NormalizeFromUniformDist(vv, -1.0, 1.0);
    return static_cast<float>(ret);
}
}  // namespace RosettaTorch::NeuralNet