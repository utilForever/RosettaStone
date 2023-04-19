// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Enchants/OngoingEnchant.hpp>
#include <Rosetta/PlayMode/Models/Playable.hpp>

#include <stdexcept>
#include <utility>

namespace RosettaStone::PlayMode
{
OngoingEnchant::OngoingEnchant(std::vector<std::shared_ptr<IEffect>> _effects)
    : Enchant(std::move(_effects))
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
    EraseIf(target->game->auras,
            [this](const IAura* aura) { return aura == this; });
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

int OngoingEnchant::GetCount() const
{
    return m_count;
}

void OngoingEnchant::SetCount(int value)
{
    m_count = value;
    m_toBeUpdated = true;
}
}  // namespace RosettaStone::PlayMode
