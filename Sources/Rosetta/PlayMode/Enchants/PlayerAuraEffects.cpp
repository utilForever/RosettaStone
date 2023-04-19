// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Enchants/PlayerAuraEffects.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode
{
int PlayerAuraEffects::GetValue(GameTag tag) const
{
    switch (tag)
    {
        case GameTag::TIMEOUT:
            return m_timeOut;
        case GameTag::SPELLPOWER:
            return m_spellPower;
        case GameTag::SPELLPOWER_DOUBLE:
        case GameTag::SPELL_HEALING_DOUBLE:
            return m_spellPowerDouble;
        case GameTag::HEALING_DOES_DAMAGE:
            return m_healingDoesDamage;
        case GameTag::CAN_TARGET_MINION_BY_HERO_POWER:
            return m_canTargetMinionByHeroPower;
        case GameTag::CANT_BE_FROZEN:
            return m_cantBeFrozen;
        case GameTag::RESOURCES_USED:
            return m_resourcesUsed;
        case GameTag::EXTRA_BATTLECRIES_BASE:
            return m_extraBattlecry;
        case GameTag::EXTRA_MINION_DEATHRATTLES_BASE:
            return m_extraMinionDeathrattle;
        case GameTag::EXTRA_CAST_SPELL:
            return m_extraCastSpell;
        case GameTag::EXTRA_TRIGGER_SECRET:
            return m_extraTriggerSecret;
        case GameTag::MEGA_WINDFURY:
            return m_megaWindfury;
        case GameTag::CHOOSE_BOTH:
            return m_chooseBoth;
        case GameTag::HEROPOWER_DAMAGE:
            return m_heroPowerDamage;
        case GameTag::TAKE_DAMAGE_DOUBLE:
            return m_takeDamageDouble;
        case GameTag::TAKE_ONE_DAMAGE_AT_A_TIME:
            return m_takeOneDamageAtTime;
        default:
            throw std::invalid_argument(
                "PlayerAuraEffects::GetValue() - Invalid game tag!");
    }
}

void PlayerAuraEffects::SetValue(GameTag tag, int value)
{
    switch (tag)
    {
        case GameTag::TIMEOUT:
            m_timeOut = value;
            break;
        case GameTag::SPELLPOWER:
            m_spellPower = value;
            break;
        case GameTag::SPELLPOWER_DOUBLE:
        case GameTag::SPELL_HEALING_DOUBLE:
            m_spellPowerDouble = value;
            break;
        case GameTag::HEALING_DOES_DAMAGE:
            m_healingDoesDamage = value;
            break;
        case GameTag::CAN_TARGET_MINION_BY_HERO_POWER:
            m_canTargetMinionByHeroPower = value;
            break;
        case GameTag::CANT_BE_FROZEN:
            m_cantBeFrozen = value;
            break;
        case GameTag::RESOURCES_USED:
            m_resourcesUsed = value;
            break;
        case GameTag::EXTRA_BATTLECRIES_BASE:
            m_extraBattlecry = value;
            break;
        case GameTag::EXTRA_MINION_DEATHRATTLES_BASE:
            m_extraMinionDeathrattle = value;
            break;
        case GameTag::EXTRA_CAST_SPELL:
            m_extraCastSpell = value;
            break;
        case GameTag::EXTRA_TRIGGER_SECRET:
            m_extraTriggerSecret = value;
            break;
        case GameTag::MEGA_WINDFURY:
            m_megaWindfury = value;
            break;
        case GameTag::CHOOSE_BOTH:
            m_chooseBoth = value;
            break;
        case GameTag::HEROPOWER_DAMAGE:
            m_heroPowerDamage = value;
            break;
        case GameTag::TAKE_DAMAGE_DOUBLE:
            m_takeDamageDouble = value;
            break;
        case GameTag::TAKE_ONE_DAMAGE_AT_A_TIME:
            m_takeOneDamageAtTime = value;
            break;
        default:
            throw std::invalid_argument(
                "PlayerAuraEffects::SetValue() - Invalid game tag!");
    }
}
}  // namespace RosettaStone::PlayMode
