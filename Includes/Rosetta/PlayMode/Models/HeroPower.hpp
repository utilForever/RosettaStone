// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_HERO_POWER_HPP
#define ROSETTASTONE_PLAYMODE_HERO_POWER_HPP

#include <Rosetta/PlayMode/Models/Playable.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief HeroPower class.
//!
//! This class inherits from Playable class.
//!
class HeroPower : public Playable
{
 public:
    //! Constructs hero power with given \p _player, \p _card,
    //! \p tags and \p id.
    //! \param _player The owner of the card.
    //! \param _card The card.
    //! \param tags The game tags.
    //! \param id The ID.
    HeroPower(Player* _player, Card* _card, std::map<GameTag, int> tags,
              int id = -1);

    //! Default destructor.
    ~HeroPower() = default;

    //! Deleted copy constructor.
    HeroPower(const HeroPower&) = delete;

    //! Deleted copy assignment operator.
    HeroPower& operator=(const HeroPower&) = delete;

    //! Deleted move constructor.
    HeroPower(HeroPower&&) noexcept = delete;

    //! Deleted move assignment operator.
    HeroPower& operator=(HeroPower&&) noexcept = delete;

    //! Calculates if a target is valid by testing the game state for each
    //! hardcoded requirement.
    //! \param _card A card to check targeting requirements.
    //! \param target The proposed target.
    //! \return true if the proposed target is valid, false otherwise.
    bool TargetingRequirements(Card* _card, Character* target) const override;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_HERO_POWER_HPP
