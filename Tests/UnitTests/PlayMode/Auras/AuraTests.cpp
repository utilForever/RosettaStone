// Copyright (c) 2026 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Utils/TestUtils.hpp>

#include <Rosetta/PlayMode/Auras/Aura.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Enchants/Effects.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[Aura] - Location is skipped by minion auras")
{
    GameConfig config;
    config.formatType = FormatType::STANDARD;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* player = game.GetCurrentPlayer();
    auto& field = *player->GetFieldZone();

    auto ownerCard = TestUtils::GenerateMinionCard("owner", 1, 1);
    auto neighborCard = TestUtils::GenerateMinionCard("neighbor", 1, 1);

    const auto AddLocation = [&] {
        field.Add(Entity::GetFromCard(player, Cards::FindCardByID("REV_983")));
    };
    const auto Activate = [&](AuraType type, Minion* owner) {
        Aura aura(type, { Effects::AttackN(1) });
        aura.Activate(owner);
        game.UpdateAura();
    };

    SUBCASE("Left location")
    {
        AddLocation();
        TestUtils::PlayMinionCard(player, &ownerCard);
        TestUtils::PlayMinionCard(player, &neighborCard);

        Activate(AuraType::ADJACENT, field[1]);
        CHECK_EQ(field[2]->GetAttack(), 2);
    }

    SUBCASE("Right location")
    {
        TestUtils::PlayMinionCard(player, &neighborCard);
        TestUtils::PlayMinionCard(player, &ownerCard);
        AddLocation();

        Activate(AuraType::ADJACENT, field[1]);
        CHECK_EQ(field[0]->GetAttack(), 2);
    }

    SUBCASE("Restless field aura")
    {
        TestUtils::PlayMinionCard(player, &ownerCard);
        TestUtils::PlayMinionCard(player, &neighborCard);
        AddLocation();

        Aura aura(AuraType::FIELD, { Effects::AttackN(1) });
        aura.condition =
            std::make_shared<SelfCondition>([](Playable*) { return true; });
        aura.restless = true;

        aura.Activate(field[0]);
        game.UpdateAura();

        CHECK_EQ(field[0]->GetAttack(), 2);
        CHECK_EQ(field[1]->GetAttack(), 2);
    }
}
