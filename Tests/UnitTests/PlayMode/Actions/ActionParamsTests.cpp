// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/PlayMode/Actions/ActionParams.hpp>
#include <Rosetta/PlayMode/Actions/ActionValidChecker.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

using namespace RosettaStone;
using namespace PlayMode;

class TestActionParams : public ActionParams
{
 public:
    TestActionParams() = default;

    TestActionParams(const TestActionParams&) = delete;
    TestActionParams(TestActionParams&&) noexcept = delete;

    TestActionParams& operator=(const TestActionParams&) = delete;
    TestActionParams& operator=(TestActionParams&&) noexcept = delete;

    void Init(const Game& game)
    {
        m_game = &game;
        ActionParams::Initialize(*m_game);
    }

    std::size_t GetNumber(ActionType actionType, ActionChoices& choices) final
    {
        if (actionType != ActionType::MAIN_ACTION)
        {
            if (choices.Size() == 1)
            {
                return choices.Get(0);
            }
        }

        const std::size_t count = choices.Size();
        const auto randIdx = Random::get<std::size_t>(0, count - 1);
        const int result = static_cast<int>(randIdx);

        return result;
    }

 private:
    const Game* m_game = nullptr;
};

TEST_CASE("[ActionParams] - Getters")
{
    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_ACTION);

    Player* player1 = game.GetPlayer1();
    Player* player2 = game.GetPlayer2();
    player1->SetTotalMana(10);
    player1->SetUsedMana(0);
    player2->SetTotalMana(10);
    player2->SetUsedMana(0);

    const auto weapon1 = dynamic_cast<Weapon*>(Entity::GetFromCard(
        player1, Cards::GetInstance().FindCardByName("Fiery War Axe")));
    player1->GetHero()->AddWeapon(*weapon1);

    const auto weapon2 = dynamic_cast<Weapon*>(Entity::GetFromCard(
        player2, Cards::GetInstance().FindCardByName("Arcanite Reaper")));
    player2->GetHero()->AddWeapon(*weapon2);

    for (std::size_t i = 0; i < 3; ++i)
    {
        Playable* playable1 = Entity::GetFromCard(
            player1, Cards::GetInstance().FindCardByName("Fireball"),
            std::nullopt, player1->GetHandZone());
        player1->GetHandZone()->Add(playable1);
    }

    for (std::size_t i = 0; i < 3; ++i)
    {
        Playable* playable2 = Entity::GetFromCard(
            player2, Cards::GetInstance().FindCardByName("Frostbolt"),
            std::nullopt, player2->GetHandZone());
        player2->GetHandZone()->Add(playable2);
    }

    for (std::size_t i = 0; i < 6; ++i)
    {
        Playable* playable1 = Entity::GetFromCard(
            player1, Cards::GetInstance().FindCardByName("Flame Imp"),
            std::nullopt, player1->GetFieldZone());
        player1->GetFieldZone()->Add(playable1);
    }

    for (std::size_t i = 0; i < 4; ++i)
    {
        Playable* playable2 = Entity::GetFromCard(
            player2, Cards::GetInstance().FindCardByName("Wisp"), std::nullopt,
            player2->GetFieldZone());
        player2->GetFieldZone()->Add(playable2);
    }

    TestActionParams actionParams;
    actionParams.Init(game);

    CHECK(actionParams.GetMinionPutLocation(0) == 0);
    CHECK(actionParams.GetSpecifiedTarget({}) == nullptr);
    CHECK(actionParams.GetSpecifiedTarget(
                    { (*player1->GetFieldZone())[0] }) != nullptr);
    CHECK(actionParams.ChooseOne({ 0 }) == 0);
    CHECK(actionParams.ChooseHandCard() != nullptr);
    CHECK(actionParams.GetAttacker() != nullptr);
}