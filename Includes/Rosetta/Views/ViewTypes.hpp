// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_VIEW_TYPES_HPP
#define ROSETTASTONE_VIEW_TYPES_HPP

#include <Rosetta/Models/Hero.hpp>

namespace RosettaStone::ViewTypes
{
struct Hero
{
    int attack;
    int health;
    int armor;

    bool isStealth;
    bool isImmune;

    constexpr static int changeID = 2;

    void Fill(const RosettaStone::Hero& hero)
    {
        static_assert(changeID == 2);

        attack = hero.GetAttack();
        health = hero.GetHealth();
        armor = hero.GetArmor();

        isStealth = (hero.GetGameTag(GameTag::STEALTH) == 1);
        isImmune = (hero.GetGameTag(GameTag::IMMUNE) == 1);
    }

    bool operator==(const Hero& rhs) const
    {
        static_assert(changeID == 2);

        if (attack != rhs.attack)
        {
            return false;
        }
        if (health != rhs.health)
        {
            return false;
        }
        if (armor != rhs.armor)
        {
            return false;
        }
        if (isStealth != rhs.isStealth)
        {
            return false;
        }
        if (isImmune != rhs.isImmune)
        {
            return false;
        }

        return true;
    }

    bool operator!=(const Hero& rhs) const
    {
        return !(*this == rhs);
    }
};
}  // namespace RosettaStone::ViewTypes

#endif  // ROSETTASTONE_VIEW_TYPES_HPP