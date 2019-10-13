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
AdaptiveEffect::AdaptiveEffect(SelfCondition* _condition,
                               std::vector<GameTag> tags)
    : Aura(AuraType::ADAPTIVE, std::vector<Effect*>{}),
      m_tags(std::move(tags)),
      m_lastValues(m_tags.size(), 0),
      m_isSwitching(true)
{
    condition = _condition;
}

void AdaptiveEffect::Activate(Entity* owner, bool)
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
    : Aura(prototype, owner)
{
    if (prototype.m_isSwitching)
    {
        condition = prototype.condition;
        m_tags = prototype.m_tags;
        m_lastValues = prototype.m_lastValues;
        m_isSwitching = true;

        return;
    }
}
}  // namespace RosettaStone
