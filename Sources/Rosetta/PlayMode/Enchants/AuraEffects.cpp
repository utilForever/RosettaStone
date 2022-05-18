// This code is based on Sabberstone project.
// Copyright (c) 2017-2021 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2021 Chris Ohk

#include <Rosetta/PlayMode/Enchants/AuraEffects.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode
{
AuraEffects::AuraEffects(CardType type) : m_type(type)
{
    switch (type)
    {
        case CardType::HERO:
            m_data = new int[AURA_EFFECT_HERO_SIZE]();
            break;
        case CardType::MINION:
            m_data = new int[AURA_EFFECT_MINION_SIZE]();
            break;
        case CardType::WEAPON:
            m_data = new int[AURA_EFFECT_WEAPON_SIZE]();
            break;
        case CardType::SPELL:
            m_data = new int[AURA_EFFECT_CARD_SIZE]();
            break;
        default:
            throw std::invalid_argument(
                "AuraEffects::AuraEffects() - Invalid card type!");
    }
}

AuraEffects::~AuraEffects()
{
    delete[] m_data;
}

int AuraEffects::GetGameTag(GameTag tag) const
{
    switch (tag)
    {
        case GameTag::IMMUNE:
            return GetImmune();
        case GameTag::CANT_BE_TARGETED_BY_SPELLS:
        case GameTag::CANT_BE_TARGETED_BY_HERO_POWERS:
            return GetCantBeTargetedBySpells();
        case GameTag::ATK:
            return GetAttack();
        case GameTag::CANNOT_ATTACK_HEROES:
            return GetCannotAttackHeroes();
        case GameTag::HEROPOWER_DAMAGE:
            return GetHeroPowerDamage();
        case GameTag::HEALTH:
            return GetHealth();
        case GameTag::WINDFURY:
            return GetWindfury();
        case GameTag::TAUNT:
            return GetTaunt();
        case GameTag::CHARGE:
            return GetCharge();
        case GameTag::LIFESTEAL:
            return GetLifesteal();
        case GameTag::CANT_ATTACK:
            return GetCantAttack();
        default:
            return 0;
    }
}

void AuraEffects::SetGameTag(GameTag tag, int value)
{
    switch (tag)
    {
        case GameTag::IMMUNE:
            SetImmune(value);
            break;
        case GameTag::CANT_BE_TARGETED_BY_SPELLS:
        case GameTag::CANT_BE_TARGETED_BY_HERO_POWERS:
            SetCantBeTargetedBySpells(value);
            break;
        case GameTag::ATK:
            SetAttack(value);
            break;
        case GameTag::CANNOT_ATTACK_HEROES:
            SetCannotAttackHeroes(value);
            break;
        case GameTag::HEROPOWER_DAMAGE:
            SetHeroPowerDamage(value);
            break;
        case GameTag::HEALTH:
            SetHealth(value);
            break;
        case GameTag::WINDFURY:
            SetWindfury(value);
            break;
        case GameTag::TAUNT:
            SetTaunt(value);
            break;
        case GameTag::CHARGE:
            SetCharge(value);
            break;
        case GameTag::LIFESTEAL:
            SetLifesteal(value);
            break;
        case GameTag::CANT_ATTACK:
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

void AuraEffects::SetImmune(int value)
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
        throw std::runtime_error(
            "AuraEffects::SetImmune() - Invalid card type!");
    }
}

int AuraEffects::GetCantBeTargetedBySpells() const
{
    return m_data[0];
}

void AuraEffects::SetCantBeTargetedBySpells(int value)
{
    m_data[0] = value;
}

int AuraEffects::GetAttack() const
{
    return m_data[1];
}

void AuraEffects::SetAttack(int value)
{
    m_data[1] = value;
}

int AuraEffects::GetCannotAttackHeroes() const
{
    return m_data[2];
}

void AuraEffects::SetCannotAttackHeroes(int value)
{
    m_data[2] = value;
}

int AuraEffects::GetHeroPowerDamage() const
{
    return m_data[4];
}

void AuraEffects::SetHeroPowerDamage(int value)
{
    m_data[4] = value;
}

int AuraEffects::GetHealth() const
{
    return m_data[2];
}

void AuraEffects::SetHealth(int value)
{
    m_data[2] = value;
}

int AuraEffects::GetWindfury() const
{
    return m_data[3];
}

void AuraEffects::SetWindfury(int value)
{
    m_data[3] = value;
}

int AuraEffects::GetTaunt() const
{
    return m_data[4];
}

void AuraEffects::SetTaunt(int value)
{
    m_data[4] = value;
}

int AuraEffects::GetCharge() const
{
    return m_data[5];
}

void AuraEffects::SetCharge(int value)
{
    m_data[5] = value;
}

int AuraEffects::GetRush() const
{
    return m_data[6];
}

void AuraEffects::SetRush(int value)
{
    m_data[6] = value;
}

int AuraEffects::GetLifesteal() const
{
    return m_data[7];
}

void AuraEffects::SetLifesteal(int value)
{
    m_data[7] = value;
}

int AuraEffects::GetCantAttack() const
{
    return m_data[8];
}

void AuraEffects::SetCantAttack(int value)
{
    m_data[8] = value;
}
}  // namespace RosettaStone::PlayMode
