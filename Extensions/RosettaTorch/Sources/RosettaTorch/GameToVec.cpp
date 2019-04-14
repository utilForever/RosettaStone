// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Cards.hpp>
#include <RosettaTorch/GameToVec.hpp>

namespace RosettaTorch
{
GameToVec::GameToVec(size_t seed) : m_seed(seed)
{
    // reproducibility
    torch::manual_seed(static_cast<uint64_t>(m_seed));

    // Generates the embedding lookup table for the card
    size_t NumOfCards = Cards::GetInstance().GetAllCards().size();

    CardVectorTable = torch::nn::Embedding(NumOfCards, CardVectorSize);
    CardVectorTable->weight = torch::randn(
        {static_cast<int>(NumOfCards), static_cast<int>(CardVectorSize)}, 
        torch::kFloat32
    );
    CardVectorTable->weight.set_requires_grad(false);
}

GameToVec::GameToVec(size_t seed, torch::Tensor weight) : m_seed(seed)
{
    // reproducibility
    torch::manual_seed(static_cast<uint64_t>(m_seed));

    // Generates the embedding lookup table for the card
    size_t NumOfCards = Cards::GetInstance().GetAllCards().size();

    CardVectorTable = torch::nn::Embedding(NumOfCards, CardVectorSize);
    CardVectorTable->weight = weight;
    CardVectorTable->weight.set_requires_grad(false);
}

torch::Tensor GameToVec::AbilityToTensor(const Card& card)
{
    (void)card;
    return torch::Tensor();
}

torch::Tensor GameToVec::GenerateTensor(const Game& game)
{
    // vector shape : [1 + 1 + 1 + n * 7 + n * 7 + n * 10 = 3 + n * 24]
    // # 1      : number of opponent player's cards on hand.
    // # 1      : number of opponent player's left cards at deck.
    // # 1      : number of current player's left cards at deck.
    // # n * 7  : opponent player's representation vectors of card at the deck.
    //            each card has a dimensionality of n.
    // # n * 7  : current player's representation vectors of card at the deck.
    //            each card has a dimensionality of n.
    // # n * 10 : current player's representation vectors of card in the hand.
    //            each card has a dimensionality of n.

    // each card is represented as a vector which has n dimensionality.
    // it includes, cost, attack, health, ability.
    // vector shape : [1 + 1 + 1 + m = n]
    // # 1 : cost
    // # 1 : attack
    // # 1 : health
    // # m : ability

    // each card's abilities are represented as a vector which has m
    // dimensionality. it includes, ... vector shape : [m]
    torch::Tensor tensor = torch::empty(GameVectorSize, torch::kFloat32);

    Player& curPlayer = game.GetCurrentPlayer();
    Player& oppPlayer = game.GetOpponentPlayer();

    // Write number of opponent player's cards, normalized, on the hand.
    tensor[0] =
        static_cast<float>(oppPlayer.GetHand().GetNumOfCards()) / HAND_SIZE;

    // Write number of opponent player's cards, normalized, on the deck.
    tensor[1] =
        static_cast<float>(oppPlayer.GetDeck().GetNumOfCards()) / MAX_DECK_SIZE;

    // Write number of current player's cards, normalized, on the deck.
    tensor[2] =
        static_cast<float>(curPlayer.GetDeck().GetNumOfCards()) / MAX_DECK_SIZE;

    return tensor;
}
}  // namespace RosettaTorch