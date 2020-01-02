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

torch::Tensor CNNModel::EncodeHero(torch::Tensor x)
{
    x = x.view({ x.size(0), HERO_IN_DIM, 2 });  // output shape : bs, 1, 2
    x = m_heroConv->forward(x);                 // output shape : bs, 1, 2
    x = torch::leaky_relu(x, .2);               // output shape : bs, 1, 2
    x = x.view({ x.size(0), -1 });              // output shape : bs, 1 * 2
    return x;
}

torch::Tensor CNNModel::EncodeMinion(torch::Tensor x)
{
    x = x.view(
        { x.size(0), MINION_IN_DIM, MINION_COUNT * 2 });  // output shape : bs, 7, 14
    x = m_minionConv->forward(x);                         // output shape : bs, 3, 14
    x = torch::leaky_relu(x, .2);                         // output shape : bs, 3, 14
    x = x.view({ x.size(0), -1 });                        // output shape : bs, 3 * 14
    return x;
}

torch::Tensor CNNModel::EncodeStandalone(torch::Tensor x)
{
    x = x.view({ x.size(0), -1 });  // output shape : bs, 17
    return x;
}

torch::Tensor CNNModel::forward(torch::Tensor hero, torch::Tensor minion,
                                torch::Tensor standalone)
{
    // input shape  : (bs, 2), (bs, 7 * 14), (bs, 17)
    // output shape : (bs, 1)

    // Encodes the information of heroes
    const auto outHero = EncodeHero(hero);

    // Encodes the information of minions
    const auto outMinion = EncodeMinion(minion);

    // Encodes the information of 'standalone'
    const auto outStandalone = EncodeStandalone(standalone);

    auto concatFeatures = torch::cat({ outHero, outMinion, outStandalone }, 1);

    concatFeatures = m_fc1->forward(concatFeatures);
    concatFeatures = torch::leaky_relu(concatFeatures, .2);

    concatFeatures = m_fc2->forward(concatFeatures);
    concatFeatures = torch::tanh(concatFeatures);

    return concatFeatures;
}
}  // namespace RosettaTorch::NeuralNet