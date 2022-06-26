// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_SPELL_HPP
#define ROSETTASTONE_PLAYMODE_SPELL_HPP

#include <Rosetta/PlayMode/Models/Playable.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief Spell class.
//!
//! This class inherits from Playable class.
//!
class Spell : public Playable
{
 public:
    //! Constructs spell with given \p _player, \p _card, \p tags and \p id.
    //! \param _player The owner of the card.
    //! \param _card The card.
    //! \param tags The game tags.
    //! \param id The card ID.
    Spell(Player* _player, Card* _card, std::map<GameTag, int> tags,
          int id = -1);

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

    //! Returns the value of spell school.
    //! \return The value of spell school.
    SpellSchool GetSpellSchool() const;

    //! Gets the value of quest progress.
    //! \return The value of quest progress.
    int GetQuestProgress() const;

    //! Gets the value of quest progress total.
    //! \return The value of quest progress total.
    int GetQuestProgressTotal() const;

    //! Increases the value of quest progress.
    void IncreaseQuestProgress();

    //! Returns whether spell is secret.
    //! \return Whether spell is secret.
    bool IsSecret() const;

    //! Returns whether spell is quest.
    //! \return Whether spell is quest.
    bool IsQuest() const;

    //! Returns whether spell is sidequest.
    //! \return Whether spell is sidequest.
    bool IsSidequest() const;

    //! Returns whether spell is questline.
    //! \return Whether spell is questline.
    bool IsQuestline() const;

    //! Returns whether spell is twinspell.
    //! \return Whether spell is twinspell.
    bool IsTwinspell() const;

    //! Returns whether spell is countered.
    //! \return Whether spell is countered.
    bool IsCountered() const;

    //! Calculates if a target is valid by testing the game state for each
    //! hardcoded requirement.
    //! \param _card A card to check targeting requirements.
    //! \param target The proposed target.
    //! \return true if the proposed target is valid, false otherwise.
    bool TargetingRequirements(Card* _card, Character* target) const override;

    //! Gets a value indicating whether source entity is playable by player.
    //! Dynamic requirements are checked, eg: If a spell costs health instead of
    //! mana, this method will return false if the health cost would be higher
    //! than the available health.
    //! \return true if it is playable by player, false otherwise.
    bool IsPlayableByPlayer() override;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_SPELL_HPP
