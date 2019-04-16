// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Minion.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
Minion::Minion(Player& _owner, Card& _card) : Character(_owner, _card)
{
    // Do nothing
}

void Minion::Reset()
{
    Entity::Reset();

    if (onGoingEffect != nullptr)
    {
        onGoingEffect->Remove();
    }

    if (isDestroyed)
    {
        auto iter = m_owner->GetGame()->deadMinions.find(orderOfPlay);
        if (iter != m_owner->GetGame()->deadMinions.end())
        {
            m_owner->GetGame()->deadMinions.erase(iter);
        }

        isDestroyed = false;
    }
}

void Minion::Destroy()
{
    Entity::Destroy();

    GetOwner().GetGame()->deadMinions.emplace(orderOfPlay, this);
}
}  // namespace RosettaStone
