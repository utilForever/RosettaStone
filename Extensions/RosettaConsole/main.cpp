// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>

#include "Console.hpp"

using namespace RosettaStone::PlayMode;

int main()
{
    Cards::GetInstance();
    Console c;
    return c.Login();
}