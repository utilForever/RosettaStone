// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_ENCHANT_HPP
#define ROSETTASTONE_ENCHANT_HPP

#include <Rosetta/Enchants/Effect.hpp>
#include <Rosetta/Enchants/IAura.hpp>

#include <vector>

namespace RosettaStone
{
class Entity;

//!
//! \brief Enchant class.
//!
//! This class stores an enchantment, also known as a buff or debuff. It is a
//! special effect gained by a minion, or in rarer occasions by a weapon.
//!
class Enchant
{
 public:
    //! Default constructor.
    Enchant() = default;

    //! Constructs enchant with given \p gameTag, \p effectOperator and
    //! \p value.
    //! \param gameTag The game tag of the card.
    //! \param effectOperator The effect operator to change card value.
    //! \param value The value to change.
    Enchant(GameTag gameTag, EffectOperator effectOperator, int value);

    //! Constructs enchant with given \p _effect, \p _useScriptTag and
    //! \p _isOneTurnEffect.
    //! \param effect The effect of the card.
    //! \param _useScriptTag A flag to use script tag.
    //! \param _isOneTurnEffect A flag whether this is one-turn effect.
    Enchant(Effect* effect, bool _useScriptTag = false,
            bool _isOneTurnEffect = false);

    //! Constructs enchant with given \p _effects, \p _useScriptTag and
    //! \p _isOneTurnEffect.
    //! \param _effects A list of effect.
    //! \param _useScriptTag A flag to use script tag.
    //! \param _isOneTurnEffect A flag whether this is one-turn effect.
    Enchant(std::vector<Effect*> _effects, bool _useScriptTag = false,
            bool _isOneTurnEffect = false);

    //! Activates enchant to \p entity.
    //! \param entity An entity to which enchant is activated.
    //! \param num1 The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    //! \param num2 The number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    virtual void ActivateTo(Entity* entity, int num1 = 0, int num2 = -1);

    std::vector<Effect*> effects;

    bool useScriptTag = false;
    bool isOneTurnEffect = false;
};

//!
//! \brief OngoingEnchant class.
//!
//! This class is implementation of a kind of enchantment that its effect
//! gradually grows due to a trigger.
//! OngoingEnchant is narrowly used when the source of the trigger and the
//! target of the Enchantment is identical. (e.g. Mana Wyrm)
//!
class OngoingEnchant : public Enchant, IAura
{
 public:
    //! Constructs ongoing enchant with given \p _effects, \p _useScriptTag and
    //! \p _isOneTurnEffect.
    //! \param _effects A list of effect.
    //! \param _useScriptTag A flag to use script tag.
    //! \param _isOneTurnEffect A flag whether this is one-turn effect.
    OngoingEnchant(std::vector<Effect*> _effects, bool _useScriptTag = false,
                   bool _isOneTurnEffect = false);

    //! Updates this effect to apply the effect to recently modified entities.
    void Update() override;

    //! Removes this effect from the game to stop affecting entities.
    void Remove() override;

 private:
    Entity* m_target = nullptr;

    int m_count = 1;
    int m_lastCount = 1;

    bool m_toBeUpdated = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ENCHANT_HPP