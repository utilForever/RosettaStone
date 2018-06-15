#include "gtest/gtest.h"

#include <Agents/GameAgent.h>
#include <Interface/Interface.h>

using namespace Hearthstonepp;

TEST(BasicCard, EX1_066)
{
    GameAgent agent(
        Player(new Account("", ""), new Deck("", CardClass::WARRIOR)),
        Player(new Account("", ""), new Deck("", CardClass::MAGE)));
    agent.GetPlayer1().totalMana = 10;
    agent.GetPlayer2().totalMana = 10;

    GameInterface game(agent);

    GameResult result = game.StartGame();

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