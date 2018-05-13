#include "gtest/gtest.h"

#include <Models/Player.h>
#include <Models/Deck.h>
#include <Enums/Enums.h>

using namespace Hearthstonepp;

 TEST(TestPlayer, Constructors)
 {
    Player player1;
    EXPECT_EQ("Anonymous", player1.GetID());
    EXPECT_EQ("Anonymous", player1.GetName());

    Player player2("1", "name1");
    EXPECT_EQ("1", player2.GetID());
    EXPECT_EQ("name1", player2.GetName());     

    std::vector<Deck*> decks;
    Player player3("2", "name2", decks);
    EXPECT_EQ("2", player3.GetID());
    EXPECT_EQ("name2", player3.GetName());     
    EXPECT_EQ(0, player3.GetNumOfDeck());
 }

TEST(TestPlayer, DeckControl)
{
    Player player;

    EXPECT_NO_THROW(player.ShowDeckList());
    EXPECT_THROW(player.CreateDeck("deck1", CardClass::INVALID), std::runtime_error);

    player.CreateDeck("deck2", CardClass::DREAM);
    player.CreateDeck("deck3", CardClass::DRUID);
    EXPECT_EQ(2, player.GetNumOfDeck());
    EXPECT_NO_THROW(player.ShowDeckList());

    player.DeleteDeck(0);
    EXPECT_EQ(1, player.GetNumOfDeck());
    EXPECT_EQ("deck3", player.GetDeck(0)->GetName());

    EXPECT_EQ(1, player.GetNumOfDeck());
}
