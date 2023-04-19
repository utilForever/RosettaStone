// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/ControlTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace SimpleTasks;
using namespace TestUtils;

TEST_CASE("[ControlTask] - Run")
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    Game game(config);

    Player* player1 = game.GetPlayer1();
    Player* player2 = game.GetPlayer2();

    auto& player1Field = *(player1->GetFieldZone());
    auto& player2Field = *(player2->GetFieldZone());

    std::vector<Card> player1Cards, player2Cards;
    player1Cards.reserve(6);
    player2Cards.reserve(6);

    const std::string name = "test";
    for (std::size_t i = 0; i < 6; ++i)
    {
        const auto id = static_cast<char>(i + 0x30);

        player1Cards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(player1, &player1Cards[i]);

        player2Cards.emplace_back(GenerateMinionCard(name + id, 1, 1));
        PlayMinionCard(player2, &player2Cards[i]);
    }

    ControlTask control(EntityType::TARGET);
    control.SetPlayer(player1);
    control.SetTarget(player2Field[0]);
    TaskStatus result = control.Run();

    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(player1Field.GetCount(), 7);
    CHECK_EQ(player2Field.GetCount(), 5);

    // Check controlled minion has valid data
    CHECK_EQ(player1Field[6]->GetAttack(), 1);
    CHECK_EQ(player1Field[6]->GetHealth(), 1);

    control.SetPlayer(player1);
    control.SetTarget(player2Field[1]);
    result = control.Run();

    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(player1Field.GetCount(), 7);
    CHECK_EQ(player2Field.GetCount(), 5);
}
