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
class Game;
class GameTag;
class Player;

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

    //! Constructs entity with given \p gameAgent and \p _card.
    //! \param gameAgent The game agent.
    //! \param _card A reference to the card.
    Entity(Game* gameAgent, Card& _card);

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

    //! Returns the game agent.
    //! \return A pointer to the game agent.
    Game* GetGame() const;

    //! Returns the owner of character.
    //! \return The owner of character.
    Player& GetOwner() const;

    //! Sets the owner of character.
    //! \param owner The owner of character.
    void SetOwner(Player& owner);

    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    int GetGameTag(GameTag tag) const;

    //! Sets game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    virtual void SetGameTag(GameTag tag, int value);

    //! Destroys character.
    virtual void Destroy();

    Card* card = nullptr;
    bool isDestroyed = false;

 protected:
    Game* m_game = nullptr;
    Player* m_owner = nullptr;

    std::map<GameTag, int> m_gameTags;

 private:
    //! Releases dynamic allocated resources.
    void FreeMemory();
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_ENTITY_HPP