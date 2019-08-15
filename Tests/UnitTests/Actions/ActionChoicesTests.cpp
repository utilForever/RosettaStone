// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Actions/ActionChoices.hpp>

using namespace RosettaStone;

TEST(ActionChoices, InvalidChoice)
{
    ActionChoices choices;

    // Get
    EXPECT_THROW(choices.Get(0), std::runtime_error);
    EXPECT_THROW(choices.Get(1), std::runtime_error);
    EXPECT_THROW(choices.Get(2), std::runtime_error);
    EXPECT_THROW(choices.Get(), std::runtime_error);

    // IsEmpty
    EXPECT_THROW(choices.IsEmpty(), std::runtime_error);

    // Size
    EXPECT_THROW(choices.Size(), std::runtime_error);

    //! Begin, IsEnd, StepNext
    EXPECT_THROW(choices.Begin(), std::runtime_error);
    EXPECT_THROW(choices.IsEnd(), std::runtime_error);
    EXPECT_THROW(choices.StepNext(), std::runtime_error);
}

TEST(ActionChoices, ChooseFromCardIDs)
{
    const std::vector<std::size_t> cardIDs = { 1, 4, 6 };
    ActionChoices choices(cardIDs);

    // Get
    EXPECT_EQ(choices.Get(0), 1);
    EXPECT_EQ(choices.Get(1), 4);
    EXPECT_EQ(choices.Get(2), 6);

    // IsEmpty
    EXPECT_EQ(choices.IsEmpty(), false);

    // Size
    EXPECT_EQ(choices.Size(), 3);

    //! Begin, IsEnd, StepNext
    int sum = 0;
    for (choices.Begin(); !choices.IsEnd(); choices.StepNext())
    {
        sum += choices.Get();
    }
    EXPECT_EQ(sum, 11);
}

TEST(ActionChoices, ChooseFromNumbers)
{
    ActionChoices choices(3);

    // Get
    EXPECT_EQ(choices.Get(0), 0);
    EXPECT_EQ(choices.Get(1), 1);
    EXPECT_EQ(choices.Get(2), 2);

    // IsEmpty
    EXPECT_EQ(choices.IsEmpty(), false);

    // Size
    EXPECT_EQ(choices.Size(), 3);

    //! Begin, IsEnd, StepNext
    int sum = 0;
    for (choices.Begin(); !choices.IsEnd(); choices.StepNext())
    {
        sum += choices.Get();
    }
    EXPECT_EQ(sum, 3);
}