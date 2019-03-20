// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_GRAVEYARD_HPP
#define ROSETTASTONE_GRAVEYARD_HPP

#include <Rosetta/Models/Entity.hpp>

#include <vector>

namespace RosettaStone
{
//!
//! \brief Graveyard class.
//!
//! This class is where the cards that are no longer used in the game.
//! Discarded cards and spell cards, after their activation, go directly to it.
//!
class Graveyard
{
 public:
    //! Default constructor.
    Graveyard();

    //! Returns the owner of graveyard.
    //! \return The owner of graveyard.
    Player& GetOwner() const;

    //! Sets the owner of graveyard.
    //! \param owner The owner of graveyard.
    void SetOwner(Player& owner);

    //! Adds a card to graveyard.
    //! \param card The card to add to graveyard.
    void AddCard(Entity& card);

 private:
    Player* m_owner = nullptr;

    std::vector<Entity*> m_cards;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GRAVEYARD_HPP
