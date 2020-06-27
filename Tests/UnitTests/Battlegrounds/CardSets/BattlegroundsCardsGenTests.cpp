// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "doctest_proxy.hpp"

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Models/Battle.hpp>

using namespace RosettaStone;
using namespace Battlegrounds;

// --------------------------------- MINION - BATTLEGROUNDS
// [CFM_315] Alleycat - TIER:1 [ATK:1/HP:1]
// - Race: Beast, Set: Gangs, Rarity: Common
// --------------------------------------------------------
// Text: <b>Battlecry:</b> Summon a 1/1 Cat.
// --------------------------------------------------------
// GameTag:
// - BATTLECRY = 1
// --------------------------------------------------------
TEST_CASE("[Battlegrounds : Minion] - CFM_315 : Alleycat")
{
    Player player1, player2;

    Minion minion1(Cards::FindCardByName("Alleycat"));

    player1.hero.Initialize(Cards::FindCardByDbfID(58536));
    player2.hero.Initialize(Cards::FindCardByDbfID(58536));

    player1.handZone.Add(minion1);
    CHECK_EQ(player1.handZone.GetCount(), 1);
    CHECK_EQ(player1.recruitFieldZone.GetCount(), 0);

    player1.PlayCard(0, 0);
    CHECK_EQ(player1.handZone.GetCount(), 0);
    CHECK_EQ(player1.recruitFieldZone.GetCount(), 2);
    CHECK_EQ(player1.recruitFieldZone[0].GetName(), "Alleycat");
    CHECK_EQ(player1.recruitFieldZone[1].GetName(), "Tabbycat");
}