// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <RosettaTorch/GameToVec.hpp>

namespace RosettaTorch
{
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

    // each card's abilities are represented as a vector which has m dimensionality.
    // it includes, ...
    // vector shape : [m]
    torch::Tensor tensor = torch::empty(GameVectorSize, torch::kFloat32);

	Player& curPlayer = game.GetCurrentPlayer();
    Player& oppPlayer = game.GetOpponentPlayer();

	// Write number of opponent player's cards, normalized, on hand.
	tensor[0] = static_cast<float>(oppPlayer.GetHand().GetNumOfCards()) / HAND_SIZE;

	// Write number of opp player's cards normalized.
    tensor[1] = static_cast<float>(oppPlayer.GetDeck().GetNumOfCards()) / MAX_DECK_SIZE;

	// Write number of current player's cards normalized.
    tensor[2] = static_cast<float>(curPlayer.GetDeck().GetNumOfCards()) / MAX_DECK_SIZE;

    return tensor;
}
}  // namespace RosettaTorch