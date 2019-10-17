// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Auras/AdaptiveEffect.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
AdaptiveEffect::AdaptiveEffect(SelfCondition* condition, GameTag tag)
    : m_condition(condition),
      m_tag(tag),
      m_operator(EffectOperator::SET),
      m_isSwitching(true)
{
    // Do nothing
}

void AdaptiveEffect::Activate(Entity* owner, [[maybe_unused]] bool cloning)
{
    auto instance = new AdaptiveEffect(*this, *owner);

    owner->owner->GetGame()->auras.emplace_back(instance);
    owner->onGoingEffect = instance;
}

void AdaptiveEffect::Update()
{
    if (m_isSwitching)
    {
        for (std::size_t i = 0; i < m_tags.size(); ++i)
        {
            const int val = condition->Evaluate(m_owner) ? 1 : 0;
            if (m_lastValues[i] == val)
            {
                continue;
            }

            Effect(m_tags[i], EffectOperator::SET, val).Apply(m_owner);
            m_lastValues[i] = val;
        }
    }
}

void AdaptiveEffect::Remove()
{
    m_owner->onGoingEffect = nullptr;
    auto& auras = m_owner->owner->GetGame()->auras;
    const auto iter = std::find(auras.begin(), auras.end(), this);
    auras.erase(iter);
}

void AdaptiveEffect::Clone(Entity* clone)
{
    Activate(clone);
}

AdaptiveEffect::AdaptiveEffect(AdaptiveEffect& prototype, Entity& owner)
{
    m_owner = &owner;

    m_condition = prototype.m_condition;
    m_valueFunc = prototype.m_valueFunc;

    m_tag = prototype.m_tag;
    m_operator = prototype.m_operator;

    m_lastValue = prototype.m_lastValue;
    m_turnOn = prototype.m_turnOn;
    m_isSwitching = prototype.m_isSwitching;
}
}  // namespace RosettaStone
