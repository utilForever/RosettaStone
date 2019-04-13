// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <RosettaTorch/GameToVec.hpp>

namespace RosettaTorch
{
torch::Tensor GameToVec::GenerateTensor(const Game& game)
{
    // vector shape : [1 + 1 + n * 7 + 1 + n * 7 + n * 10 = 3 + n * 24]
    // # 1      : number of opponent player's cards on hand (sparse)
	// # 1      : number of opponent player's left cards at deck (sparse)
	// # n * 7  : opponent player's representation vectors of card at the deck. 
	//            each card has a dimensionality of n.
    // # 1      : number of current player's left cards at deck (sparse)
	// # n * 7  : current player's representation vectors of card at the deck. 
	//            each card has a dimensionality of n.
	// # n * 10 : current player's representation vectors of card in the hand.
	//            each card has a dimensionality of n.

	// each card is represented as a vector which has n dimensionality.
	// it includes, cost, attack, health, ability.
	// vector shape : [1 + 1 + 1 + m = n]
	// # 1 : cost (sparse)
	// # 1 : attack (sparse)
	// # 1 : health (sparse)
	// # m : ability

	// each card's abilities are represented as a vector which has m dimensionality.
    // it includes, ...
    // vector shape : [m]
    torch::Tensor tensor = torch::empty(GameVectorSize, torch::kInt8);

    return tensor;
}
}  // namespace RosettaTorch