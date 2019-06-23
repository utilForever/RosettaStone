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
    int attack = 0;
    int health = 0;
    int armor = 0;
    bool isStealth = false;
    bool isImmune = false;

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
    bool attackable = false;

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
    bool isExhausted = false;

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
    int attack = 0;
    int durability = 0;
    bool isEquipped = false;

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
    int remaining = 0;
    int total = 0;
    int overloadOwed = 0;
    int overloadLocked = 0;

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

struct Minion
{
    std::string cardID;
    int attack = 0;
    int health = 0;
    bool isSilenced = false;
    bool hasTaunt = false;
    bool cantAttackHero = false;
    bool isStealth = false;
    bool isImmune = false;

    constexpr static int changeID = 3;

    void Fill(const RosettaStone::Minion& minion)
    {
        cardID = minion.card.id;
        attack = minion.GetAttack();
        health = minion.GetHealth();
        isSilenced = (minion.GetGameTag(GameTag::SILENCED) == 1);
        hasTaunt = (minion.GetGameTag(GameTag::TAUNT) == 1);
        cantAttackHero =
            (minion.GetGameTag(GameTag::CANNOT_ATTACK_HEROES) == 1);
        isStealth = (minion.GetGameTag(GameTag::STEALTH) == 1);
        isImmune = (minion.GetGameTag(GameTag::IMMUNE) == 1);
    }

    bool operator==(const Minion& rhs) const
    {
        static_assert(changeID == 3);

        if (cardID != rhs.cardID)
        {
            return false;
        }
        if (attack != rhs.attack)
        {
            return false;
        }
        if (health != rhs.health)
        {
            return false;
        }
        if (isSilenced != rhs.isSilenced)
        {
            return false;
        }
        if (hasTaunt != rhs.hasTaunt)
        {
            return false;
        }
        if (cantAttackHero != rhs.cantAttackHero)
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

    bool operator!=(const Minion& rhs) const
    {
        return !(*this == rhs);
    }
};

struct MyMinion : public Minion
{
    bool attackable = false;

    constexpr static int changeID = 1;

    void Fill(const RosettaStone::Minion& minion, bool _attackable)
    {
        Minion::Fill(minion);
        attackable = _attackable;
    }

    bool operator==(const MyMinion& rhs) const
    {
        static_assert(changeID == 1);

        if (Minion::operator!=(rhs))
        {
            return false;
        }
        if (attackable != rhs.attackable)
        {
            return false;
        }

        return true;
    }

    bool operator!=(const MyMinion& rhs) const
    {
        return !(*this == rhs);
    }
};

using Minions = std::vector<Minion>;
using MyMinions = std::vector<MyMinion>;

struct MyHandCard
{
    std::string cardID;
    int cost;
    int attack;
    int health;

    constexpr static int changeID = 1;

    void Fill(RosettaStone::Entity& entity)
    {
        cardID = entity.card.id;
        cost = entity.GetCost();
        attack = entity.GetGameTag(GameTag::ATK);
        health = entity.GetGameTag(GameTag::HEALTH);
    }

    bool operator==(const MyHandCard& rhs) const
    {
        static_assert(changeID == 1);

        if (cardID != rhs.cardID)
        {
            return false;
        }
        if (cost != rhs.cost)
        {
            return false;
        }
        if (attack != rhs.attack)
        {
            return false;
        }
        if (health != rhs.health)
        {
            return false;
        }

        return true;
    }

    bool operator!=(const MyHandCard& rhs) const
    {
        return !(*this == rhs);
    }
};

struct OpHandCard
{
    constexpr static int changeID = 1;

    bool operator==([[maybe_unused]] const OpHandCard& rhs) const
    {
        static_assert(changeID == 1);

        return true;
    }

    bool operator!=(const OpHandCard& rhs) const
    {
        return !(*this == rhs);
    }
};

using MyHand = std::vector<MyHandCard>;
using OpHand = std::vector<OpHandCard>;
}  // namespace RosettaStone::ViewTypes

#endif  // ROSETTASTONE_VIEW_TYPES_HPP