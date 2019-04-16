// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Policies/BasicPolicy.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawTask.hpp>

using namespace RosettaStone;
using namespace SimpleTasks;

class DrawTestPolicy : public BasicPolicy
{
 public:
    explicit DrawTestPolicy(
        std::function<void(const TaskMeta&)>&& overdrawHandler)
        : m_overdrawHandler(std::move(overdrawHandler))
    {
        // Do nothing
    }

    void NotifyOverDraw(const TaskMeta& meta) override
    {
        m_overdrawHandler(meta);
    }

 private:
    std::function<void(const TaskMeta&)> m_overdrawHandler;
};

TEST(DrawTask, GetTaskID)
{
    const DrawTask draw(1);
    EXPECT_EQ(draw.GetTaskID(), TaskID::DRAW);
}

TEST(DrawTask, Run)
{
    std::vector<Card> cards;
    std::vector<Entity*> minions;

    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player& p = game.GetPlayer1();

    const auto Generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(Card());

        Card card = cards.back();
        card.id = std::move(id);

        minions.emplace_back(new Minion(p, card));

        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i < '3'; ++i)
    {
        p.GetDeck().AddCard(*Generate(id + i));
    }

    DrawTask draw(3);
    TaskStatus result = draw.Run(p);
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(p.GetHand().GetNumOfCards(), 3u);

    for (std::size_t i = 0; i < 3; ++i)
    {
        EXPECT_EQ(p.GetHand().GetCard(i)->card.id,
                  id + static_cast<char>(2 - i + 0x30));
    }
}

TEST(DrawTask, RunExhaust)
{
    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player& p = game.GetPlayer1();
    EXPECT_EQ(p.GetDeck().GetNumOfCards(), 0u);

    DrawTask draw(3);

    TaskStatus result = draw.Run(game.GetPlayer1());
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(p.GetHand().GetNumOfCards(), 0u);
    EXPECT_EQ(p.GetDeck().GetNumOfCards(), 0u);
    // Health: 30 - (1 + 2 + 3)
    EXPECT_EQ(p.GetHero()->GetHealth(), 24);

    Card card;
    card.id = "card1";

    auto minion = new Minion(p, card);
    p.GetDeck().AddCard(*minion);

    result = draw.Run(game.GetPlayer1());
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(p.GetHand().GetNumOfCards(), 1u);
    EXPECT_EQ(p.GetHand().GetCard(0)->card.id, "card1");
    EXPECT_EQ(p.GetDeck().GetNumOfCards(), 0u);
    // Health: 30 - (1 + 2 + 3 + 4 + 5)
    EXPECT_EQ(p.GetHero()->GetHealth(), 15);
}

TEST(DrawTask, RunOverDraw)
{
    std::vector<Card> cards;
    std::vector<Entity*> minions;

    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player& p = game.GetPlayer1();

    const auto Generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(Card());

        Card card = cards.back();
        card.id = std::move(id);

        minions.emplace_back(new Minion(p, card));

        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i <= '2'; ++i)
    {
        p.GetDeck().AddCard(*Generate(id + i));
    }
    for (char i = '0'; i <= '9'; ++i)
    {
        p.GetHand().AddCard(*Generate(id + i));
    }

    DrawTask draw(3);

    DrawTestPolicy policy([&](const TaskMeta& burnt) {
        EXPECT_EQ(burnt.GetID(), TaskID::OVERDRAW);
        EXPECT_EQ(burnt.GetStatus(), TaskStatus::COMPLETE);
        EXPECT_EQ(burnt.GetUserID(), p.playerID);

        EXPECT_TRUE(burnt.HasObjects());

        const auto& entities = burnt.GetObject<SizedPtr<Entity*>>();
        for (std::size_t i = 0; i < 3; ++i)
        {
            EXPECT_EQ(entities[i]->card.id,
                      id + static_cast<char>(2 - i + 0x30));
        }
    });
    p.SetPolicy(&policy);

    TaskStatus result = draw.Run(p);
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(p.GetDeck().GetNumOfCards(), 0u);
    EXPECT_EQ(p.GetHand().GetNumOfCards(), 10u);
}

TEST(DrawTask, RunExhaustOverdraw)
{
    std::vector<Card> cards;
    std::vector<Minion*> minions;

    GameConfig config;
    config.startPlayer = PlayerType::PLAYER1;
    Game game(config);

    Player& p = game.GetPlayer1();

    const auto Generate = [&](std::string&& id) -> Entity* {
        cards.emplace_back(Card());

        Card card = cards.back();
        card.id = std::move(id);

        minions.emplace_back(new Minion(p, card));
        return minions.back();
    };

    const std::string id = "card";
    for (char i = '0'; i <= '2'; ++i)
    {
        p.GetDeck().AddCard(*Generate(id + i));
    }
    for (char i = '0'; i <= '8'; ++i)
    {
        p.GetHand().AddCard(*Generate(id + i));
    }

    DrawTask draw(4);

    DrawTestPolicy policy([&](const TaskMeta& burnt) {
        EXPECT_EQ(burnt.GetID(), TaskID::OVERDRAW);
        EXPECT_EQ(burnt.GetStatus(), TaskStatus::COMPLETE);
        EXPECT_EQ(burnt.GetUserID(), p.playerID);

        EXPECT_TRUE(burnt.HasObjects());

        const auto& entities = burnt.GetObject<SizedPtr<Entity*>>();
        for (std::size_t i = 0; i < 2; ++i)
        {
            EXPECT_EQ(entities[i]->card.id,
                      id + static_cast<char>(2 - i + 0x30));
        }
    });
    p.SetPolicy(&policy);

    TaskStatus result = draw.Run(p);
    EXPECT_EQ(result, TaskStatus::COMPLETE);
    EXPECT_EQ(p.GetDeck().GetNumOfCards(), 0u);
    EXPECT_EQ(p.GetHand().GetNumOfCards(), 10u);
    EXPECT_EQ(p.GetHand().GetCard(9)->card.id, "card2");
}