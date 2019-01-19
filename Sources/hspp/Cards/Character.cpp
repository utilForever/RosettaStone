// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Accounts/Player.hpp>
#include <hspp/Cards/Character.hpp>
#include <hspp/Cards/Minion.hpp>
#include <hspp/Managers/GameAgent.hpp>

#include <algorithm>

namespace Hearthstonepp
{
Character::Character(GameAgent* gameAgent, Card& card) : Entity(gameAgent, card)
{
    if (!card.id.empty())
    {
        m_attack = card.attack ? *card.attack : 0;
        health = card.health ? static_cast<int>(*card.health) : 0;
        maxHealth = health;
    }
}

size_t Character::GetAttack() const
{
    return m_attack;
}

void Character::SetAttack(size_t attack)
{
    m_attack = attack;
}

void Character::Destroy()
{
    // Do nothing
}

bool Character::CanAttack() const
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

    // If attack count is 0, returns false
    if (attackableCount == 0)
    {
        return false;
    }

    return true;
}

Player& Character::GetOwner() const
{
    return *m_owner;
}

void Character::SetOwner(Player& owner)
{
    m_owner = &owner;
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

std::vector<Character*> Character::GetValidCombatTargets(Player& opponent)
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

    if (opponent.GetHero()->GetGameTag(GameTag::CANNOT_ATTACK_HEROES) == 0 &&
        opponent.GetHero()->GetGameTag(GameTag::IMMUNE) == 0 &&
        opponent.GetHero()->GetGameTag(GameTag::STEALTH) == 0)
    {
        targets.emplace_back(opponent.GetHero());
    }

    return targets;
}

size_t Character::TakeDamage(Character& source, size_t damage)
{
    (void)source;

    if (GetGameTag(GameTag::DIVINE_SHIELD) == 1)
    {
        SetGameTag(GameTag::DIVINE_SHIELD, 0);
        return 0;
    }

    if (GetGameTag(GameTag::IMMUNE) == 1)
    {
        return 0;
    }

    health -= static_cast<int>(damage);

    if (health <= 0)
    {
        const auto minion = dynamic_cast<Minion*>(this);
        if (minion != nullptr)
        {
            GetGameAgent()->KillMinion(*minion);
        }
    }

    return damage;
}

void Character::TakeHeal(Character& source, int heal)
{
    (void)source;

    health = std::min(health + heal, maxHealth);
}
}  // namespace Hearthstonepp