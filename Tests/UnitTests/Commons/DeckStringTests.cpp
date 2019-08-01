// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Commons/DeckString.hpp>

using namespace RosettaStone;

TEST(DeckString, ParseFromString)
{
    DeckInfo info = DeckString::ParseFromString("AAECAR8IxwOHBMkErgaggAOnggObhQPWmQMLngGoArUDxQj+DJjwAu/xAvWJA+aWA/mWA76YAwA=");

    EXPECT_EQ(info.GetClass(), CardClass::HUNTER);
    EXPECT_EQ(info.GetNumOfCards(), 30u);
    EXPECT_EQ(info.GetNumCardInDeck("EX1_080"), 2);  // Secretkeeper
    EXPECT_EQ(info.GetNumCardInDeck("EX1_610"), 1);  // Explosive Trap
    EXPECT_EQ(info.GetNumCardInDeck("EX1_611"), 1);  // Freezing Trap
    EXPECT_EQ(info.GetNumCardInDeck("GIL_577"), 2);  // Rat Trap
    EXPECT_EQ(info.GetNumCardInDeck("EX1_554"), 1);  // Snake Trap
    EXPECT_EQ(info.GetNumCardInDeck("EX1_609"), 1);  // Snipe
    EXPECT_EQ(info.GetNumCardInDeck("DAL_086"), 2);  // Sunreaver Spy
    EXPECT_EQ(info.GetNumCardInDeck("NEW1_031"), 2); // Animal Companion
    EXPECT_EQ(info.GetNumCardInDeck("EX1_617"), 2);  // Deadly Shot
    EXPECT_EQ(info.GetNumCardInDeck("EX1_536"), 2);  // Eaglehorn Bow
    EXPECT_EQ(info.GetNumCardInDeck("EX1_539"), 2);  // Kill Command
    EXPECT_EQ(info.GetNumCardInDeck("TRL_530"), 2);  // Masked Contender
    EXPECT_EQ(info.GetNumCardInDeck("DAL_558"), 1);  // Archmage Vargoth
    EXPECT_EQ(info.GetNumCardInDeck("GIL_622"), 2);  // Lifedrinker
    EXPECT_EQ(info.GetNumCardInDeck("DAL_371"), 2);  // Marked Shot
    EXPECT_EQ(info.GetNumCardInDeck("BOT_573"), 1);  // Subject 9
    EXPECT_EQ(info.GetNumCardInDeck("BOT_548"), 1);  // Zilliax
    EXPECT_EQ(info.GetNumCardInDeck("DAL_378"), 2);  // Unleash the Beast
    EXPECT_EQ(info.GetNumCardInDeck("TRL_065"), 1);  // Zul'jin
}
