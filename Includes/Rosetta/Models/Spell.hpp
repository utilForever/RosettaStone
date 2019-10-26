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
    //! Constructs spell with given \p player, \p card and \p tags.
    //! \param player The owner of the card.
    //! \param card The card.
    //! \param tags The game tags.
    Spell(Player* player, Card* card, std::map<GameTag, int> tags);

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

    //! Returns whether spell is secret.
    //! \return Whether spell is secret.
    bool IsSecret() const;

    //! Returns whether spell is countered.
    //! \return Whether spell is countered.
    bool IsCountered() const;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SPELL_HPP
