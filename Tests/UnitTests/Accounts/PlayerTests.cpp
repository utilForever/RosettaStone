// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Accounts/Account.hpp>
#include <hspp/Cards/Deck.hpp>
#include <hspp/Enums/CardEnums.hpp>

using namespace Hearthstonepp;

TEST(TestPlayer, Constructors)
{
    Account player1;
    EXPECT_EQ("anonymous@gmail.com", player1.GetEmail());
    EXPECT_EQ("Anonymous", player1.GetNickname());

    Account player2("1", "name1");
    EXPECT_EQ("1", player2.GetEmail());
    EXPECT_EQ("name1", player2.GetNickname());

    const std::vector<Deck*> decks;
    Account player3("2", "name2", decks);
    EXPECT_EQ("2", player3.GetEmail());
    EXPECT_EQ("name2", player3.GetNickname());
    EXPECT_EQ(0, static_cast<int>(player3.GetNumOfDeck()));
}

TEST(Account, DeckControl)
{
    Account player;

    EXPECT_NO_THROW(player.ShowDeckList());
    EXPECT_EQ(false, player.CreateDeck("deck1", CardClass::INVALID));

    player.CreateDeck("deck2", CardClass::DREAM);
    player.CreateDeck("deck3", CardClass::DRUID);

    EXPECT_EQ(2, static_cast<int>(player.GetNumOfDeck()));
    EXPECT_NO_THROW(player.ShowDeckList());

    EXPECT_NO_THROW(player.DeleteDeck(0));
    EXPECT_EQ(1, static_cast<int>(player.GetNumOfDeck()));
    EXPECT_EQ("deck3", player.GetDeck(0)->GetName());

    EXPECT_EQ(1, static_cast<int>(player.GetNumOfDeck()));
}
