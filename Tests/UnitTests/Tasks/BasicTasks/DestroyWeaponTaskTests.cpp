#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <hspp/Tasks/BasicTasks/DestroyWeaponTask.h>

using namespace Hearthstonepp;

TEST(DestroyWeaponTask, GetTaskID)
{
    BasicTasks::DestroyWeaponTask destroy;
    EXPECT_EQ(destroy.GetTaskID(), +TaskID::DESTROY);
}

TEST(DestroyWeaponTask, Run)
{
    BasicTasks::DestroyWeaponTask destroy;
    TestUtils::PlayerGenerator gen(CardClass::DRUID, CardClass::ROGUE);

    Card card;
    card.id = "weapon1";

    Weapon weapon(card);
    gen.player1.hero->weapon = &weapon;

    MetaData result = destroy.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::DESTROY_WEAPON_SUCCESS);
    EXPECT_EQ(gen.player1.hero->weapon, static_cast<const Weapon*>(nullptr));
}
