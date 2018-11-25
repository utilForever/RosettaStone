// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Accounts/Player.h>
#include <hspp/Cards/Character.h>
#include <hspp/Commons/Macros.h>

#include <algorithm>

namespace Hearthstonepp
{
Character::Character(Card& card) : Entity(card)
{
    if (!card.id.empty())
    {
#if defined(HEARTHSTONEPP_WINDOWS) || defined(HEARTHSTONEPP_LINUX)
        m_attack = card.attack.has_value() ? card.attack.value() : 0;
        health =
            card.health.has_value() ? static_cast<int>(card.health.value()) : 0;
#elif defined(HEARTHSTONEPP_MACOSX)
        m_attack = card.attack.value_or(0);
        health = static_cast<int>(card.health.value_or(0));
#endif
        maxHealth = health;
    }
}

Character* Character::Clone() const
{
    return new Character(*this);
}

size_t Character::GetAttack() const
{
    return m_attack;
}

void Character::SetAttack(size_t attack)
{
    m_attack = attack;
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

bool Character::IsValidAttackTarget(Player& opponent, Character* target) const
{
    auto validTargets = GetValidAttackTargets(opponent);
    if (std::find(validTargets.begin(), validTargets.end(), target) ==
        validTargets.end())
    {
        return false;
    }

    const Hero* hero = dynamic_cast<Hero*>(target);
    return !(hero != nullptr &&
             hero->GetGameTag(GameTag::CANNOT_ATTACK_HEROES) == 1);
}

std::vector<Character*> Character::GetValidAttackTargets(Player& opponent)
{
    bool isExistTauntInField = false;
    std::vector<Character*> targets;
    std::vector<Character*> targetsHaveTaunt;

    for (auto& minion : opponent.field)
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

    if (opponent.hero->GetGameTag(GameTag::CANNOT_ATTACK_HEROES) == 0 &&
        opponent.hero->GetGameTag(GameTag::IMMUNE) == 0 &&
        opponent.hero->GetGameTag(GameTag::STEALTH) == 0)
    {
        targets.emplace_back(opponent.hero);
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

    return damage;
}
}  // namespace Hearthstonepp