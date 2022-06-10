// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_PLAY_HISTORY_HPP
#define ROSETTASTONE_PLAYMODE_PLAY_HISTORY_HPP

#include <Rosetta/PlayMode/Models/Playable.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief PlayHistory struct.
//!
//! This struct holds all values for played card.
//!
struct PlayHistory
{
    explicit PlayHistory(const Playable* source, const Playable* target,
                         int _turn, int _chooseOne)
    {
        sourcePlayer = source->player;
        sourceCard = source->card;
        sourceID = source->GetGameTag(GameTag::ENTITY_ID);

        if (target)
        {
            targetPlayer = target->player;
            targetCard = target->card;
        }

        turn = _turn;
        chooseOne = _chooseOne;
    }

    Player* sourcePlayer = nullptr;
    Player* targetPlayer = nullptr;
    Card* sourceCard = nullptr;
    Card* targetCard = nullptr;
    int sourceID = -1;
    int turn = -1;
    int chooseOne = -1;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_PLAY_HISTORY_HPP
