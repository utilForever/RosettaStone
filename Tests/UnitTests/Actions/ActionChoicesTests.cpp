// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Actions/ActionChoices.hpp>

#include <stdexcept>

using namespace RosettaStone;

TEST_CASE("[ActionChoices] - InvalidChoice")
{
    ActionChoices choices;

    // Get
    CHECK_THROWS_AS(choices.Get(0), std::runtime_error);
    CHECK_THROWS_AS(choices.Get(1), std::runtime_error);
    CHECK_THROWS_AS(choices.Get(2), std::runtime_error);
    CHECK_THROWS_AS(choices.Get(), std::runtime_error);

    // IsEmpty
    CHECK_THROWS_AS(choices.IsEmpty(), std::runtime_error);

    // Size
    CHECK_THROWS_AS(choices.Size(), std::runtime_error);

    //! Begin, IsEnd, StepNext
    CHECK_THROWS_AS(choices.Begin(), std::runtime_error);
    CHECK_THROWS_AS(choices.IsEnd(), std::runtime_error);
    CHECK_THROWS_AS(choices.StepNext(), std::runtime_error);
}

TEST_CASE("[ActionChoices] - ChooseFromCardIDs")
{
    const std::vector<std::size_t> cardIDs = { 1, 4, 6 };
    ActionChoices choices(cardIDs);

    // Get
    CHECK_EQ(choices.Get(0), 1);
    CHECK_EQ(choices.Get(1), 4);
    CHECK_EQ(choices.Get(2), 6);

    // IsEmpty
    CHECK_EQ(choices.IsEmpty(), false);

    // Size
    CHECK_EQ(choices.Size(), 3);

    //! Begin, IsEnd, StepNext
    int sum = 0;
    for (choices.Begin(); !choices.IsEnd(); choices.StepNext())
    {
        sum += choices.Get();
    }
    CHECK_EQ(sum, 11);
}

TEST_CASE("[ActionChoices] - ChooseFromNumbers")
{
    ActionChoices choices(3);

    // Get
    CHECK_EQ(choices.Get(0), 0);
    CHECK_EQ(choices.Get(1), 1);
    CHECK_EQ(choices.Get(2), 2);

    // IsEmpty
    CHECK_EQ(choices.IsEmpty(), false);

    // Size
    CHECK_EQ(choices.Size(), 3);

    //! Begin, IsEnd, StepNext
    int sum = 0;
    for (choices.Begin(); !choices.IsEnd(); choices.StepNext())
    {
        sum += choices.Get();
    }
    CHECK_EQ(sum, 3);
}