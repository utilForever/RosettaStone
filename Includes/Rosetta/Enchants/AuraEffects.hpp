// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_AURA_EFFECTS_HPP
#define ROSETTASTONE_AURA_EFFECTS_HPP

#include <Rosetta/Enums/CardEnums.hpp>

#include <map>

namespace RosettaStone
{
class Entity;

//!
//! \brief AuraEffects class.
//!
//! This class is a simple container for saving tag value perturbations from
//! external auras. Call indexer to get value for a particular tag.
//!
class AuraEffects
{
 public:
    //! Constructs aura effects with given \p owner.
    //! \param owner The owner of aura effects.
    explicit AuraEffects(Entity* owner);

    //! Returns the owner of aura effects.
    //! \return The owner of aura effects.
    Entity* GetOwner() const;

    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    int GetGameTag(GameTag tag) const;

    //! Sets game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    void SetGameTag(GameTag tag, int value);

 private:
    Entity* m_owner = nullptr;

    std::map<GameTag, int> m_gameTags;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_AURA_EFFECTS_HPP
