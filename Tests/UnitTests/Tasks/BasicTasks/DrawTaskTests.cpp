// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <hspp/Cards/Cards.h>
#include <hspp/Managers/GameAgent.h>
#include <hspp/Tasks/BasicTasks/DrawTask.h>
#include <hspp/Tasks/TaskAgent.h>

using namespace Hearthstonepp;

TEST(DrawTask, GetTaskID)
{
    TestUtils::PlayerGenerator gen(CardClass::ROGUE, CardClass::DRUID);
    GameAgent agent(std::move(gen.player1), std::move(gen.player2));

    const BasicTasks::DrawTask draw(agent.GetTaskAgent(), 1);
    EXPECT_EQ(draw.GetTaskID(), +TaskID::DRAW);
}

TEST(DrawTask, Run)
{
    std::vector<Card> cards;
    std::vector<Entity*> entities;
    const auto generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(Card());
        Card card = cards.back();
        card.id = std::move(id);

        entities.emplace_back(new Entity(card));
        return entities.back();
    };

    TestUtils::PlayerGenerator gen(CardClass::ROGUE, CardClass::DRUID);
    GameAgent agent(std::move(gen.player1), std::move(gen.player2));

    Player& p1 = agent.GetPlayer1();
    Player& p2 = agent.GetPlayer2();

    const std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        p1.cards.emplace_back(generate(id + i));
    }

    BasicTasks::DrawTask draw(agent.GetTaskAgent(), 3);
    MetaData result = draw.Run(p1, p2);
    EXPECT_EQ(result, MetaData::DRAW_SUCCESS);
    EXPECT_EQ(p1.hand.size(), static_cast<size_t>(3));

    for (size_t i = 0; i < 3; ++i)
    {
        EXPECT_EQ(p1.hand[i]->card->id, id + static_cast<char>(2 - i + 0x30));
    }
}

TEST(DrawTask, RunExhaust)
{
    TestUtils::PlayerGenerator gen(CardClass::ROGUE, CardClass::DRUID);
    GameAgent agent(std::move(gen.player1), std::move(gen.player2));

    Player& p1 = agent.GetPlayer1();
    EXPECT_EQ(p1.cards.size(), static_cast<size_t>(0));

    BasicTasks::DrawTask draw(agent.GetTaskAgent(), 3);
    MetaData result = draw.Run(agent.GetPlayer1(), agent.GetPlayer2());
    EXPECT_EQ(result, MetaData::DRAW_EXHAUST);
    EXPECT_EQ(p1.hand.size(), static_cast<size_t>(0));
    EXPECT_EQ(p1.cards.size(), static_cast<size_t>(0));
    EXPECT_EQ(p1.exhausted, 3);
    EXPECT_EQ(p1.hero->health,
              static_cast<size_t>(24));  // 30 - (1 + 2 + 3)

    Card card;
    card.id = "card1";

    auto entity = new Entity(card);
    p1.cards.emplace_back(entity);

    result = draw.Run(agent.GetPlayer1(), agent.GetPlayer2());
    EXPECT_EQ(result, MetaData::DRAW_EXHAUST);
    EXPECT_EQ(p1.hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(p1.hand[0]->card->id, "card1");
    EXPECT_EQ(p1.cards.size(), static_cast<size_t>(0));
    EXPECT_EQ(p1.exhausted, 5);
    EXPECT_EQ(p1.hero->health,
              static_cast<size_t>(15));  // 30 - (1 + 2 + 3 + 4 + 5)
}

TEST(DrawTask, RunOverDraw)
{
    std::vector<Card> cards;
    std::vector<Entity*> entities;
    const auto generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(Card());
        Card card = cards.back();
        card.id = std::move(id);

        entities.emplace_back(new Entity(card));
        return entities.back();
    };

    TestUtils::PlayerGenerator gen(CardClass::ROGUE, CardClass::DRUID);
    GameAgent agent(std::move(gen.player1), std::move(gen.player2));

    Player& p1 = agent.GetPlayer1();
    Player& p2 = agent.GetPlayer2();

    const std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        p1.cards.emplace_back(generate(id + i));
    }

    p1.hand.resize(10);
    BasicTasks::DrawTask draw(agent.GetTaskAgent(), 3);
    MetaData result = draw.Run(p1, p2);
    EXPECT_EQ(result, MetaData::DRAW_OVERDRAW);
    EXPECT_EQ(p1.cards.size(), static_cast<size_t>(0));
    EXPECT_EQ(p1.hand.size(), static_cast<size_t>(10));

    TaskMeta burnt;
    agent.GetTaskMeta(burnt);

    EXPECT_EQ(burnt.id, +TaskID::OVERDRAW);
    EXPECT_EQ(burnt.status, MetaData::DRAW_OVERDRAW);
    EXPECT_EQ(burnt.userID, p1.id);

    auto burntCard =
        TaskMeta::ConvertTo<FlatData::EntityVector>(burnt)->vector();
    EXPECT_EQ(burntCard->size(), static_cast<flatbuffers::uoffset_t>(3));

    for (flatbuffers::uoffset_t i = 0; i < 3; ++i)
    {
        auto card = burntCard->Get(i)->card();
        EXPECT_EQ(card->id()->str(), id + static_cast<char>(2 - i + 0x30));
    }
}

TEST(DrawTask, RunExhaustOverdraw)
{
    std::vector<Card> cards;
    std::vector<Entity*> entities;
    const auto generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(Card());
        Card card = cards.back();
        card.id = std::move(id);

        entities.emplace_back(new Entity(card));
        return entities.back();
    };

    TestUtils::PlayerGenerator gen(CardClass::ROGUE, CardClass::DRUID);
    GameAgent agent(std::move(gen.player1), std::move(gen.player2));

    Player& p1 = agent.GetPlayer1();
    Player& p2 = agent.GetPlayer2();

    const std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        p1.cards.emplace_back(generate(id + i));
    }

    p1.hand.resize(9);
    BasicTasks::DrawTask draw(agent.GetTaskAgent(), 4);
    MetaData result = draw.Run(p1, p2);
    EXPECT_EQ(result, MetaData::DRAW_EXHAUST_OVERDRAW);
    EXPECT_EQ(p1.cards.size(), static_cast<size_t>(0));
    EXPECT_EQ(p1.hand.size(), static_cast<size_t>(10));
    EXPECT_EQ(p1.hand[9]->card->id, "card0");

    TaskMeta burnt;
    agent.GetTaskMeta(burnt);

    EXPECT_EQ(burnt.id, +TaskID::OVERDRAW);
    EXPECT_EQ(burnt.status, MetaData::DRAW_EXHAUST_OVERDRAW);
    EXPECT_EQ(burnt.userID, p1.id);

    auto burntCard =
        TaskMeta::ConvertTo<FlatData::EntityVector>(burnt)->vector();
    EXPECT_EQ(burntCard->size(), static_cast<flatbuffers::uoffset_t>(2));

    for (flatbuffers::uoffset_t i = 0; i < 2; ++i)
    {
        auto card = burntCard->Get(i)->card();
        EXPECT_EQ(card->id()->str(), id + static_cast<char>(2 - i + 0x30));
    }
}

TEST(DrawCardTask, GetTaskID)
{
    const Card card{};
    const BasicTasks::DrawCardTask draw(card);
    EXPECT_EQ(draw.GetTaskID(), +TaskID::DRAW);
}

TEST(DrawCardTask, Run)
{
    Cards& instance = Cards::GetInstance();
    TestUtils::PlayerGenerator gen(CardClass::ROGUE, CardClass::DRUID);

    Card nerubian = instance.FindCardByID("AT_036t");
    EXPECT_NE(nerubian.id, "");
    EXPECT_EQ(nerubian.name, "Nerubian");

    Card poisonedBlade = instance.FindCardByID("AT_034");
    EXPECT_NE(poisonedBlade.id, "");
    EXPECT_EQ(poisonedBlade.name, "Poisoned Blade");

    auto minionNerubian = new Entity(nerubian);
    auto weaponPoisonedBlade = new Entity(poisonedBlade);
    gen.player1.cards.emplace_back(weaponPoisonedBlade);
    gen.player1.cards.emplace_back(minionNerubian);

    BasicTasks::DrawCardTask drawNerubian(nerubian);
    MetaData result = drawNerubian.Run(gen.player1, gen.player2);

    EXPECT_EQ(result, MetaData::DRAW_SUCCESS);
    EXPECT_EQ(gen.player1.hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(gen.player1.hand[0]->card->id, nerubian.id);
    EXPECT_EQ(gen.player1.cards.size(), static_cast<size_t>(1));
    EXPECT_EQ(gen.player1.cards[0]->card->id, poisonedBlade.id);

    BasicTasks::DrawCardTask drawPoisonedBlade(poisonedBlade);
    result = drawPoisonedBlade.Run(gen.player1, gen.player2);

    EXPECT_EQ(result, MetaData::DRAW_SUCCESS);
    EXPECT_EQ(gen.player1.hand.size(), static_cast<size_t>(2));
    EXPECT_EQ(gen.player1.hand[1]->card->id, poisonedBlade.id);
    EXPECT_EQ(gen.player1.cards.size(), static_cast<size_t>(0));

    delete minionNerubian;
    delete weaponPoisonedBlade;
}
