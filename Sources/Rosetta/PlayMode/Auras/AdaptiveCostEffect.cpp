// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Auras/AdaptiveCostEffect.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Entity.hpp>

#include <utility>

namespace RosettaStone::PlayMode
{
AdaptiveCostEffect::AdaptiveCostEffect(std::function<int(Playable*)> costFunc,
                                       EffectOperator effectOp,
                                       std::optional<SelfCondition> condition)
    : m_costFunc(std::move(costFunc)),
      m_effectOp(effectOp),
      m_condition(std::move(condition))
{
    // Do nothing
}

void AdaptiveCostEffect::Activate(Playable* owner, bool cloning)
{
    if (!cloning && owner->GetZoneType() != ZoneType::HAND)
    {
        return;
    }

    auto instance = new AdaptiveCostEffect(*this, *owner);

    if (!owner->costManager)
    {
        owner->costManager = new CostManager();
    }

    owner->costManager->ActivateAdaptiveEffect(instance);
    owner->ongoingEffect = instance;
    owner->game->auras.emplace_back(instance);
}

int AdaptiveCostEffect::Apply(int value) const
{
    if (m_costFunc &&
        (m_condition == std::nullopt || m_condition->Evaluate(m_owner)))
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
    m_owner->ongoingEffect = nullptr;

    EraseIf(m_owner->game->auras,
            [this](const IAura* aura) { return aura == this; });

    if (const auto costManager = m_owner->costManager; costManager)
    {
        costManager->DeactivateAdaptiveEffect();
    }
}

void AdaptiveCostEffect::Clone(Playable* clone)
{
    Activate(clone, true);
}

AdaptiveCostEffect::AdaptiveCostEffect(const AdaptiveCostEffect& prototype,
                                       Playable& owner)
    : m_owner(&owner),
      m_costFunc(prototype.m_costFunc),
      m_effectOp(prototype.m_effectOp),
      m_condition(prototype.m_condition)
{
    // Do nothing
}
}  // namespace RosettaStone::PlayMode
