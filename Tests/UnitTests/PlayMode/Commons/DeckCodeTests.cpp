// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Utils/DeckCode.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[DeckString] - Decode")
{
    CHECK_THROWS(DeckCode::Decode("AAECAR8I"));
    CHECK_THROWS(
        DeckCode::Decode("AQECAR8IxwOHBMkErgaggAOnggObhQPWmQMLngGoArU"
                         "DxQj+DJjwAu/xAvWJA+aWA/mWA76YAwA="));
    CHECK_THROWS(
        DeckCode::Decode("AAICAR8IxwOHBMkErgaggAOnggObhQPWmQMLngGoArU"
                         "DxQj+DJjwAu/xAvWJA+aWA/mWA76YAwA="));
    CHECK_THROWS(
        DeckCode::Decode("AAESAR8IxwOHBMkErgaggAOnggObhQPWmQMLngGoArU"
                         "DxQj+DJjwAu/xAvWJA+aWA/mWA76YAwA="));
    CHECK_THROWS(
        DeckCode::Decode("AAECAh8FCMcDhwTJBK4GoIADp4IDm4UD1pkDC54BqAK"
                         "1A8UI/gyY8ALv8QL1iQPmlgP5lgO+mAMA"));
    CHECK_THROWS(
        DeckCode::Decode("AAECAQAIxwOHBMkErgaggAOnggObhQPWmQMLngGoArU"
                         "DxQj+DJjwAu/xAvWJA+aWA/mWA76YAwA="));

    Deck info = DeckCode::Decode(
        "AAECAR8IxwOHBMkErgaggAOnggObhQPWmQMLngGoArUDxQj+DJjwAu/xAvWJA+aWA/"
        "mWA76YAwA=");

    CHECK_EQ(info.GetClass(), CardClass::HUNTER);
    CHECK_EQ(info.GetNumOfCards(), 30u);
    CHECK_EQ(info.GetNumCardInDeck("EX1_080"), 2);   // Secretkeeper
    CHECK_EQ(info.GetNumCardInDeck("EX1_610"), 1);   // Explosive Trap
    CHECK_EQ(info.GetNumCardInDeck("EX1_611"), 1);   // Freezing Trap
    CHECK_EQ(info.GetNumCardInDeck("GIL_577"), 2);   // Rat Trap
    CHECK_EQ(info.GetNumCardInDeck("EX1_554"), 1);   // Snake Trap
    CHECK_EQ(info.GetNumCardInDeck("EX1_609"), 1);   // Snipe
    CHECK_EQ(info.GetNumCardInDeck("DAL_086"), 2);   // Sunreaver Spy
    CHECK_EQ(info.GetNumCardInDeck("NEW1_031"), 2);  // Animal Companion
    CHECK_EQ(info.GetNumCardInDeck("EX1_617"), 2);   // Deadly Shot
    CHECK_EQ(info.GetNumCardInDeck("EX1_536"), 2);   // Eaglehorn Bow
    CHECK_EQ(info.GetNumCardInDeck("EX1_539"), 2);   // Kill Command
    CHECK_EQ(info.GetNumCardInDeck("TRL_530"), 2);   // Masked Contender
    CHECK_EQ(info.GetNumCardInDeck("DAL_558"), 1);   // Archmage Vargoth
    CHECK_EQ(info.GetNumCardInDeck("GIL_622"), 2);   // Lifedrinker
    CHECK_EQ(info.GetNumCardInDeck("DAL_371"), 2);   // Marked Shot
    CHECK_EQ(info.GetNumCardInDeck("BOT_573"), 1);   // Subject 9
    CHECK_EQ(info.GetNumCardInDeck("BOT_548"), 1);   // Zilliax
    CHECK_EQ(info.GetNumCardInDeck("DAL_378"), 2);   // Unleash the Beast
    CHECK_EQ(info.GetNumCardInDeck("TRL_065"), 1);   // Zul'jin

    Deck info2 = DeckCode::Decode(
        "AAECAR8IxwOHBMkErgaggAOnggObhQPWmQMAC54BAqgCArUDAsUIAv4MApjwAgLv8QIC9Y"
        "kDAuaWAwL5lgMCvpgDAg==");

    CHECK_EQ(info.GetClass(), CardClass::HUNTER);
    CHECK_EQ(info.GetNumOfCards(), 30u);
    CHECK_EQ(info.GetNumCardInDeck("EX1_080"), 2);   // Secretkeeper
    CHECK_EQ(info.GetNumCardInDeck("EX1_610"), 1);   // Explosive Trap
    CHECK_EQ(info.GetNumCardInDeck("EX1_611"), 1);   // Freezing Trap
    CHECK_EQ(info.GetNumCardInDeck("GIL_577"), 2);   // Rat Trap
    CHECK_EQ(info.GetNumCardInDeck("EX1_554"), 1);   // Snake Trap
    CHECK_EQ(info.GetNumCardInDeck("EX1_609"), 1);   // Snipe
    CHECK_EQ(info.GetNumCardInDeck("DAL_086"), 2);   // Sunreaver Spy
    CHECK_EQ(info.GetNumCardInDeck("NEW1_031"), 2);  // Animal Companion
    CHECK_EQ(info.GetNumCardInDeck("EX1_617"), 2);   // Deadly Shot
    CHECK_EQ(info.GetNumCardInDeck("EX1_536"), 2);   // Eaglehorn Bow
    CHECK_EQ(info.GetNumCardInDeck("EX1_539"), 2);   // Kill Command
    CHECK_EQ(info.GetNumCardInDeck("TRL_530"), 2);   // Masked Contender
    CHECK_EQ(info.GetNumCardInDeck("DAL_558"), 1);   // Archmage Vargoth
    CHECK_EQ(info.GetNumCardInDeck("GIL_622"), 2);   // Lifedrinker
    CHECK_EQ(info.GetNumCardInDeck("DAL_371"), 2);   // Marked Shot
    CHECK_EQ(info.GetNumCardInDeck("BOT_573"), 1);   // Subject 9
    CHECK_EQ(info.GetNumCardInDeck("BOT_548"), 1);   // Zilliax
    CHECK_EQ(info.GetNumCardInDeck("DAL_378"), 2);   // Unleash the Beast
    CHECK_EQ(info.GetNumCardInDeck("TRL_065"), 1);   // Zul'jin
}
