// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Enchants/OngoingEnchant.hpp>
#include <Rosetta/Models/Playable.hpp>

#include <utility>

namespace RosettaStone
{
OngoingEnchant::OngoingEnchant(std::vector<IEffect*> effects)
    : Enchant(std::move(effects))
{
    // Do nothing
}

void OngoingEnchant::ActivateTo(Entity* entity, int num1, int num2)
{
    Clone(dynamic_cast<Playable*>(entity));

    Enchant::ActivateTo(entity, num1, num2);
}

void OngoingEnchant::Activate([[maybe_unused]] Playable* owner,
                              [[maybe_unused]] bool cloning)
{
    throw std::logic_error("OngoingEnchant::Activate() - Not implemented!");
}

void OngoingEnchant::Update()
{
    if (!m_toBeUpdated)
    {
        return;
    }

    const std::size_t delta = m_count - m_lastCount;

    for (std::size_t i = 0; i < delta; ++i)
    {
        Enchant::ActivateTo(target);
    }

    m_lastCount = m_count;
    m_toBeUpdated = false;
}

void OngoingEnchant::Remove()
{
    target->ongoingEffect = nullptr;
    EraseIf(target->game->auras, [this](IAura* aura) { return aura == this; });
}

void OngoingEnchant::Clone(Playable* clone)
{
    auto copy = new OngoingEnchant(effects);
    copy->game = clone->game;
    copy->target = clone;
    copy->isOneTurnEffect = isOneTurnEffect;

    clone->ongoingEffect = copy;
    copy->game->auras.emplace_back(copy);
}

std::size_t OngoingEnchant::GetCount() const
{
    return m_count;
}

void OngoingEnchant::SetCount(std::size_t value)
{
    m_count = value;
    m_toBeUpdated = true;
}
}  // namespace RosettaStone
