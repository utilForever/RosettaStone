// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_SPELL_HPP
#define ROSETTASTONE_SPELL_HPP

#include <Rosetta/Models/Entity.hpp>

namespace RosettaStone
{
//!
//! \brief Spell class.
//!
//! This class inherits from Entity structure.
//!
class Spell : public Entity
{
 public:
    //! Default constructor.
    Spell() = default;

    //! Constructs spell with given \p _owner and \p _card.
    //! \param _owner An owner of the card.
    //! \param _card A reference to the card.
    Spell(Player& _owner, Card& _card);

    //! Default destructor.
    ~Spell() = default;

    //! Default copy constructor.
    Spell(const Spell& spell) = default;

    //! Default move constructor.
    Spell(Spell&& spell) = default;

    //! Default copy assignment operator.
    Spell& operator=(const Spell& spell) = default;

    //! Default move assignment operator.
    Spell& operator=(Spell&& spell) = default;

    //! Returns whether spell is secret.
    //! \return Whether spell is secret.
    bool IsSecret() const;

    //! Returns whether spell is countered.
    //! \return Whether spell is countered.
    bool IsCountered() const;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_SPELL_HPP
