// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

using namespace RosettaStone;
using namespace PlayMode;
using namespace SimpleTasks;

TEST_CASE("[DrawTask] - Run")
{
    std::vector<Card*> cards;
    std::vector<Playable*> minions;

    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    Game game(config);

    Player* player = game.GetPlayer1();
    auto& playerHand = *(player->GetHandZone());
    auto& playerDeck = *(player->GetDeckZone());

    const auto Generate = [&](std::string&& id) -> Playable* {
        cards.emplace_back(new Card());

        Card* card = cards.back();
        card->id = std::move(id);
        const std::map<GameTag, int> tags;

        minions.emplace_back(new Minion(player, card, tags));

        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        playerDeck.Add(Generate(id + i));
    }

    DrawTask draw(3);
    draw.SetPlayer(player);

    TaskStatus result = draw.Run();
    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(playerHand.GetCount(), 3);

    for (std::size_t i = 0; i < 3; ++i)
    {
        CHECK_EQ(playerHand[i]->card->id, id + static_cast<char>(2 - i + 0x30));
    }

    for (Card* card : cards)
    {
        delete card;
    }
}

TEST_CASE("[DrawTask] - RunExhaust")
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    Game game(config);

    Player* player = game.GetPlayer1();
    auto& playerHand = *(player->GetHandZone());
    auto& playerDeck = *(player->GetDeckZone());

    CHECK_EQ(playerDeck.GetCount(), 0);

    DrawTask draw(3);
    draw.SetPlayer(game.GetPlayer1());

    TaskStatus result = draw.Run();
    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(playerHand.GetCount(), 0);
    CHECK_EQ(playerDeck.GetCount(), 0);
    // Health: 30 - (1 + 2 + 3)
    CHECK_EQ(player->GetHero()->GetHealth(), 24);

    Card card;
    card.id = "card1";
    const std::map<GameTag, int> tags;

    const auto minion = new Minion(player, &card, tags);
    playerDeck.Add(minion);

    result = draw.Run();
    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(playerHand.GetCount(), 1);
    CHECK_EQ(playerHand[0]->card->id, "card1");
    CHECK_EQ(playerDeck.GetCount(), 0);
    // Health: 30 - (1 + 2 + 3 + 4 + 5)
    CHECK_EQ(player->GetHero()->GetHealth(), 15);
}

TEST_CASE("[DrawTask] - RunOverDraw")
{
    std::vector<Card*> cards;
    std::vector<Playable*> minions;

    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    Game game(config);

    Player* player = game.GetPlayer1();
    auto& playerHand = *(player->GetHandZone());
    auto& playerDeck = *(player->GetDeckZone());

    const auto Generate = [&](std::string&& id) -> Playable* {
        cards.emplace_back(new Card());

        Card* card = cards.back();
        card->id = std::move(id);
        const std::map<GameTag, int> tags;

        minions.emplace_back(new Minion(player, card, tags));

        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i <= '2'; ++i)
    {
        playerDeck.Add(Generate(id + i));
    }
    for (char i = '0'; i <= '9'; ++i)
    {
        playerHand.Add(Generate(id + i));
    }

    DrawTask draw(3);
    draw.SetPlayer(player);

    TaskStatus result = draw.Run();
    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(playerDeck.GetCount(), 0);
    CHECK_EQ(playerHand.GetCount(), 10);

    for (Card* card : cards)
    {
        delete card;
    }
}

TEST_CASE("[DrawTask] - RunExhaustOverdraw")
{
    std::vector<Card*> cards;
    std::vector<Playable*> minions;

    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    config.player1Class = CardClass::PRIEST;
    config.player2Class = CardClass::MAGE;
    Game game(config);

    Player* player = game.GetPlayer1();
    auto& playerHand = *(player->GetHandZone());
    auto& playerDeck = *(player->GetDeckZone());

    const auto Generate = [&](std::string&& id) -> Playable* {
        cards.emplace_back(new Card());

        Card* card = cards.back();
        card->id = std::move(id);
        const std::map<GameTag, int> tags;

        minions.emplace_back(new Minion(player, card, tags));
        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i <= '2'; ++i)
    {
        playerDeck.Add(Generate(id + i));
    }
    for (char i = '0'; i <= '8'; ++i)
    {
        playerHand.Add(Generate(id + i));
    }

    DrawTask draw(4);
    draw.SetPlayer(player);

    TaskStatus result = draw.Run();
    CHECK_EQ(result, TaskStatus::COMPLETE);
    CHECK_EQ(playerDeck.GetCount(), 0);
    CHECK_EQ(playerHand.GetCount(), 10);
    CHECK_EQ(playerHand[9]->card->id, "card2");

    for (Card* card : cards)
    {
        delete card;
    }
}