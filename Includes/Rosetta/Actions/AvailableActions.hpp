// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_AVAILABLE_ACTIONS_HPP
#define ROSETTASTONE_AVAILABLE_ACTIONS_HPP

#include <Rosetta/Games/Game.hpp>

namespace RosettaStone::Generic
{
struct ActionEncode
{
    TaskID taskID;
    Entity* source;

    size_t numTarget;
    Entity* target[4];
};

std::vector<ActionEncode> AvailableActions(const Game& game)
{
    return std::vector<ActionEncode>();
}
}

#endif