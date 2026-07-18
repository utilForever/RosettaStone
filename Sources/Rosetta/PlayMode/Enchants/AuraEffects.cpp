// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2024 Chris Ohk

#include <Rosetta/PlayMode/Enchants/AuraEffects.hpp>

#include <stdexcept>

namespace
{
class InvalidAuraEffectOperation final : public std::logic_error
{
 public:
    using std::logic_error::logic_error;
};
}  // namespace

namespace RosettaStone::PlayMode
{
AuraEffects::AuraEffects(CardType type) : m_type(type)
{
    using enum CardType;

    switch (type)
    {
        case HERO:
        case MINION:
        case WEAPON:
        case SPELL:
            break;
        default:
            throw std::invalid_argument(
                "AuraEffects::AuraEffects() - Invalid card type!");
    }
}

int AuraEffects::GetGameTag(GameTag tag) const
{
    using enum GameTag;

    switch (tag)
    {
        case IMMUNE:
            return GetImmune();
        case CANT_BE_TARGETED_BY_SPELLS:
        case CANT_BE_TARGETED_BY_HERO_POWERS:
            return GetCantBeTargetedBySpells();
        case ATK:
            return GetAttack();
        case CANNOT_ATTACK_HEROES:
            return GetCannotAttackHeroes();
        case HEROPOWER_DAMAGE:
            return GetHeroPowerDamage();
        case HEALTH:
            return GetHealth();
        case WINDFURY:
            return GetWindfury();
        case TAUNT:
            return GetTaunt();
        case CHARGE:
            return GetCharge();
        case RUSH:
            return GetRush();
        case LIFESTEAL:
            return GetLifesteal();
        case CANT_ATTACK:
            return GetCantAttack();
        default:
            return 0;
    }
}

void AuraEffects::SetGameTag(GameTag tag, int value) const
{
    using enum GameTag;

    switch (tag)
    {
        case IMMUNE:
            SetImmune(value);
            break;
        case CANT_BE_TARGETED_BY_SPELLS:
        case CANT_BE_TARGETED_BY_HERO_POWERS:
            SetCantBeTargetedBySpells(value);
            break;
        case ATK:
            SetAttack(value);
            break;
        case CANNOT_ATTACK_HEROES:
            SetCannotAttackHeroes(value);
            break;
        case HEROPOWER_DAMAGE:
            SetHeroPowerDamage(value);
            break;
        case HEALTH:
            SetHealth(value);
            break;
        case WINDFURY:
            SetWindfury(value);
            break;
        case TAUNT:
            SetTaunt(value);
            break;
        case CHARGE:
            SetCharge(value);
            break;
        case RUSH:
            SetRush(value);
            break;
        case LIFESTEAL:
            SetLifesteal(value);
            break;
        case CANT_ATTACK:
            SetCantAttack(value);
            break;
        default:
            return;
    }
}

int AuraEffects::GetImmune() const
{
    if (m_type == CardType::WEAPON)
    {
        return m_data[0];
    }

    if (m_type == CardType::HERO)
    {
        return m_data[3];
    }

    return 0;
}

void AuraEffects::SetImmune(int value) const
{
    if (m_type == CardType::WEAPON)
    {
        m_data[0] = value;
    }
    else if (m_type == CardType::HERO)
    {
        m_data[3] = value;
    }
    else
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetImmune() - Invalid card type!");
    }
}

int AuraEffects::GetCantBeTargetedBySpells() const
{
    if (m_type != CardType::HERO && m_type != CardType::MINION)
    {
        return 0;
    }

    return m_data[0];
}

void AuraEffects::SetCantBeTargetedBySpells(int value) const
{
    if (m_type != CardType::HERO && m_type != CardType::MINION)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetCantBeTargetedBySpells() - Invalid card type!");
    }

    m_data[0] = value;
}

int AuraEffects::GetAttack() const
{
    if (m_type == CardType::SPELL)
    {
        return 0;
    }

    return m_data[1];
}

void AuraEffects::SetAttack(int value) const
{
    if (m_type == CardType::SPELL)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetAttack() - Invalid card type!");
    }

    m_data[1] = value;
}

int AuraEffects::GetCannotAttackHeroes() const
{
    if (m_type != CardType::HERO)
    {
        return 0;
    }

    return m_data[2];
}

void AuraEffects::SetCannotAttackHeroes(int value) const
{
    if (m_type != CardType::HERO)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetCannotAttackHeroes() - Invalid card type!");
    }

    m_data[2] = value;
}

int AuraEffects::GetHeroPowerDamage() const
{
    if (m_type != CardType::HERO)
    {
        return 0;
    }

    return m_data[4];
}

void AuraEffects::SetHeroPowerDamage(int value) const
{
    if (m_type != CardType::HERO)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetHeroPowerDamage() - Invalid card type!");
    }

    m_data[4] = value;
}

int AuraEffects::GetHealth() const
{
    if (m_type != CardType::MINION)
    {
        return 0;
    }

    return m_data[2];
}

void AuraEffects::SetHealth(int value) const
{
    if (m_type != CardType::MINION)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetHealth() - Invalid card type!");
    }

    m_data[2] = value;
}

int AuraEffects::GetWindfury() const
{
    if (m_type != CardType::MINION)
    {
        return 0;
    }

    return m_data[3];
}

void AuraEffects::SetWindfury(int value) const
{
    if (m_type != CardType::MINION)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetWindfury() - Invalid card type!");
    }

    m_data[3] = value;
}

int AuraEffects::GetTaunt() const
{
    if (m_type != CardType::MINION)
    {
        return 0;
    }

    return m_data[4];
}

void AuraEffects::SetTaunt(int value) const
{
    if (m_type != CardType::MINION)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetTaunt() - Invalid card type!");
    }

    m_data[4] = value;
}

int AuraEffects::GetCharge() const
{
    if (m_type != CardType::MINION)
    {
        return 0;
    }

    return m_data[5];
}

void AuraEffects::SetCharge(int value) const
{
    if (m_type != CardType::MINION)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetCharge() - Invalid card type!");
    }

    m_data[5] = value;
}

int AuraEffects::GetRush() const
{
    if (m_type != CardType::MINION)
    {
        return 0;
    }

    return m_data[6];
}

void AuraEffects::SetRush(int value) const
{
    if (m_type != CardType::MINION)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetRush() - Invalid card type!");
    }

    m_data[6] = value;
}

int AuraEffects::GetLifesteal() const
{
    if (m_type != CardType::MINION)
    {
        return 0;
    }

    return m_data[7];
}

void AuraEffects::SetLifesteal(int value) const
{
    if (m_type != CardType::MINION)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetLifesteal() - Invalid card type!");
    }

    m_data[7] = value;
}

int AuraEffects::GetCantAttack() const
{
    if (m_type != CardType::MINION)
    {
        return 0;
    }

    return m_data[8];
}

void AuraEffects::SetCantAttack(int value) const
{
    if (m_type != CardType::MINION)
    {
        throw InvalidAuraEffectOperation(
            "AuraEffects::SetCantAttack() - Invalid card type!");
    }

    m_data[8] = value;
}
}  // namespace RosettaStone::PlayMode
