// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Cards/Cards.hpp>
#include <hspp/Managers/GameAgent.hpp>
#include <hspp/Tasks/SimpleTasks/DrawTask.hpp>

using namespace Hearthstonepp;
using namespace SimpleTasks;

TEST(DrawTask, GetTaskID)
{
    const DrawTask draw(1);
    EXPECT_EQ(draw.GetTaskID(), +TaskID::DRAW);
}

TEST(DrawTask, Run)
{
    std::vector<Card> cards;
    std::vector<Entity*> minions;

    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);
    Player& p = agent.GetPlayer1();

    const auto Generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(Card());

        Card card = cards.back();
        card.id = std::move(id);

        minions.emplace_back(new Minion(&agent, card));

        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        p.GetDeck().emplace_back(Generate(id + i));
    }

    DrawTask draw(3);
    MetaData result = draw.Run(p);
    EXPECT_EQ(result, MetaData::DRAW_SUCCESS);
    EXPECT_EQ(p.GetHand().size(), 3u);

    for (size_t i = 0; i < 3; ++i)
    {
        EXPECT_EQ(p.GetHand()[i]->card->id,
                  id + static_cast<char>(2 - i + 0x30));
    }
}

TEST(DrawTask, RunExhaust)
{
    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);
    Player& p = agent.GetPlayer1();
    EXPECT_EQ(p.GetDeck().size(), 0u);

    DrawTask draw(3);

    MetaData result = draw.Run(agent.GetPlayer1());
    EXPECT_EQ(result, MetaData::DRAW_EXHAUST);
    EXPECT_EQ(p.GetHand().size(), 0u);
    EXPECT_EQ(p.GetDeck().size(), 0u);
    EXPECT_EQ(p.GetNumCardAfterExhaust(), 3);
    // Health: 30 - (1 + 2 + 3)
    EXPECT_EQ(p.GetHero()->health, 24);

    Card card;
    card.id = "card1";

    auto minion = new Minion(&agent, card);
    p.GetDeck().emplace_back(minion);

    result = draw.Run(agent.GetPlayer1());
    EXPECT_EQ(result, MetaData::DRAW_EXHAUST);
    EXPECT_EQ(p.GetHand().size(), 1u);
    EXPECT_EQ(p.GetHand()[0]->card->id, "card1");
    EXPECT_EQ(p.GetDeck().size(), 0u);
    EXPECT_EQ(p.GetNumCardAfterExhaust(), 5);
    // Health: 30 - (1 + 2 + 3 + 4 + 5)
    EXPECT_EQ(p.GetHero()->health, 15);
}

TEST(DrawTask, RunOverDraw)
{
    std::vector<Card> cards;
    std::vector<Entity*> minions;

    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);
    Player& p = agent.GetPlayer1();

    const auto Generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(Card());

        Card card = cards.back();
        card.id = std::move(id);

        minions.emplace_back(new Minion(&agent, card));

        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        p.GetDeck().emplace_back(Generate(id + i));
    }

    p.GetHand().resize(10);

    DrawTask draw(3);

    MetaData result = draw.Run(p);
    EXPECT_EQ(result, MetaData::DRAW_OVERDRAW);
    EXPECT_EQ(p.GetDeck().size(), 0u);
    EXPECT_EQ(p.GetHand().size(), 10u);

    TaskMeta burnt;
    agent.GetTaskMeta(burnt);
    EXPECT_EQ(burnt.GetID(), +TaskID::OVERDRAW);
    EXPECT_EQ(burnt.GetStatus(), MetaData::DRAW_OVERDRAW);
    EXPECT_EQ(burnt.GetUserID(), p.GetID());

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
    std::vector<Minion*> minions;

    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);
    Player& p = agent.GetPlayer1();

    const auto Generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(Card());

        Card card = cards.back();
        card.id = std::move(id);

        minions.emplace_back(new Minion(&agent, card));
        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        p.GetDeck().emplace_back(Generate(id + i));
    }

    p.GetHand().resize(9);

    DrawTask draw(4);

    MetaData result = draw.Run(p);
    EXPECT_EQ(result, MetaData::DRAW_EXHAUST_OVERDRAW);
    EXPECT_EQ(p.GetDeck().size(), 0u);
    EXPECT_EQ(p.GetHand().size(), 10u);
    EXPECT_EQ(p.GetHand()[9]->card->id, "card0");

    TaskMeta burnt;
    agent.GetTaskMeta(burnt);
    EXPECT_EQ(burnt.GetID(), +TaskID::OVERDRAW);
    EXPECT_EQ(burnt.GetStatus(), MetaData::DRAW_EXHAUST_OVERDRAW);
    EXPECT_EQ(burnt.GetUserID(), p.GetID());

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
    const DrawCardTask draw(card);

    EXPECT_EQ(draw.GetTaskID(), +TaskID::DRAW);
}

TEST(DrawCardTask, Run)
{
    Cards& instance = Cards::GetInstance();
    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, PlayerType::PLAYER1);

    Card nerubian = instance.FindCardByID("AT_036t");
    EXPECT_NE(nerubian.id, "");
    EXPECT_EQ(nerubian.name, "Nerubian");

    Card poisonedBlade = instance.FindCardByID("AT_034");
    EXPECT_NE(poisonedBlade.id, "");
    EXPECT_EQ(poisonedBlade.name, "Poisoned Blade");

    auto minionNerubian = new Minion(&agent, nerubian);
    auto weaponPoisonedBlade = new Weapon(&agent, poisonedBlade);
    agent.GetPlayer1().GetDeck().emplace_back(weaponPoisonedBlade);
    agent.GetPlayer1().GetDeck().emplace_back(minionNerubian);

    DrawCardTask drawNerubian(nerubian);
    MetaData result = drawNerubian.Run(agent.GetPlayer1());

    EXPECT_EQ(result, MetaData::DRAW_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().GetHand().size(), 1u);
    EXPECT_EQ(agent.GetPlayer1().GetHand()[0]->card->id, nerubian.id);
    EXPECT_EQ(agent.GetPlayer1().GetDeck().size(), 1u);
    EXPECT_EQ(agent.GetPlayer1().GetDeck()[0]->card->id, poisonedBlade.id);

    DrawCardTask drawPoisonedBlade(poisonedBlade);
    result = drawPoisonedBlade.Run(agent.GetPlayer1());

    EXPECT_EQ(result, MetaData::DRAW_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().GetHand().size(), 2u);
    EXPECT_EQ(agent.GetPlayer1().GetHand()[1]->card->id, poisonedBlade.id);
    EXPECT_EQ(agent.GetPlayer1().GetDeck().size(), 0u);

    delete minionNerubian;
    delete weaponPoisonedBlade;
}
