#include "gtest/gtest.h"

#include <Agents/GameAgent.h>
#include <Interface/Interface.h>

using namespace Hearthstonepp;

TEST(BasicCard, EX1_066)
{
    GameAgent agent(User(new Player("", ""), new Deck("", CardClass::WARRIOR)),
                    User(new Player("", ""), new Deck("", CardClass::MAGE)));
    GameInterface game(agent);

    GameResult result = game.StartGame();

    //var game = new Game(
    //    new GameConfig{StartPlayer = 1, Player1HeroClass = CardClass.WARRIOR,
    //                   Player2HeroClass = CardClass.MAGE, FillDecks = true,
    //                   FillDecksPredictably = true});
    //game.Player1.BaseMana = 10;
    //game.Player2.BaseMana = 10;
    //game.StartGame();

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