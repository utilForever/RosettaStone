// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_ENTITY_H
#define HEARTHSTONEPP_ENTITY_H

#include <hspp/Cards/Card.h>

#include <map>

namespace Hearthstonepp
{
struct Card;
class GameTag;

//!
//! \brief Abstract entity structure that stores card data.
//!
//! This structure is base structure of all data-holding/action-performing/
//! visible or invisible objects in a Hearthstone++.
//! An entity is defined as a collection of properties, called GameTags.
//!
struct Entity
{
    //! Default constructor.
    Entity() = default;

    //! Constructs entity with given \p pCard.
    //! \param pCard A pointer to the card.
    Entity(const Card* pCard);

    //! Destructor.
    virtual ~Entity() = default;

    //! Copy constructor.
    Entity(const Entity& ent);

    //! Copy assignment operator.
    Entity& operator=(const Entity& ent);

    //! Clones member variables.
    virtual Entity* Clone() const;

    const Card* card = nullptr;

    std::map<GameTag, int> gameTags;
};
}  // namespace Hearthstonepp

#endif