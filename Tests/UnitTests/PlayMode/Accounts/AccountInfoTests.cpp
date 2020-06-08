// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Accounts/AccountInfo.hpp>
#include <Rosetta/PlayMode/Accounts/DeckInfo.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[AccountInfo] - Constructors")
{
    AccountInfo player1;
    CHECK_EQ("anonymous@gmail.com", player1.GetEmail());
    CHECK_EQ("Anonymous", player1.GetNickname());

    AccountInfo player2("1", "name1");
    CHECK_EQ("1", player2.GetEmail());
    CHECK_EQ("name1", player2.GetNickname());

    const std::vector<DeckInfo*> decks;
    AccountInfo player3("2", "name2", decks);
    CHECK_EQ("2", player3.GetEmail());
    CHECK_EQ("name2", player3.GetNickname());
    CHECK_EQ(0, static_cast<int>(player3.GetNumOfDeck()));
}

TEST_CASE("[AccountInfo] - DeckControl")
{
    AccountInfo player;

    CHECK_NOTHROW(player.ShowDeckList());
    CHECK_EQ(false, player.CreateDeck("deck1", CardClass::INVALID));

    player.CreateDeck("deck2", CardClass::DREAM);
    player.CreateDeck("deck3", CardClass::DRUID);

    CHECK_EQ(2, static_cast<int>(player.GetNumOfDeck()));
    CHECK_NOTHROW(player.ShowDeckList());

    CHECK_NOTHROW(player.DeleteDeck(0));
    CHECK_EQ(1, static_cast<int>(player.GetNumOfDeck()));
    CHECK_EQ("deck3", player.GetDeck(0)->GetName());
}
