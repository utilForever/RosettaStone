// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/AdaptiveCostEffect.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Player.hpp>

#include <utility>

namespace RosettaStone
{
AdaptiveCostEffect::AdaptiveCostEffect(std::function<int(Entity*)> costFunc,
                                       EffectOperator effectOp)
    : Aura(AuraType::ADAPTIVE, std::vector<Effect*>{}),
      m_costFunc(std::move(costFunc)),
      m_effectOp(effectOp)
{
    // Do nothing
}

void AdaptiveCostEffect::Activate(Entity* owner, bool cloning)
{
    if (!cloning && owner->GetZoneType() != ZoneType::HAND)
    {
        return;
    }

    auto instance = new AdaptiveCostEffect(*this, *owner);

    if (owner->costManager == nullptr)
    {
        owner->costManager = new CostManager();
    }

    owner->costManager->ActivateAdaptiveEffect(instance);
    owner->onGoingEffect = instance;
    owner->owner->GetGame()->auras.emplace_back(instance);
}

int AdaptiveCostEffect::Apply(int value) const
{
    if (m_costFunc != nullptr)
    {
        if (m_effectOp == EffectOperator::ADD)
        {
            return value + m_costFunc(m_owner);
        }

        if (m_effectOp == EffectOperator::SUB)
        {
            return value - m_costFunc(m_owner);
        }

        if (m_effectOp == EffectOperator::MUL)
        {
            return value * m_costFunc(m_owner);
        }

        if (m_effectOp == EffectOperator::SET)
        {
            return m_costFunc(m_owner);
        }
    }

    return value;
}

void AdaptiveCostEffect::Update()
{
    m_owner->costManager->UpdateAdaptiveEffect();
}

void AdaptiveCostEffect::Remove()
{
    m_owner->onGoingEffect = nullptr;

    auto& auras = m_owner->owner->GetGame()->auras;
    const auto iter = std::find(auras.begin(), auras.end(), this);
    auras.erase(iter);

    m_owner->costManager->DeactivateAdaptiveEffect();
}

void AdaptiveCostEffect::Clone(Entity* clone)
{
    Activate(clone, true);
}

AdaptiveCostEffect::AdaptiveCostEffect(AdaptiveCostEffect& prototype,
                                       Entity& owner)
    : Aura(prototype, owner)
{
    m_costFunc = prototype.m_costFunc;
    m_effectOp = prototype.m_effectOp;
}
}  // namespace RosettaStone
