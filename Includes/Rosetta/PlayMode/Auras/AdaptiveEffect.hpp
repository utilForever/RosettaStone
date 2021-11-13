// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_ADAPTIVE_EFFECT_HPP
#define ROSETTASTONE_PLAYMODE_ADAPTIVE_EFFECT_HPP

#include <Rosetta/PlayMode/Auras/Aura.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief AdaptiveEffect class.
//!
//! Effects of this kind of Auras are influenced by other factors in game, in
//! real time. e.g. Lightspawn, Southsea Deckhand.
//!
class AdaptiveEffect : public IAura
{
 public:
    //! Constructs adaptive effect with given \p tag, \p effectOp
    //! and \p valueFunc.
    //! \param tag The game tag.
    //! \param effectOp The effect operator to change the attribute.
    //! \param valueFunc The value function to get the attribute.
    AdaptiveEffect(GameTag tag, EffectOperator effectOp,
                   std::function<int(Playable*)> valueFunc);

    //! Constructs adaptive effect with given \p condition and \p tag.
    //! \param condition The specific condition.
    //! \param tag The game tag.
    AdaptiveEffect(std::shared_ptr<SelfCondition> condition, GameTag tag);

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of adaptive effect.
    //! \param cloning The flag to indicate that it is cloned.
    void Activate(Playable* owner,
                  [[maybe_unused]] bool cloning = false) override;

    //! Updates this effect to apply the effect to recently modified entities.
    void Update() override;

    //! Removes this effect from the game to stop affecting entities.
    void Remove() override;

    //! Clones aura effect to \p clone.
    //! \param clone The entity to clone aura effect.
    void Clone(Playable* clone) override;

 private:
    //! Constructs adaptive effect with given \p prototype and \p owner.
    //! \param prototype An adaptive effect for prototype.
    //! \param owner An owner of adaptive effect.
    AdaptiveEffect(const AdaptiveEffect& prototype, Playable& owner);

    Playable* m_owner = nullptr;

    std::shared_ptr<SelfCondition> m_condition;
    std::function<int(Playable*)> m_valueFunc;

    GameTag m_tag;
    EffectOperator m_operator;

    int m_lastValue = 0;
    bool m_turnOn = true;
    bool m_isSwitching = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ADAPTIVE_EFFECT_HPP
