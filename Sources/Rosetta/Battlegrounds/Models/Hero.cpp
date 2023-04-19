// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Models/Hero.hpp>
#include <Rosetta/Battlegrounds/Models/Player.hpp>

namespace RosettaStone::Battlegrounds
{
void Hero::Initialize(const Card& heroCard)
{
    card = heroCard;
    health = heroCard.gameTags.at(GameTag::HEALTH);
}

void Hero::TakeDamage(Player& player, int amount)
{
    health -= amount;
    if (health <= 0)
    {
        player.ProcessDefeat();
    }
}
}  // namespace RosettaStone::Battlegrounds
