// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_ENCHANT_HPP
#define ROSETTASTONE_PLAYMODE_ENCHANT_HPP

#include <Rosetta/PlayMode/Enchants/Effect.hpp>

#include <memory>
#include <vector>

namespace RosettaStone::PlayMode
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

    //! Default destructor.
    virtual ~Enchant() = default;

    //! Constructs enchant with given \p gameTag, \p effectOperator and
    //! \p value.
    //! \param gameTag The game tag of the card.
    //! \param effectOperator The effect operator to change card value.
    //! \param value The value to change.
    explicit Enchant(GameTag gameTag, EffectOperator effectOperator, int value);

    //! Constructs enchant with given \p _effect, \p _useScriptTag and
    //! \p _isOneTurnEffect.
    //! \param effect The effect of the card.
    //! \param _useScriptTag A flag to use script tag.
    //! \param _isOneTurnEffect A flag whether this is one-turn effect.
    explicit Enchant(const std::shared_ptr<IEffect>& effect,
                     bool _useScriptTag = false, bool _isOneTurnEffect = false);

    //! Constructs enchant with given \p _effects, \p _useScriptTag and
    //! \p _isOneTurnEffect.
    //! \param _effects A list of effect.
    //! \param _useScriptTag A flag to use script tag.
    //! \param _isOneTurnEffect A flag whether this is one-turn effect.
    explicit Enchant(std::vector<std::shared_ptr<IEffect>> _effects,
                     bool _useScriptTag = false, bool _isOneTurnEffect = false);

    //! Activates enchant to \p entity.
    //! \param entity An entity to which enchant is activated.
    //! \param num1 The number of GameTag::TAG_SCRIPT_DATA_NUM_1.
    //! \param num2 The number of GameTag::TAG_SCRIPT_DATA_NUM_2.
    virtual void ActivateTo(Entity* entity, int num1 = 0, int num2 = -1);

    void RemoveEffect(Entity* target) const;

    void RemoveEffect(Entity* target, int num1, int num2) const;

    std::vector<std::shared_ptr<IEffect>> effects;

    bool useScriptTag = false;
    bool isOneTurnEffect = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ENCHANT_HPP