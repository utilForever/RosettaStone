// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_SPELL_HPP
#define HEARTHSTONEPP_SPELL_HPP

#include <hspp/Cards/Entity.hpp>

namespace Hearthstonepp
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

    //! Constructs spell with given \p gameAgent and \p card.
    //! \param gameAgent The game agent.
    //! \param card A reference to the card.
    Spell(GameAgent* gameAgent, Card& card);

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

    //! Destroys spell.
    void Destroy() override;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_SPELL_HPP