// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/CardDef.hpp>

#include <utility>

namespace RosettaStone
{
CardDef::CardDef(Power _power) : power(std::move(_power))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::map<PlayReq, int> _playReqs)
    : power(std::move(_power)), playReqs(std::move(_playReqs))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::vector<std::string> _chooseCardIDs)
    : power(std::move(_power)), chooseCardIDs(std::move(_chooseCardIDs))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::map<PlayReq, int> _playReqs,
                 std::vector<std::string> _chooseCardIDs)
    : power(std::move(_power)),
      playReqs(std::move(_playReqs)),
      chooseCardIDs(std::move(_chooseCardIDs))
{
    // Do nothing
}

CardDef::CardDef(Power _power, std::map<PlayReq, int> _playReqs,
                 std::vector<std::string> _chooseCardIDs,
                 std::vector<std::string> _entourages)
    : power(std::move(_power)),
      playReqs(std::move(_playReqs)),
      chooseCardIDs(std::move(_chooseCardIDs)),
      entourages(std::move(_entourages))
{
    // Do nothing
}
}  // namespace RosettaStone
