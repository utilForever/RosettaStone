// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

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
    gen.player1.hero->weapon = new Weapon(card);

    MetaData result = destroy.Run(gen.player1, gen.player2);
    EXPECT_EQ(result, MetaData::DESTROY_WEAPON_SUCCESS);
    EXPECT_EQ(gen.player1.hero->weapon, static_cast<const Weapon*>(nullptr));
}
