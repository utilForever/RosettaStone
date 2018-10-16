// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <hspp/Tasks/BasicTasks/DestroyMinionTask.h>

using namespace Hearthstonepp;

TEST(DestroyMinionTask, GetTaskID)
{
    auto card = TestUtils::GenerateMinionCard("test", 1, 1);
    BasicTasks::DestroyMinionTask destroy(new Minion(card));
    EXPECT_EQ(destroy.GetTaskID(), +TaskID::DESTROY);
}

TEST(DestroyMinionTask, Run)
{
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);
    Player& player1 = gen.player1;
    Player& player2 = gen.player2;

    std::vector<Card> cards;
    cards.reserve(5);

    std::string name = "test";
    for (size_t i = 0; i < 5; ++i)
    {
        char id = static_cast<char>(i + 0x30);
        cards.emplace_back(TestUtils::GenerateMinionCard(name + id, 1, 1));
        player1.field.emplace_back(new Minion(cards[i]));
    }

    BasicTasks::DestroyMinionTask destroy(player1.field[2]);
    MetaData result = destroy.Run(player1, player2);

    EXPECT_EQ(result, MetaData::DESTROY_MINION_SUCCESS);
    EXPECT_EQ(player1.field.size(), static_cast<size_t>(4));

    EXPECT_EQ(player1.field[0]->card->id, name + '0');
    EXPECT_EQ(player1.field[1]->card->id, name + '1');
    EXPECT_EQ(player1.field[2]->card->id, name + '3');
    EXPECT_EQ(player1.field[3]->card->id, name + '4');

    result = destroy.Run(player1, player2);
    EXPECT_EQ(result, MetaData::DESTROY_MINION_NOT_FOUND);
}
