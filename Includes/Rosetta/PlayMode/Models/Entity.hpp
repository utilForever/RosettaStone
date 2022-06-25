// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_ENTITY_HPP
#define ROSETTASTONE_PLAYMODE_ENTITY_HPP

#include <Rosetta/PlayMode/Cards/Card.hpp>
#include <Rosetta/PlayMode/Enchants/AuraEffects.hpp>
#include <Rosetta/PlayMode/Managers/CostManager.hpp>
#include <Rosetta/PlayMode/Zones/IZone.hpp>

#include <map>
#include <optional>

namespace RosettaStone::PlayMode
{
class Game;
class Player;
class Card;
class Enchantment;

//!
//! \brief Entity class.
//!
//! This class is base structure of all data-holding/action-performing/
//! visible or invisible objects in a RosettaStone.
//! An entity is defined as a collection of properties, called GameTags.
//!
class Entity
{
 public:
    //! Default constructor.
    Entity() = default;

    //! Constructs entity with given \p _game, \p _card, \p _tags and \p _id.
    //! \param _game The game.
    //! \param _card The card.
    //! \param _tags The game tags.
    //! \param _id The ID.
    Entity(Game* _game, Card* _card, std::map<GameTag, int> _tags,
           int _id = -1);

    //! Destructor.
    virtual ~Entity();

    //! Deleted copy constructor.
    Entity(const Entity&) = delete;

    //! Deleted copy assignment operator.
    Entity& operator=(const Entity&) = delete;

    //! Deleted move constructor.
    Entity(Entity&&) noexcept = delete;

    //! Deleted move assignment operator.
    Entity& operator=(Entity&&) noexcept = delete;

    //! Returns the value of native game tag.
    //! \param tag The game tag of card.
    //! \return The value of native game tag.
    int GetNativeGameTag(GameTag tag) const;

    //! Sets the value of game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for native game tag.
    void SetNativeGameTag(GameTag tag, int value);

    //! Returns a list of game tag.
    //! \return A list of game tag.
    std::map<GameTag, int> GetGameTags() const;

    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    virtual int GetGameTag(GameTag tag) const;

    //! Sets the value of game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    virtual void SetGameTag(GameTag tag, int value);

    //! Returns the value of card target.
    //! \return The value of card target.
    int GetCardTarget() const;

    //! Sets the value of card target.
    //! \param value The value of card target.
    void SetCardTarget(int value);

    //! Resets all game tag values that where changed after creation.
    //! Any enchants and trigger is removed.
    virtual void Reset();

    //! Builds a new entity that can be added to a game.
    //! \param player An owner of the entity.
    //! \param card The card from which the entity must be derived.
    //! \param cardTags The tags preset of card for the entity.
    //! \param zone The zone in which the entity must spawn.
    //! \param id An entity ID to assign to the newly created entity.
    //! \return A pointer to entity that is allocated dynamically.
    static Playable* GetFromCard(
        Player* player, Card* card,
        std::optional<std::map<GameTag, int>> cardTags = std::nullopt,
        const IZone* zone = nullptr, int id = -1);

    Game* game = nullptr;
    Player* player = nullptr;
    Card* card = nullptr;
    IZone* zone = nullptr;

    AuraEffects* auraEffects = nullptr;
    std::vector<std::shared_ptr<Enchantment>> appliedEnchantments;

 protected:
    std::map<GameTag, int> m_gameTags;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ENTITY_HPP
