// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_ATK_HPP
#define ROSETTASTONE_PLAYMODE_ATK_HPP

#include <Rosetta/PlayMode/Enchants/Attrs/SelfContainedIntAttr.hpp>

#include <memory>

namespace RosettaStone::PlayMode
{
//!
//! \brief Atk class.
//!
//! This class is an attribute for attack and inherits from SelfContainedIntAttr
//! class. It uses CRTP(Curiously Recurring Template Pattern) technique.
//!
class Atk : public SelfContainedIntAttr<Atk, Entity>
{
 public:
    //! Generates new effect for attack attribute.
    //! \param effectOp The effect operator of the effect.
    //! \param value The value of the effect.
    //! \return The effect that is dynamically allocated.
    static std::shared_ptr<IEffect> Effect(EffectOperator effectOp, int value)
    {
        return SelfContainedIntAttr::Effect(effectOp, value);
    }

    //! Applies the effect that affects the attribute.
    //! \param entity The entity to apply the effect.
    //! \param effectOp The effect operator to change the attribute.
    //! \param value The value to change the attribute.
    void Apply(Entity* entity, EffectOperator effectOp, int value) override
    {
        if (effectOp == EffectOperator::SET)
        {
            auto& effects = entity->game->oneTurnEffects;

            for (int i = static_cast<int>(effects.size()) - 1; i >= 0; --i)
            {
                Entity* ent = effects[i].first;
                IEffect* eff = effects[i].second;

                if (ent != entity ||
                    dynamic_cast<GenericEffect<Playable, Atk>*>(eff) == nullptr)
                {
                    continue;
                }

                effects.erase(effects.begin() + i);
            }
        }

        if (const auto character = dynamic_cast<Character*>(entity); character)
        {
            SelfContainedIntAttr::Apply(character, effectOp, value);
        }
        else
        {
            const auto effect =
                new PlayMode::Effect(GameTag::ATK, effectOp, value);
            effect->ApplyTo(entity);
            delete effect;
        }
    }

 protected:
    //! Returns the value of the attribute of the entity.
    //! \param entity The entity to get the value of the attribute.
    //! \return The value of the attribute of the entity.
    int GetValue(Entity* entity) override
    {
        if (const auto hero = dynamic_cast<Hero*>(entity); hero)
        {
            if (hero->HasWeapon())
            {
                return hero->GetAttack() - hero->weapon->GetAttack();
            }

            return hero->GetAttack();
        }

        const auto minion = dynamic_cast<Minion*>(entity);
        return minion->GetAttack();
    }

    //! Sets the value of the attribute of the entity.
    //! \param entity The entity to set the value of the attribute.
    //! \param value The value of the attribute of the entity.
    void SetValue(Entity* entity, int value) override
    {
        auto character = dynamic_cast<Character*>(entity);
        character->SetAttack(value);
    }

    //! Returns the value the attribute that is affected by the aura effect.
    //! \param auraEffects The aura effects that affects the attribute.
    //! \return The value the attribute that is affected by the aura effect.
    int GetAuraValue(AuraEffects* auraEffects) override
    {
        return auraEffects->GetAttack();
    }

    //! Sets the value the attribute that is affected by the aura effect.
    //! \param auraEffects The aura effects that affects the attribute.
    //! \param value The value the attribute that is affected by
    //! the aura effect.
    void SetAuraValue(AuraEffects* auraEffects, int value) override
    {
        auraEffects->SetAttack(value);
    }
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ATK_HPP
