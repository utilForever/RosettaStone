// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ChangeHeroPowerTask.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace SimpleTasks;

TEST_CASE("[ChangeHeroPowerTask] - Run")
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    config.formatType = FormatType::WILD;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Hero& hero = *game.GetPlayer1()->GetHero();
    HeroPower* oldHeroPower = hero.heroPower;
    const int oldEntityID = oldHeroPower->GetGameTag(GameTag::ENTITY_ID);

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
    CHECK_EQ(oldHeroPower->zone, game.GetPlayer1()->GetSetasideZone());
    CHECK_EQ(game.entityList.at(oldEntityID), oldHeroPower);
}
