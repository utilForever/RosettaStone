#include "gtest/gtest.h"

#include <Agents/GameAgent.h>
#include <Interface/Interface.h>
#include <Tasks/BasicTask.h>

using namespace Hearthstonepp;

TEST(BasicCard, EX1_066)
{
    GameAgent agent(
        Player(new Account("Player 1", ""), new Deck("", CardClass::WARRIOR)),
        Player(new Account("Player 2", ""), new Deck("", CardClass::MAGE)));
    agent.GetPlayer1().totalMana = 10;
    agent.GetPlayer2().totalMana = 10;

    agent.Process(agent.GetPlayer1(),
                  BasicTask::DrawTask(
                      Cards::GetInstance()->FindCardByName("Fiery War Axe")));
    EXPECT_EQ(agent.GetPlayer1().hand.size(), 1);

    agent.Process(agent.GetPlayer2(),
                  BasicTask::DrawTask(Cards::GetInstance()->FindCardByName(
                      "Acidic Swamp Ooze")));
    EXPECT_EQ(agent.GetPlayer2().hand.size(), 1);

    //IPlayable weapon =
    //    Generic.DrawCard(game.CurrentPlayer, Cards.FromName("Fiery War Axe"));
    //game.Process(PlayCardTask.Any(game.CurrentPlayer, weapon));

    //Assert.True(game.CurrentPlayer.Hero.Weapon != null);

    //game.Process(EndTurnTask.Any(game.CurrentPlayer));

    //Assert.True(game.CurrentOpponent.Hero.Weapon != null);

    //IPlayable minion2 = Generic.DrawCard(game.CurrentPlayer,
    //                                     Cards.FromName("Acidic Swamp Ooze"));
    //game.Process(PlayCardTask.Minion(game.CurrentPlayer, minion2));

    //Assert.False(game.CurrentOpponent.Hero.Weapon != null);
}