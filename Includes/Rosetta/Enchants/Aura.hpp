// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_AURA_HPP
#define ROSETTASTONE_AURA_HPP

#include <Rosetta/Enchants/Enchant.hpp>

#include <string>

namespace RosettaStone
{
class Entity;

//! Aura types. Indicates the range of auras.
enum class AuraType
{
    INVALID,   //!< Invalid type.
    ADJACENT,  //!< This type of aura affects the minions adjacent to the source
               //!< of the aura.
    FIELD_EXCEPT_SOURCE  //!< This type of aura affects all friendly minions
                         //!< except the source of the aura.
};

//!
//! \brief Aura class.
//!
//! This class represent aura. Auras can affect entities and change the applied
//! entities attack, cost and so on. Aura must be activated first to affect
//! entities.
//!
class Aura
{
 public:
    //! Default constructor.
    Aura() = default;

    //! Constructs aura with given \p enchantmentID and \p type.
    //! \param enchantmentID The enchantment card ID.
    //! \param type The type of aura.
    Aura(std::string&& enchantmentID, AuraType type);

    //! Constructs aura with given \p prototype and \p owner.
    //! \param prototype An aura for prototype.
    //! \param owner An owner of aura.
    Aura(Aura& prototype, Entity& owner);

    //! Sets aura to be updated.
    //! \param value An value to be updated.
    void SetToBeUpdated(bool value);

    //! Activates aura to battlefield.
    //! \param owner An owner of aura.
    void Activate(Entity& owner);

    //! Updates aura to apply the effect to recently modified entities.
    void Update();

    //! Removes aura to disapply the effect to recently modified entities.
    void Remove();

    //! Removes entity to update a list of entities.
    //! \param entity An entity to remove.
    void RemoveEntity(Entity& entity);

    //! Apply aura's effect(s) to target entity.
    //! \param entity An entity to apply aura's effect(s).
    void Apply(Entity& entity);

    //! Returns the type of aura.
    //! \return The type of aura.
    AuraType GetAuraType();

    //! Returns the effect of aura.
    //! \return The effect of aura.
    std::vector<Effect> GetEffects();

    //! Returns the applied entities affected by the aura.
    //! \return The applied entities affected by the aura.
    std::vector<Entity*> GetAppliedEntities();

 private:
    //! Adds aura to battlefield.
    void AddToField();

    //! Internal method of Update().
    void UpdateInternal();

    //! Internal method of Remove().
    void RemoveInternal();

    std::string m_enchantmentID;
    AuraType m_type = AuraType::INVALID;

    Entity* m_owner = nullptr;
    std::vector<Effect> m_effects;
    std::vector<Entity*> m_appliedEntities;

    bool m_turnOn = true;
    bool m_toBeUpdated = true;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_AURA_HPP
