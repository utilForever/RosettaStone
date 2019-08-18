 // Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <NeuralNet/Models/CNNModel.hpp>

namespace RosettaTorch::NeuralNet
{
CNNModel::CNNModel()
{
}

torch::Tensor CNNModel::encodeHero(torch::Tensor x)
{
    x = x.view((hero_in_dim, 2, 1));
    x = heroConv1(x);
    x = torch::leaky_relu(x, .2);
    x = x.view((1, 1, -1));
    return x;
}

torch::Tensor CNNModel::encodeMinion(torch::Tensor x)
{
    x = x.view((minion_in_dim, minion_count * 2, 1));
    x = minionConv1(x);
    x = torch::leaky_relu(x, .2);
    x = x.view((1, 1, -1));
    return x;
}

torch::Tensor CNNModel::encodeStandalone(torch::Tensor x)
{
    x = x.view((1, 1, -1));
    return x;
}

torch::Tensor CNNModel::forward(const torch::Tensor hero,
                                const torch::Tensor minion, 
    const torch::Tensor standalone)
{
    // input shape  : (2,), (14,), (1,)
    // output shape : (1,) 

    // Encodes the information of heros
    const auto outHero = CNNModel::encodeHero(hero);

    // Encodes the information of minions
    const auto outMinion = CNNModel::encodeMinion(minion);

    // Encodes the information of 'standalone'
    const auto outStandalone = CNNModel::encodeStandalone(standalone);

    auto concatFeatures =
        torch::cat(( outHero, outMinion, outStandalone ), -1);

    concatFeatures = fc1(concatFeatures);
    concatFeatures = torch::leaky_relu(concatFeatures, .2);

    concatFeatures = fc2(concatFeatures);
    concatFeatures = torch::tanh(concatFeatures);

    return concatFeatures;
}
}  // namespace RosettaTorch::NeuralNet