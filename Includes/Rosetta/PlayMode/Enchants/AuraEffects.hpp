// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_AURA_EFFECTS_HPP
#define ROSETTASTONE_PLAYMODE_AURA_EFFECTS_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>

namespace RosettaStone::PlayMode
{
class Entity;

constexpr int AURA_EFFECT_CARD_SIZE = 0;
constexpr int AURA_EFFECT_WEAPON_SIZE = AURA_EFFECT_CARD_SIZE + 2;
constexpr int AURA_EFFECT_CHARACTER_SIZE = AURA_EFFECT_CARD_SIZE + 2;
constexpr int AURA_EFFECT_HERO_SIZE = AURA_EFFECT_CHARACTER_SIZE + 3;
constexpr int AURA_EFFECT_MINION_SIZE = AURA_EFFECT_CHARACTER_SIZE + 7;

//!
//! \brief AuraEffects class.
//!
//! This class is a simple container for saving tag value perturbations from
//! external auras. Call indexer to get value for a particular tag.
//!
class AuraEffects
{
 public:
    //! Constructs aura effects with given \p type.
    //! \param type The type of the card.
    explicit AuraEffects(CardType type);

    //! Destructor.
    ~AuraEffects();

    //! Deleted copy constructor.
    AuraEffects(const AuraEffects&) = delete;

    //! Deleted move constructor.
    AuraEffects(AuraEffects&&) noexcept = delete;

    //! Deleted copy assignment operator.
    AuraEffects& operator=(const AuraEffects&) = delete;

    //! Deleted move assignment operator.
    AuraEffects& operator=(AuraEffects&&) noexcept = delete;

    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    int GetGameTag(GameTag tag) const;

    //! Sets game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    void SetGameTag(GameTag tag, int value) const;

    //! Returns the value of GameTag::IMMUNE.
    //! \return The value of GameTag::IMMUNE.
    int GetImmune() const;

    //! Sets the value of GameTag::IMMUNE.
    //! \param value The value of GameTag::IMMUNE to set.
    void SetImmune(int value) const;

    //! Returns the value of GameTag::CANT_BE_TARGETED_BY_SPELLS and
    //! GameTag::CANT_BE_TARGETED_BY_HERO_POWERS.
    //! \return The value of GameTag::CANT_BE_TARGETED_BY_SPELLS and
    //! GameTag::CANT_BE_TARGETED_BY_HERO_POWERS.
    int GetCantBeTargetedBySpells() const;

    //! Sets the value of GameTag::CANT_BE_TARGETED_BY_SPELLS and
    //! GameTag::CANT_BE_TARGETED_BY_HERO_POWERS.
    //! \param value The value of GameTag::CANT_BE_TARGETED_BY_SPELLS and
    //! GameTag::CANT_BE_TARGETED_BY_HERO_POWERS to set.
    void SetCantBeTargetedBySpells(int value) const;

    //! Returns the value of GameTag::ATK.
    //! \return The value of GameTag::ATK.
    int GetAttack() const;

    //! Sets the value of GameTag::ATK.
    //! \param value The value of GameTag::ATK to set.
    void SetAttack(int value) const;

    //! Returns the value of GameTag::CANNOT_ATTACK_HEROES.
    //! \return The value of GameTag::CANNOT_ATTACK_HEROES.
    int GetCannotAttackHeroes() const;

    //! Sets the value of GameTag::CANNOT_ATTACK_HEROES.
    //! \param value The value of GameTag::CANNOT_ATTACK_HEROES to set.
    void SetCannotAttackHeroes(int value) const;

    //! Returns the value of GameTag::HEROPOWER_DAMAGE.
    //! \return The value of GameTag::HEROPOWER_DAMAGE.
    int GetHeroPowerDamage() const;

    //! Sets the value of GameTag::HEROPOWER_DAMAGE.
    //! \param value The value of GameTag::HEROPOWER_DAMAGE to set.
    void SetHeroPowerDamage(int value) const;

    //! Returns the value of GameTag::HEALTH.
    //! \return The value of GameTag::HEALTH.
    int GetHealth() const;

    //! Sets the value of GameTag::HEALTH.
    //! \param value The value of GameTag::HEALTH to set.
    void SetHealth(int value) const;

    //! Returns the value of GameTag::WINDFURY.
    //! \return The value of GameTag::WINDFURY.
    int GetWindfury() const;

    //! Sets the value of GameTag::WINDFURY.
    //! \param value The value of GameTag::WINDFURY to set.
    void SetWindfury(int value) const;

    //! Returns the value of GameTag::TAUNT.
    //! \return The value of GameTag::TAUNT.
    int GetTaunt() const;

    //! Sets the value of GameTag::TAUNT.
    //! \param value The value of GameTag::TAUNT to set.
    void SetTaunt(int value) const;

    //! Returns the value of GameTag::CHARGE.
    //! \return The value of GameTag::CHARGE.
    int GetCharge() const;

    //! Sets the value of GameTag::CHARGE.
    //! \param value The value of GameTag::CHARGE to set.
    void SetCharge(int value) const;

    //! Returns the value of GameTag::RUSH.
    //! \return The value of GameTag::RUSH.
    int GetRush() const;

    //! Sets the value of GameTag::RUSH.
    //! \param value The value of GameTag::RUSH to set.
    void SetRush(int value) const;

    //! Returns the value of GameTag::LIFESTEAL.
    //! \return The value of GameTag::LIFESTEAL.
    int GetLifesteal() const;

    //! Sets the value of GameTag::LIFESTEAL.
    //! \param value The value of GameTag::LIFESTEAL to set.
    void SetLifesteal(int value) const;

    //! Returns the value of GameTag::CANT_ATTACK.
    //! \return The value of GameTag::CANT_ATTACK.
    int GetCantAttack() const;

    //! Sets the value of GameTag::CANT_ATTACK.
    //! \param value The value of GameTag::CANT_ATTACK to set.
    void SetCantAttack(int value) const;

 private:
    CardType m_type = CardType::INVALID;

    // Indices:
    // Cards
    // ...
    // Weapon
    // 0 : IMMUNE
    // 1 : ATK
    // Character
    // 0 : CANT_BE_TARGETED_BY_SPELLS / CANT_BE_TARGETED_BY_HERO_POWERS
    // 1 : ATK
    // Hero
    // 2 : CANNOT_ATTACK_HEROES
    // 3 : IMMUNE
    // 4 : HEROPOWER_DAMAGE
    // Minion
    // 2 : HEALTH
    // 3 : WINDFURY
    // 4 : TAUNT
    // 5 : CHARGE
    // 6 : RUSH
    // 7 : LIFESTEAL
    // 8 : CANT_ATTACK
    int* m_data = nullptr;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_AURA_EFFECTS_HPP
