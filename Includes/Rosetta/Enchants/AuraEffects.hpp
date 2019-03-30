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
//!
//! \brief AuraEffects class.
//!
//! This class is a simple container for saving tag value perturbations from
//! external auras. Call indexer to get value for a particular tag.
//!
class AuraEffects
{
 public:
    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    int GetGameTag(GameTag tag) const;

    //! Sets game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    virtual void SetGameTag(GameTag tag, int value);

private:
    std::map<GameTag, int> m_gameTags;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_AURA_EFFECTS_HPP
