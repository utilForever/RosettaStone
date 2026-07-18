// Copyright (c) 2017-2026 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>

using namespace RosettaStone;
using namespace PlayMode;

TEST_CASE("[Player] - Game tags share entity storage")
{
    Player player;
    player.SetGameTag(GameTag::TIMEOUT, 30);

    CHECK_EQ(player.GetNativeGameTag(GameTag::TIMEOUT), 30);
}

TEST_CASE("[Player] - AddHeroAndPower shares aura state and moves weapon")
{
    GameConfig config;
    config.player1Class = CardClass::PALADIN;
    config.player2Class = CardClass::MAGE;
    config.formatType = FormatType::WILD;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* player = game.GetPlayer1();
    Hero* oldHero = player->GetHero();

    auto* weapon = dynamic_cast<Weapon*>(
        Entity::GetFromCard(player, Cards::FindCardByID("CS2_091")));
    oldHero->auraEffects = std::make_shared<AuraEffects>(CardType::HERO);
    oldHero->AddWeapon(*weapon);
    const auto auraEffects = oldHero->auraEffects;

    player->AddHeroAndPower(Cards::GetHeroCard(CardClass::MAGE),
                            Cards::GetDefaultHeroPower(CardClass::MAGE));
    CHECK_EQ(oldHero->weapon, nullptr);
    CHECK_EQ(player->GetHero()->weapon, weapon);
    CHECK_EQ(oldHero->auraEffects, auraEffects);
    CHECK_EQ(player->GetHero()->auraEffects, auraEffects);
}
