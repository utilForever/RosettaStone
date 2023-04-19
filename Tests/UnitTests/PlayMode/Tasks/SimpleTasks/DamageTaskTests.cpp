// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DamageTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace SimpleTasks;
using namespace TestUtils;

TEST_CASE("[DamageTask] - Run")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();

    Player* player1 = game.GetPlayer1();
    auto& p1Field = *(player1->GetFieldZone());

    std::vector<Card> cards;
    cards.reserve(5);

    const std::string name = "test";
    for (std::size_t i = 0; i < 5; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        cards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(player1, &cards[i]);
    }

    DamageTask damage(EntityType::FRIENDS, 1);
    damage.SetPlayer(player1);
    damage.SetSource(p1Field[0]);

    TaskStatus result = damage.Run();
    game.ProcessDestroyAndUpdateAura();

    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(player1->GetFieldZone()->GetCount(), 0);
}

TEST_CASE("[DamageTask] - SpellPower")
{
    GameConfig config;
    config.player1Class = CardClass::SHAMAN;
    config.player2Class = CardClass::WARLOCK;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = true;
    config.autoRun = false;

    Game game(config);
    game.Start();

    Player* player1 = game.GetPlayer1();
    auto& p1Field = *(player1->GetFieldZone());

    std::vector<Card> cards;
    cards.reserve(5);

    const std::string name = "test";
    for (std::size_t i = 0; i < 5; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);
        cards.emplace_back(GenerateMinionCard(name + id, 1, 5));
        PlayMinionCard(player1, &cards[i]);
    }

    DamageTask damage1(EntityType::FRIENDS, 1, true);
    damage1.SetPlayer(player1);
    damage1.SetSource(p1Field[0]);

    TaskStatus result = damage1.Run();
    game.ProcessDestroyAndUpdateAura();

    CHECK_EQ(result, TaskStatus::COMPLETE);
    for (std::size_t i = 0; i < 5; ++i)
    {
        CHECK_EQ(p1Field[i]->GetHealth(), 4);
    }

    player1->SetGameTag(GameTag::SPELLPOWER, 1);

    DamageTask damage2(EntityType::FRIENDS, 1, true);
    damage2.SetPlayer(player1);
    damage2.SetSource(p1Field[0]);

    result = damage2.Run();
    game.ProcessDestroyAndUpdateAura();

    CHECK_EQ(result, TaskStatus::COMPLETE);
    for (std::size_t i = 0; i < 5; ++i)
    {
        CHECK_EQ(p1Field[i]->GetHealth(), 2);
    }
}