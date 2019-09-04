// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Views/Types/Player.hpp>

namespace RosettaStone::Views::Types
{
void Hero::Parse(BoardRefView gameState, PlayerType side)
{
    if (side == gameState.GetSide())
    {
        Parse(gameState.GetHero());
    }
    else
    {
        Parse(gameState.GetOpponentHero());
    }
}

void Hero::Parse(RosettaStone::Hero* hero)
{
    cardID = hero->card->id;
    attack = hero->GetAttack();
    armor = hero->GetArmor();
    damage = hero->GetDamage();
    maxHealth = hero->GetMaxHealth();
    isExhausted = hero->IsExhausted();
}

void HeroPower::Parse(BoardRefView gameState, PlayerType side)
{
    cardID = gameState.GetHeroPower(side).card->id;
    isExhausted = gameState.GetHeroPower(side).IsExhausted();
}

void Player::Parse(BoardRefView gameState, PlayerType side)
{
    hero.Parse(gameState, side);
    heroPower.Parse(gameState, side);
    manaCrystal.Parse(
        gameState.GetRemainingMana(side), gameState.GetTotalMana(side),
        gameState.GetOverloadOwed(side), gameState.GetOverloadLocked(side));
    minions.Parse(gameState, side);
    fatigue = gameState.GetFatigueDamage(side);
}
}  // namespace RosettaStone::Views::Types