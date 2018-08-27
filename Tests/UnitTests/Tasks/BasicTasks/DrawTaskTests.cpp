#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <Managers/GameAgent.h>
#include <Tasks/BasicTasks/DrawTask.h>
#include <Tasks/TaskAgent.h>

using namespace Hearthstonepp;

TEST(DrawTask, GetTaskID)
{
    TestUtils::GenPlayer gen(CardClass::ROGUE, CardClass::DRUID);
    GameAgent agent(gen.player1, gen.player2);

    BasicTasks::DrawTask draw(1, agent.GetTaskAgent());
    EXPECT_EQ(draw.GetTaskID(), +TaskID::DRAW);
}

TEST(DrawTask, Run)
{
    std::vector<std::unique_ptr<Card>> cards;
    std::vector<std::unique_ptr<Entity>> entities;
    auto generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(std::make_unique<Card>());
        Card* card = cards.back().get();
        card->id = std::move(id);

        entities.emplace_back(std::make_unique<Entity>(card));
        return entities.back().get();
    };

    TestUtils::GenPlayer gen(CardClass::ROGUE, CardClass::DRUID);
    GameAgent agent(gen.player1, gen.player2);

    std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        gen.player1.cards.emplace_back(generate(id + i));
    }

    BasicTasks::DrawTask draw(3, agent.GetTaskAgent());
    MetaData result = draw.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::DRAW_SUCCESS);
    EXPECT_EQ(gen.player1.hand.size(), static_cast<size_t>(3));

    for (size_t i = 0; i < 3; ++i)
    {
        EXPECT_EQ(gen.player1.hand[i]->card->id, id + static_cast<char>(2 - i + 0x30));
    }
}

TEST(DrawTask, RunExhaust)
{
    TestUtils::GenPlayer gen(CardClass::ROGUE, CardClass::DRUID);
    GameAgent agent(gen.player1, gen.player2);

    BasicTasks::DrawTask draw(3, agent.GetTaskAgent());
    MetaData result = draw.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::DRAW_EXHAUST);
    EXPECT_EQ(gen.player1.hand.size(), static_cast<size_t>(0));
    EXPECT_EQ(gen.player1.cards.size(), static_cast<size_t>(0));
    EXPECT_EQ(gen.player1.exhausted, 3);
    EXPECT_EQ(gen.player1.hero->health, static_cast<size_t>(24)); // 30 - (1 + 2 + 3)

    auto card = std::make_unique<Card>();
    card->id = "card1";

    auto entity = std::make_unique<Entity>(card.get());
    gen.player1.cards.emplace_back(entity.get());

    result = draw.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::DRAW_EXHAUST);
    EXPECT_EQ(gen.player1.hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(gen.player1.hand[0]->card->id, "card1");
    EXPECT_EQ(gen.player1.cards.size(), static_cast<size_t>(0));
    EXPECT_EQ(gen.player1.exhausted, 5);
    EXPECT_EQ(gen.player1.hero->health, static_cast<size_t>(15)); // 30 - (1 + 2 + 3 + 4 + 5)
}

TEST(DrawTask, RunOverDraw)
{
    std::vector<std::unique_ptr<Card>> cards;
    std::vector<std::unique_ptr<Entity>> entities;
    auto generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(std::make_unique<Card>());
        Card* card = cards.back().get();
        card->id = std::move(id);
        
        entities.emplace_back(std::make_unique<Entity>(card));
        return entities.back().get();
    };

    TestUtils::GenPlayer gen(CardClass::ROGUE, CardClass::DRUID);
    GameAgent agent(gen.player1, gen.player2);

    std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        gen.player1.cards.emplace_back(generate(id + i));
    }

    gen.player1.hand.resize(10);
    BasicTasks::DrawTask draw(3, agent.GetTaskAgent());
    MetaData result = draw.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::DRAW_OVERDRAW);
    EXPECT_EQ(gen.player1.cards.size(), static_cast<size_t>(0));
    EXPECT_EQ(gen.player1.hand.size(), static_cast<size_t>(10));

    TaskMeta burnt;
    agent.GetTaskMeta(burnt);

    EXPECT_EQ(burnt.id, +TaskID::OVER_DRAW);
    EXPECT_EQ(burnt.status, MetaData::DRAW_OVERDRAW);
    EXPECT_EQ(burnt.userID, gen.player1.id);

    auto burntCard = TaskMeta::ConvertTo<FlatData::EntityVector>(burnt)->vector();
    EXPECT_EQ(burntCard->size(), static_cast<flatbuffers::uoffset_t>(3));
    
    for (flatbuffers::uoffset_t i = 0; i < 3; ++i)
    {
        auto card = burntCard->Get(i)->card();
        EXPECT_EQ(card->id()->str(), id + static_cast<char>(2 - i + 0x30));
    }
}

TEST(DrawTask, RunExhaustOverdraw)
{
    std::vector<std::unique_ptr<Card>> cards;
    std::vector<std::unique_ptr<Entity>> entities;
    auto generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(std::make_unique<Card>());
        Card* card = cards.back().get();
        card->id = std::move(id);

        entities.emplace_back(std::make_unique<Entity>(card));
        return entities.back().get();
    };

    TestUtils::GenPlayer gen(CardClass::ROGUE, CardClass::DRUID);
    GameAgent agent(gen.player1, gen.player2);

    std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        gen.player1.cards.emplace_back(generate(id + i));
    }

    gen.player1.hand.resize(9);
    BasicTasks::DrawTask draw(4, agent.GetTaskAgent());
    MetaData result = draw.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::DRAW_EXHAUST_OVERDRAW);
    EXPECT_EQ(gen.player1.cards.size(), static_cast<size_t>(0));
    EXPECT_EQ(gen.player1.hand.size(), static_cast<size_t>(10));
    EXPECT_EQ(gen.player1.hand[9]->card->id, "card0");

    TaskMeta burnt;
    agent.GetTaskMeta(burnt);

    EXPECT_EQ(burnt.id, +TaskID::OVER_DRAW);
    EXPECT_EQ(burnt.status, MetaData::DRAW_EXHAUST_OVERDRAW);
    EXPECT_EQ(burnt.userID, gen.player1.id);

    auto burntCard = TaskMeta::ConvertTo<FlatData::EntityVector>(burnt)->vector();
    EXPECT_EQ(burntCard->size(), static_cast<flatbuffers::uoffset_t>(2));

    for (flatbuffers::uoffset_t i = 0; i < 2; ++i)
    {
        auto card = burntCard->Get(i)->card();
        EXPECT_EQ(card->id()->str(), id + static_cast<char>(2 - i + 0x30));
    }
}

TEST(DrawCardTask, GetTaskID)
{
    auto card = std::make_unique<Card>();
    BasicTasks::DrawCardTask draw(card.get());
    EXPECT_EQ(draw.GetTaskID(), +TaskID::DRAW);
}

TEST(DrawCardTask, Run)
{
    Cards* cards = Cards::GetInstance();
    TestUtils::GenPlayer gen(CardClass::ROGUE, CardClass::DRUID);

    const Card* nerubian = cards->FindCardByID("AT_036t");
    EXPECT_NE(nerubian, static_cast<const Card*>(nullptr));
    EXPECT_EQ(nerubian->name, "Nerubian");

    const Card* poisonedBlade = cards->FindCardByID("AT_034");
    EXPECT_NE(poisonedBlade, static_cast<const Card*>(nullptr));
    EXPECT_EQ(poisonedBlade->name, "Poisoned Blade");

    auto eNerubian = std::make_unique<Entity>(nerubian);
    auto ePoisonedBlade = std::make_unique<Entity>(poisonedBlade);
    gen.player1.cards.emplace_back(ePoisonedBlade.get());
    gen.player1.cards.emplace_back(eNerubian.get());

    BasicTasks::DrawCardTask drawNerubian(nerubian);
    MetaData result = drawNerubian.Run(gen.player1, gen.player2);

    EXPECT_EQ(result, MetaData::DRAW_SUCCESS);
    EXPECT_EQ(gen.player1.hand.size(), static_cast<size_t>(1));
    EXPECT_EQ(gen.player1.hand[0]->card->id, nerubian->id);
    EXPECT_EQ(gen.player1.cards.size(), static_cast<size_t>(1));
    EXPECT_EQ(gen.player1.cards[0]->card->id, poisonedBlade->id);

    BasicTasks::DrawCardTask drawPoisonedBlade(poisonedBlade);
    result = drawPoisonedBlade.Run(gen.player1, gen.player2);

    EXPECT_EQ(result, MetaData::DRAW_SUCCESS);
    EXPECT_EQ(gen.player1.hand.size(), static_cast<size_t>(2));
    EXPECT_EQ(gen.player1.hand[1]->card->id, poisonedBlade->id);
    EXPECT_EQ(gen.player1.cards.size(), static_cast<size_t>(0));
}
