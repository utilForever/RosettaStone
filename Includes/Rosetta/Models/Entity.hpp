// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_ENTITY_HPP
#define ROSETTASTONE_ENTITY_HPP

#include <Rosetta/Cards/Card.hpp>
#include <Rosetta/Enchants/AuraEffects.hpp>
#include <Rosetta/Enums/TaskEnums.hpp>
#include <Rosetta/Zones/IZone.hpp>

#include <array>
#include <map>

namespace RosettaStone
{
class Card;
class Enchantment;
class Game;
class Player;

//!
//! \brief Abstract entity structure that stores card data.
//!
//! This structure is base structure of all data-holding/action-performing/
//! visible or invisible objects in a RosettaStone.
//! An entity is defined as a collection of properties, called GameTags.
//!
class Entity
{
 public:
    //! Default constructor.
    Entity() = default;

    //! Constructs entity with given \p _owner, \p _card and \p tags.
    //! \param _owner The owner of the card.
    //! \param _card The card.
    //! \param tags The game tags.
    Entity(Player& _owner, Card& _card, std::map<GameTag, int> tags);

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

    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    int GetGameTag(GameTag tag) const;

    //! Sets game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    virtual void SetGameTag(GameTag tag, int value);

    //! Returns the value of zone type.
    //! \return The value of zone type.
    ZoneType GetZoneType() const;

    //! Sets the value of zone type.
    //! \param type The value of zone type.
    void SetZoneType(ZoneType type);

    //! Returns the value of zone position.
    //! \return The value of zone position.
    int GetZonePosition() const;

    //! Sets the value of zone position.
    //! \param value The value of zone position.
    void SetZonePosition(int value);

    //! Returns the value of cost.
    //! \return The value of cost.
    int GetCost() const;

    //! Sets the value of cost.
    //! \param cost The value of cost.
    void SetCost(int cost);

    //! Returns the value of exhausted.
    //! \return The value of exhausted.
    bool IsExhausted() const;

    //! Sets the value of exhausted.
    //! \param exhausted The value of exhausted.
    void SetExhausted(bool exhausted);

    //! Returns whether this entity has combo.
    //! \return Whether this entity has combo.
    bool HasCombo() const;

    //! Returns whether this entity has overload.
    //! \return Whether this entity has overload.
    bool HasOverload() const;

    //! Returns the value of overload.
    //! \return The value of overload.
    int GetOverload() const;

    //! Returns whether this entity has deathrattle power.
    //! \return Whether this entity has deathrattle power.
    bool HasDeathrattle() const;

    //! Returns whether this entity has to choose one.
    //! \return Whether this entity has to choose one.
    bool HasChooseOne() const;

    //! Resets all game tag values that where changed after creation.
    //! Any enchants and trigger is removed.
    virtual void Reset();

    //! Destroys entity.
    virtual void Destroy();

    //! Activates the task.
    //! \param type The type of power.
    //! \param target The target.
    //! \param chooseOne The index of chosen card from two cards.
    void ActivateTask(PowerType type, Entity* target = nullptr, int chooseOne = 0);

    //! Builds a new entity that can be added to a game.
    //! \param player An owner of the entity.
    //! \param card The card from which the entity must be derived.
    //! \param cardTags The tags preset of card for the entity.
    //! \param zone The zone in which the entity must spawn.
    //! \param id An entity ID to assign to the newly created entity.
    //! \return A pointer to entity that is allocated dynamically.
    static Entity* GetFromCard(
        Player& player, Card&& card,
        std::optional<std::map<GameTag, int>> cardTags = std::nullopt,
        IZone* zone = nullptr, int id = -1);

    Player* owner = nullptr;
    Card card;

    IZone* zone = nullptr;

    AuraEffects* auraEffects = nullptr;
    Aura* onGoingEffect = nullptr;
    Trigger* activatedTrigger = nullptr;

    std::array<Entity*, 2> chooseOneCard{};
    std::vector<Enchantment*> appliedEnchantments;

    int id = 0;
    int orderOfPlay = 0;

    bool isDestroyed = false;

 protected:
    std::map<GameTag, int> m_gameTags;

 private:
    //! Releases dynamic allocated resources.
    void FreeMemory();
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_ENTITY_HPP
