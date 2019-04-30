// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Character.hpp>
#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Models/Player.hpp>

#include <algorithm>

namespace RosettaStone
{
Character::Character(Player& _owner, Card& _card) : Entity(_owner, _card)
{
    // Do nothing
}

int Character::GetAttack() const
{
    return GetGameTag(GameTag::ATK);
}

void Character::SetAttack(int attack)
{
    SetGameTag(GameTag::ATK, attack);
}

int Character::GetDamage() const
{
    return GetGameTag(GameTag::DAMAGE);
}

void Character::SetDamage(int damage)
{
    if (GetGameTag(GameTag::HEALTH) <= damage)
    {
        Destroy();
    }

    SetGameTag(GameTag::DAMAGE, damage < 0 ? 0 : damage);
}

int Character::GetHealth() const
{
    return GetGameTag(GameTag::HEALTH) - GetGameTag(GameTag::DAMAGE);
}

void Character::SetHealth(int health)
{
    if (health == 0)
    {
        Destroy();
    }

    SetGameTag(GameTag::HEALTH, health);
    SetGameTag(GameTag::DAMAGE, 0);
}

int Character::GetBaseHealth() const
{
    return GetGameTag(GameTag::HEALTH);
}

void Character::SetBaseHealth(int baseHealth)
{
    SetGameTag(GameTag::HEALTH, baseHealth);
}

int Character::GetSpellPower()
{
    return GetGameTag(GameTag::SPELLPOWER);
}

void Character::SetSpellPower(int spellPower)
{
    SetGameTag(GameTag::SPELLPOWER, spellPower);
}

int Character::GetNumAttacksThisTurn() const
{
    return GetGameTag(GameTag::NUM_ATTACKS_THIS_TURN);
}

void Character::SetNumAttacksThisTurn(int amount)
{
    SetGameTag(GameTag::NUM_ATTACKS_THIS_TURN, amount);
}

bool Character::CanAttack()
{
    // If the value of attack is 0, returns false
    if (GetAttack() == 0)
    {
        return false;
    }

    // If the character is frozen, returns false
    if (GetGameTag(GameTag::FROZEN) == 1)
    {
        return false;
    }

    // If the character is exhausted, returns false
    if (GetExhausted())
    {
        return false;
    }

    //! If the character can't attack, returns false
    if (GetGameTag(GameTag::CANT_ATTACK) == 1)
    {
        return false;
    }

    return true;
}

bool Character::IsValidCombatTarget(Player& opponent, Character* target) const
{
    auto targets = GetValidCombatTargets(opponent);
    if (std::find(targets.begin(), targets.end(), target) == targets.end())
    {
        return false;
    }

    const Hero* hero = dynamic_cast<Hero*>(target);
    return !(hero != nullptr &&
             hero->GetGameTag(GameTag::CANNOT_ATTACK_HEROES) == 1);
}

std::vector<Character*> Character::GetValidCombatTargets(Player& opponent) const
{
    bool isExistTauntInField = false;
    std::vector<Character*> targets;
    std::vector<Character*> targetsHaveTaunt;

    for (auto& minion : opponent.GetField().GetAllMinions())
    {
        if (minion->GetGameTag(GameTag::STEALTH) == 0)
        {
            if (minion->GetGameTag(GameTag::TAUNT) == 1)
            {
                isExistTauntInField = true;
                targetsHaveTaunt.emplace_back(minion);
                continue;
            }

            if (!isExistTauntInField)
            {
                targets.emplace_back(minion);
            }
        }
    }

    if (isExistTauntInField)
    {
        return targetsHaveTaunt;
    }

    if (GetGameTag(GameTag::CANNOT_ATTACK_HEROES) == 0 &&
        opponent.GetHero()->GetGameTag(GameTag::IMMUNE) == 0 &&
        opponent.GetHero()->GetGameTag(GameTag::STEALTH) == 0)
    {
        targets.emplace_back(opponent.GetHero());
    }

    return targets;
}

int Character::TakeDamage(Entity& source, int damage)
{
    const auto hero = dynamic_cast<Hero*>(this);
    const auto minion = dynamic_cast<Minion*>(this);

    const bool isFatigue = (hero != nullptr) && (this == &source);
    if (isFatigue)
    {
        hero->fatigue = damage;
    }

    if (minion != nullptr && GetGameTag(GameTag::DIVINE_SHIELD) == 1)
    {
        SetGameTag(GameTag::DIVINE_SHIELD, 0);
        return 0;
    }

    const int armor = (hero != nullptr) ? hero->GetArmor() : 0;
    const int amount =
        (hero == nullptr) ? damage : armor < damage ? damage - armor : 0;

    if (GetGameTag(GameTag::IMMUNE) == 1)
    {
        return 0;
    }

    if (armor > 0)
    {
        hero->SetArmor(armor < damage ? 0 : armor - damage);
    }

    SetDamage(GetDamage() + amount);

    // Process damage triggers
    owner->GetGame()->triggerManager.OnTakeDamageTrigger(owner, this);
    owner->GetGame()->ProcessTasks();

    return amount;
}

void Character::TakeFullHeal(Entity& source)
{
    TakeHeal(source, GetDamage());
}

void Character::TakeHeal(Entity& source, int heal)
{
    (void)source;

    if (GetDamage() == 0)
    {
        return;
    }

    int amount = GetDamage() > heal ? heal : GetDamage();
    SetDamage(GetDamage() - amount);

    owner->GetGame()->triggerManager.OnHealTrigger(nullptr, this);
    owner->GetGame()->ProcessTasks();
}
}  // namespace RosettaStone
