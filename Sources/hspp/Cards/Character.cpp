// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Character.h>

namespace Hearthstonepp
{
Character::Character(Card& card) : Entity(card)
{
    if (!card.id.empty())
    {
#ifndef HEARTHSTONEPP_MACOSX
        m_attack = card.attack.has_value() ? card.attack.value() : 0;
        health = card.health.has_value() ? card.health.value() : 0;
#else
        m_attack = card.attack.value_or(0);
        health = card.health.value_or(0);
#endif
        maxHealth = health;
    }
}

Character::Character(const Character& c) : Entity(c)
{
    m_attack = c.m_attack;
    attackableCount = c.attackableCount;
    health = c.health;
    maxHealth = c.maxHealth;
}

Character& Character::operator=(const Character& c)
{
    if (this == &c)
    {
        return *this;
    }

    m_attack = c.m_attack;
    attackableCount = c.attackableCount;
    health = c.health;
    maxHealth = c.maxHealth;

    return *this;
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

size_t Character::TakeDamage(Character& source, size_t damage)
{
    (void)source;

    if (GetGameTag(GameTag::DIVINE_SHIELD) == 1)
    {
        SetGameTag(GameTag::DIVINE_SHIELD, 0);
        return 0;
    }

    health = (health <= damage) ? 0 : health - damage;

    return damage;
}
}  // namespace Hearthstonepp