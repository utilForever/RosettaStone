// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_SPELL_HPP
#define ROSETTASTONE_SPELL_HPP

#include <Rosetta/Models/Playable.hpp>

namespace RosettaStone
{
//!
//! \brief Spell class.
//!
//! This class inherits from Playable class.
//!
class Spell : public Playable
{
 public:
    //! Constructs spell with given \p player, \p card, \p tags and \p id.
    //! \param player The owner of the card.
    //! \param card The card.
    //! \param tags The game tags.
    //! \param id The card ID.
    Spell(Player* player, Card* card, std::map<GameTag, int> tags, int id = -1);

    //! Default destructor.
    ~Spell() = default;

    //! Deleted copy constructor.
    Spell(const Spell&) = delete;

    //! Deleted copy assignment operator.
    Spell& operator=(const Spell&) = delete;

    //! Deleted move constructor.
    Spell(Spell&&) noexcept = delete;

    //! Deleted move assignment operator.
    Spell& operator=(Spell&&) noexcept = delete;

    //! Increases the value of quest progress.
    void IncreaseQuestProgress();

    //! Returns whether spell is secret.
    //! \return Whether spell is secret.
    bool IsSecret() const;

    //! Returns whether spell is quest.
    //! \return Whether spell is quest.
    bool IsQuest() const;

    //! Returns whether spell is twinspell.
    //! \return Whether spell is twinspell.
    bool IsTwinspell() const;

    //! Returns whether spell is countered.
    //! \return Whether spell is countered.
    bool IsCountered() const;

    //! Calculates if a target is valid by testing the game state for each
    //! hardcoded requirement.
    //! \param target The proposed target.
    //! \return true if the proposed target is valid, false otherwise.
    bool TargetingRequirements(Character* target) const override;

    //! Gets a value indicating whether source entity is playable by player.
    //! Dynamic requirements are checked, eg: If a spell costs health instead of
    //! mana, this method will return false if the health cost would be higher
    //! than the available health.
    //! \return true if it is playable by player, false otherwise.
    bool IsPlayableByPlayer() override;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SPELL_HPP
