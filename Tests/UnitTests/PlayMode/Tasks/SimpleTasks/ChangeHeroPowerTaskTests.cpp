// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ChangeHeroPowerTask.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace SimpleTasks;

TEST_CASE("[ChangeHeroPowerTask] - Run")
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    Game game(config);

    Hero& hero = *game.GetPlayer1()->GetHero();

    hero.heroPower->SetExhausted(true);
    CHECK_EQ(hero.heroPower->card->id,
              Cards::GetDefaultHeroPower(CardClass::PRIEST)->id);
    CHECK(hero.heroPower->IsExhausted());

    ChangeHeroPowerTask change(Cards::GetDefaultHeroPower(CardClass::MAGE)->id);
    change.SetPlayer(game.GetPlayer1());

    TaskStatus result = change.Run();
    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(hero.heroPower->card->id,
              Cards::GetDefaultHeroPower(CardClass::MAGE)->id);
    CHECK_FALSE(hero.heroPower->IsExhausted());
}