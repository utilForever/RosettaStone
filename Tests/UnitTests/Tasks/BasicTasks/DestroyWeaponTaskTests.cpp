// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <hspp/Managers/GameAgent.h>
#include <hspp/Tasks/BasicTasks/DestroyWeaponTask.h>

using namespace Hearthstonepp;

TEST(DestroyWeaponTask, GetTaskID)
{
    const BasicTasks::DestroyWeaponTask destroy;
    EXPECT_EQ(destroy.GetTaskID(), +TaskID::DESTROY);
}

TEST(DestroyWeaponTask, Run)
{
    BasicTasks::DestroyWeaponTask destroy;
    GameAgent agent(CardClass::ROGUE, CardClass::DRUID, 1);

    Card card;
    card.id = "weapon1";
    agent.GetPlayer1().hero->weapon = new Weapon(card);

    MetaData result = destroy.Run(agent.GetPlayer1());
    EXPECT_EQ(result, MetaData::DESTROY_WEAPON_SUCCESS);
    EXPECT_EQ(agent.GetPlayer1().hero->weapon,
              static_cast<const Weapon*>(nullptr));
}
