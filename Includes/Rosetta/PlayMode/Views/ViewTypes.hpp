// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_VIEW_TYPES_HPP
#define ROSETTASTONE_PLAYMODE_VIEW_TYPES_HPP

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Models/Hero.hpp>
#include <Rosetta/PlayMode/Models/HeroPower.hpp>
#include <Rosetta/PlayMode/Models/Minion.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Models/Weapon.hpp>

namespace RosettaStone::PlayMode::ViewTypes
{
//! This struct contains information of hero.
//! Note that this struct is used for the board view.
struct Hero
{
    int attack = 0;
    int health = 0;
    int armor = 0;
    bool isStealth = false;
    bool isImmune = false;

    void Fill(const PlayMode::Hero& hero)
    {
        attack = hero.GetAttack();
        health = hero.GetHealth();
        armor = hero.GetArmor();
        isStealth = (hero.GetGameTag(GameTag::STEALTH) == 1);
        isImmune = (hero.GetGameTag(GameTag::IMMUNE) == 1);
    }

    bool operator==(const Hero& rhs) const
    {
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

//! This struct contains information of hero for the current player.
//! Note that this struct inherits from Hero struct.
//! Note that this struct is used for the board view.
struct MyHero : public Hero
{
    bool attackable = false;

    void Fill(const PlayMode::Hero& hero, bool _attackable)
    {
        Hero::Fill(hero);
        attackable = _attackable;
    }

    bool operator==(const MyHero& rhs) const
    {
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

//! This struct contains information of hero power.
//! Note that this struct is used for the board view.
struct HeroPower
{
    std::string cardID;
    bool isExhausted = false;

    void Fill(PlayMode::HeroPower& power)
    {
        cardID = power.card->id;
        isExhausted = power.IsExhausted();
    }

    bool operator==(const HeroPower& rhs) const
    {
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

//! This struct contains information of weapon.
//! Note that this struct is used for the board view.
struct Weapon
{
    std::string cardID;
    int attack = 0;
    int durability = 0;
    bool isEquipped = false;

    void Fill(const PlayMode::Weapon& weapon)
    {
        cardID = weapon.card->id;
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

//! This struct contains information of mana crystal.
//! Note that this struct is used for the board view.
struct ManaCrystal
{
    int remaining = 0;
    int total = 0;
    int overloadOwed = 0;
    int overloadLocked = 0;

    void Fill(int remainingMana, int totalMana, int overloadOwedMana,
              int overloadLockedMana)
    {
        remaining = remainingMana;
        total = totalMana;
        overloadOwed = overloadOwedMana;
        overloadLocked = overloadLockedMana;
    }

    bool operator==(const ManaCrystal& rhs) const
    {
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

//! This struct contains information of minion.
//! Note that this struct is used for the board view.
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

    void Fill(const PlayMode::Minion& minion)
    {
        cardID = minion.card->id;
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

//! This struct contains information of minion for the current player.
//! Note that this struct inherits from Minion struct.
//! Note that this struct is used for the board view.
struct MyMinion : public Minion
{
    bool attackable = false;

    void Fill(const PlayMode::Minion& minion, bool _attackable)
    {
        Minion::Fill(minion);
        attackable = _attackable;
    }

    bool operator==(const MyMinion& rhs) const
    {
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

//! This struct contains information of the hand cards for the current player.
//! Note that this struct is used for the board view.
struct MyHandCard
{
    std::string cardID;
    int cost = 0;
    int attack = 0;
    int health = 0;

    void Fill(Playable& entity)
    {
        cardID = entity.card->id;
        cost = entity.GetCost();
        attack = entity.GetGameTag(GameTag::ATK);
        health = entity.GetGameTag(GameTag::HEALTH);
    }

    bool operator==(const MyHandCard& rhs) const
    {
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

//! This struct contains information of the hand cards for the opponent player.
//! Note that this struct is used for the board view.
struct OpHandCard
{
    bool operator==([[maybe_unused]] const OpHandCard& rhs) const
    {
        return true;
    }

    bool operator!=(const OpHandCard& rhs) const
    {
        return !(*this == rhs);
    }
};

using MyHand = std::vector<MyHandCard>;
using OpHand = std::vector<OpHandCard>;

struct Deck
{
    int count = 0;

    void Fill(int _count)
    {
        count = _count;
    }

    bool operator==(const Deck& rhs) const
    {
        return count == rhs.count;
    }

    bool operator!=(const Deck& rhs) const
    {
        return !(*this == rhs);
    }
};
}  // namespace RosettaStone::PlayMode::ViewTypes

namespace std
{
//! \brief Template specialization of std::hash for ViewTypes::Hero.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::Hero>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::Hero& rhs) const noexcept
    {
        std::size_t result = 0;
        CombineHash(result, rhs.attack);
        CombineHash(result, rhs.health);
        CombineHash(result, rhs.armor);
        CombineHash(result, rhs.isStealth);
        CombineHash(result, rhs.isImmune);

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::MyHero.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::MyHero>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::MyHero& rhs) const noexcept
    {
        std::size_t result =
            std::hash<RosettaStone::PlayMode::ViewTypes::Hero>()(rhs);
        CombineHash(result, rhs.attackable);

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::HeroPower.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::HeroPower>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::HeroPower& rhs) const noexcept
    {
        std::size_t result = 0;
        CombineHash(result, rhs.cardID);
        CombineHash(result, rhs.isExhausted);

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::Weapon.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::Weapon>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::Weapon& rhs) const noexcept
    {
        std::size_t result = 0;
        CombineHash(result, rhs.isEquipped);

        if (rhs.isEquipped)
        {
            CombineHash(result, rhs.cardID);
            CombineHash(result, rhs.attack);
            CombineHash(result, rhs.durability);
        }

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::ManaCrystal.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::ManaCrystal>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::ManaCrystal& rhs) const
        noexcept
    {
        std::size_t result = 0;
        CombineHash(result, rhs.remaining);
        CombineHash(result, rhs.total);
        CombineHash(result, rhs.overloadOwed);
        CombineHash(result, rhs.overloadLocked);

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::Minion.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::Minion>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::Minion& rhs) const noexcept
    {
        std::size_t result = 0;
        CombineHash(result, rhs.cardID);
        CombineHash(result, rhs.attack);
        CombineHash(result, rhs.health);
        CombineHash(result, rhs.isSilenced);
        CombineHash(result, rhs.hasTaunt);
        CombineHash(result, rhs.cantAttackHero);
        CombineHash(result, rhs.isStealth);
        CombineHash(result, rhs.isImmune);

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::MyMinion.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::MyMinion>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::MyMinion& rhs) const noexcept
    {
        std::size_t result =
            std::hash<RosettaStone::PlayMode::ViewTypes::Minion>()(rhs);
        CombineHash(result, rhs.attackable);

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::Minions.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::Minions>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::Minions& rhs) const noexcept
    {
        std::size_t result = 0;

        for (const auto& minion : rhs)
        {
            CombineHash(result, minion);
        }

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::MyMinions.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::MyMinions>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::MyMinions& rhs) const noexcept
    {
        std::size_t result = 0;

        for (const auto& minion : rhs)
        {
            CombineHash(result, minion);
        }

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::MyHandCard.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::MyHandCard>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::MyHandCard& rhs) const noexcept
    {
        std::size_t result = 0;
        CombineHash(result, rhs.cardID);
        CombineHash(result, rhs.cost);
        CombineHash(result, rhs.attack);
        CombineHash(result, rhs.health);

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::OpHandCard.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::OpHandCard>
{
    std::size_t operator()([
        [maybe_unused]] const RosettaStone::PlayMode::ViewTypes::OpHandCard&
                               rhs) const noexcept
    {
        return 0;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::MyHand.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::MyHand>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::MyHand& rhs) const noexcept
    {
        std::size_t result = 0;

        for (const auto& entity : rhs)
        {
            CombineHash(result, entity);
        }

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::OpHand.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::OpHand>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::OpHand& rhs) const noexcept
    {
        std::size_t result = 0;

        for (const auto& entity : rhs)
        {
            CombineHash(result, entity);
        }

        return result;
    }
};

//! \brief Template specialization of std::hash for ViewTypes::Deck.
template <>
struct hash<RosettaStone::PlayMode::ViewTypes::Deck>
{
    std::size_t operator()(
        const RosettaStone::PlayMode::ViewTypes::Deck& rhs) const noexcept
    {
        std::size_t result = 0;
        CombineHash(result, rhs.count);

        return result;
    }
};
}  // namespace std

#endif  // ROSETTASTONE_PLAYMODE_VIEW_TYPES_HPP