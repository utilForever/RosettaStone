// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/Enchantment.hpp>

#include <algorithm>

namespace RosettaStone
{
Enchantment::Enchantment(Player& _owner, Card& _card, Entity* target)
    : Entity(_owner, _card), m_target(target)
{
    // Do nothing
}

Enchantment* Enchantment::GetInstance(Player& player, Card& card, Entity* target)
{
    Enchantment* instance = new Enchantment(player, card, target);

    target->appliedEnchantments.emplace_back(instance);

    return instance;
}

Entity* Enchantment::GetTarget() const
{
    return m_target;
}

void Enchantment::Remove()
{
    if (activatedTrigger != nullptr)
    {
        activatedTrigger->Remove();
    }

    auto iter = std::find(m_target->appliedEnchantments.begin(),
                          m_target->appliedEnchantments.end(), this);
    if (iter != m_target->appliedEnchantments.end())
    {
        m_target->appliedEnchantments.erase(iter);
    }
}
}  // namespace RosettaStone
