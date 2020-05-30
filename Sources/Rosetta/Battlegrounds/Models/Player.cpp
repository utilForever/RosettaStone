// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>

namespace RosettaStone::Battlegrounds
{
void Player::SelectHero(std::size_t idx)
{
    const auto heroCard = Cards::FindCardByDbfID(heroChoices.at(idx));
    hero.Initialize(heroCard);

    selectHeroCallback();
}

void Player::PrepareMinionsForPurchase()
{
    prepareMinionCallback(*this);
}

void Player::PurchaseMinion(std::size_t idx)
{
    handZone.Add(minionsInTavern.at(idx).value(), -1);
}
}  // namespace RosettaStone::Battlegrounds
