#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <hspp/Cards/Cards.h>
#include <hspp/Tasks/BasicTasks/ShuffleTask.h>

using namespace Hearthstonepp;

TEST(ShuffleTask, GetTaskID)
{
    BasicTasks::ShuffleTask init;
    EXPECT_EQ(init.GetTaskID(), +TaskID::SHUFFLE);
}

TEST(ShuffleTask, Run)
{
    BasicTasks::ShuffleTask init;
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);

    for (int i = 0; i < 5; i++)
    {
        auto card = TestUtils::GenerateMinionCard("minion", 5, 1);
        Minion minion(*card.get());
        gen.player1.cards.emplace_back(&minion);
    }

    MetaData result = init.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::SHUFFLE_SUCCESS);
    EXPECT_EQ(gen.player1.cards.size(), static_cast<size_t>(5));
}
