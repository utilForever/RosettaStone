// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_AVAILABLE_ACTIONS_HPP
#define ROSETTASTONE_AVAILABLE_ACTIONS_HPP

#include <Rosetta/Enums/TaskEnums.hpp>
#include <Rosetta/Games/Game.hpp>

namespace RosettaStone::Generic
{
struct ActionEncode
{
    static constexpr size_t NumTarget = 4;

    TaskID taskID;
    Entity* source;

    size_t numTarget;
    Entity* target[NumTarget];

    ActionEncode(TaskID taskID = TaskID::INVALID, Entity* source = nullptr,
                 size_t numTarget = 0)
        : taskID(taskID),
          source(source),
          numTarget(numTarget),
          target{
              nullptr,
          }
    {
        // Do nothing.
    }
};

inline std::vector<ActionEncode> AvailableActions(const Game& game)
{
    (void)game;
    return std::vector<ActionEncode>();
}
}  // namespace RosettaStone::Generic

#endif