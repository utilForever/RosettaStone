// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_VIEW_TYPES_HPP
#define ROSETTASTONE_VIEW_TYPES_HPP

#include <Rosetta/Models/Hero.hpp>
#include <Rosetta/Models/HeroPower.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Models/Weapon.hpp>

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

struct MyHero : public Hero
{
    bool attackable;

    constexpr static int changeID = 1;

    void Fill(const RosettaStone::Hero& hero, bool _attackable)
    {
        Hero::Fill(hero);
        attackable = _attackable;
    }

    bool operator==(const MyHero& rhs) const
    {
        static_assert(changeID == 1);

        if (Hero::operator!=(rhs))
        {
            return false;
        }
        if (attackable != rhs.attackable)
        {
            return false;
        }

        return true;
    }

    bool operator!=(const MyHero& rhs) const
    {
        return !(*this == rhs);
    }
};

struct HeroPower
{
    std::string cardID;
    bool isExhausted;

    constexpr static int changeID = 1;

    void Fill(RosettaStone::HeroPower& power)
    {
        cardID = power.card.id;
        isExhausted = power.IsExhausted();
    }

    bool operator==(const HeroPower& rhs) const
    {
        static_assert(changeID == 1);

        if (cardID != rhs.cardID)
        {
            return false;
        }
        if (isExhausted != rhs.isExhausted)
        {
            return false;
        }

        return true;
    }

    bool operator!=(const HeroPower& rhs) const
    {
        return !(*this == rhs);
    }
};

struct Weapon
{
    std::string cardID;
    int attack;
    int durability;
    bool isEquipped;

    constexpr static int changeID = 1;

    void Fill(const RosettaStone::Weapon& weapon)
    {
        cardID = weapon.card.id;
        attack = weapon.GetAttack();
        durability = weapon.GetDurability();
        isEquipped = true;
    }

    void Invalidate()
    {
        isEquipped = false;
    }

    bool operator==(const Weapon& rhs) const
    {
        static_assert(changeID == 1);

        if (isEquipped != rhs.isEquipped)
        {
            return false;
        }

        if (isEquipped)
        {
            if (cardID != rhs.cardID)
            {
                return false;
            }
            if (attack != rhs.attack)
            {
                return false;
            }
            if (durability != rhs.durability)
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Weapon& rhs) const
    {
        return !(*this == rhs);
    }
};

struct ManaCrystal
{
    int remaining;
    int total;
    int overloadOwed;
    int overloadLocked;

    constexpr static int changeID = 1;

    void Fill(const RosettaStone::Player& player)
    {
        remaining = player.GetRemainingMana();
        total = player.GetTotalMana();
        overloadOwed = player.GetOverloadOwed();
        overloadLocked = player.GetOverloadLocked();
    }

    bool operator==(const ManaCrystal& rhs) const
    {
        static_assert(changeID == 1);

        if (remaining != rhs.remaining)
        {
            return false;
        }
        if (total != rhs.total)
        {
            return false;
        }
        if (overloadOwed != rhs.overloadOwed)
        {
            return false;
        }
        if (overloadLocked != rhs.overloadLocked)
        {
            return false;
        }

        return true;
    }

    bool operator!=(const ManaCrystal& rhs) const
    {
        return !(*this == rhs);
    }
};
}  // namespace RosettaStone::ViewTypes

#endif  // ROSETTASTONE_VIEW_TYPES_HPP