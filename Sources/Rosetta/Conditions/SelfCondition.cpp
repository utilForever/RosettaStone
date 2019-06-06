// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Games/Game.hpp>
#include <utility>

namespace RosettaStone
{
SelfCondition::SelfCondition(std::function<bool(Entity*)> func)
    : m_func(std::move(func))
{
    // Do nothing
}

SelfCondition SelfCondition::IsDead()
{
    return SelfCondition(
        [=](Entity* entity) -> bool { return entity->isDestroyed; });
}

SelfCondition SelfCondition::IsUndamaged()
{
    return SelfCondition([=](Entity* entity) -> bool {
        const auto character = dynamic_cast<Character*>(entity);
        if (!character)
        {
            return false;
        }

        return character->GetDamage() == 0;
    });
}

SelfCondition SelfCondition::IsWeaponEquipped()
{
    return SelfCondition([=](Entity* entity) -> bool {
        return entity->owner->GetHero()->HasWeapon();
    });
}

SelfCondition SelfCondition::IsRace(Race race)
{
    return SelfCondition(
        [=](Entity* entity) -> bool { return entity->card.GetRace() == race; });
}

SelfCondition SelfCondition::IsControllingRace(Race race)
{
    return SelfCondition([=](Entity* entity) -> bool {
        for (auto& minion : entity->owner->GetFieldZone().GetAll())
        {
            if (minion->card.GetRace() == race)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsMinion()
{
    return SelfCondition([=](Entity* entity) -> bool {
        return dynamic_cast<Minion*>(entity) != nullptr;
    });
}

SelfCondition SelfCondition::HasMinionInHand()
{
    return SelfCondition([=](Entity* entity) -> bool {
        for (auto& card : entity->owner->GetHandZone().GetAll())
        {
            if (dynamic_cast<Minion*>(card) != nullptr)
            {
                return true;
            }
        }

        return false;
    });
}

SelfCondition SelfCondition::IsTagValue(GameTag tag, int value,
                                        RelaSign relaSign)
{
    return SelfCondition([=](Entity* entity) -> bool {
        return (relaSign == RelaSign::EQ && entity->GetGameTag(tag) == value) ||
               (relaSign == RelaSign::GEQ &&
                entity->GetGameTag(tag) >= value) ||
               (relaSign == RelaSign::LEQ && entity->GetGameTag(tag) <= value);
    });
}

bool SelfCondition::Evaluate(Entity* entity) const
{
    return m_func(entity);
}
}  // namespace RosettaStone
