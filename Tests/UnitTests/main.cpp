// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#define DOCTEST_CONFIG_IMPLEMENT
#include <doctest.h>

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>

using namespace RosettaStone;

int main()
{
    doctest::Context context;

    PlayMode::Cards::GetInstance();
    Battlegrounds::Cards::GetInstance();

    // Run queries, or run tests unless --no-run is specified
    const int res = context.run();

    return res;
}
