// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_ENTITY_HPP
#define HEARTHSTONEPP_ENTITY_HPP

#include <hspp/Cards/Card.hpp>

#include <map>

namespace Hearthstonepp
{
class Card;
class GameAgent;
class GameTag;

//!
//! \brief Abstract entity structure that stores card data.
//!
//! This structure is base structure of all data-holding/action-performing/
//! visible or invisible objects in a Hearthstone++.
//! An entity is defined as a collection of properties, called GameTags.
//!
class Entity
{
 public:
    //! Default constructor.
    Entity() = default;

    //! Constructs entity with given \p _card.
    //! \param _card A reference to the card.
    Entity(GameAgent* gameAgent, Card& _card);

    //! Destructor.
    virtual ~Entity();

    //! Copy constructor.
    Entity(const Entity& ent);

    //! Move constructor.
    Entity(Entity&& ent) noexcept;

    //! Copy assignment operator.
    Entity& operator=(const Entity& ent);

    //! Move assignment operator.
    Entity& operator=(Entity&& ent) noexcept;

    GameAgent* GetGameAgent() const;

    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    int GetGameTag(GameTag tag) const;

    //! Sets game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    virtual void SetGameTag(GameTag tag, int value);

    const Card* card = nullptr;

 protected:
    GameAgent* m_gameAgent = nullptr;

    std::map<GameTag, int> m_gameTags;

 private:
    //! Releases dynamic allocated resources.
    void FreeMemory();
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_ENTITY_HPP