// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_AURA_HPP
#define ROSETTASTONE_AURA_HPP

#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Enchants/Enchant.hpp>

#include <string>

namespace RosettaStone
{
class Entity;

//! Aura types. Indicates the range of auras.
enum class AuraType
{
    INVALID,   //!< Invalid type.
    SELF,      //!< This type of aura only affects the source of the aura.
    ADJACENT,  //!< This type of aura affects the minions adjacent to the source
               //!< of the aura.
    FIELD,     //!< This type of aura affects all friendly minions.
    FIELD_EXCEPT_SOURCE,  //!< This type of aura affects all friendly minions
                          //!< except the source of the aura.
    WEAPON,   //!< This type of aura affects the weapon of the source's
              //!< controller.
    ADAPTIVE  //!< This type of aura is influenced by other factors in game.
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

    //! Constructs aura with given \p type and \p effects.
    //! \param type The type of aura.
    //! \param effects A list of effect.
    Aura(AuraType type, std::vector<Effect*> effects);

    //! Constructs aura with given \p type and \p enchantmentID.
    //! \param type The type of aura.
    //! \param enchantmentID The enchantment card ID.
    Aura(AuraType type, std::string&& enchantmentID);

    //! Default virtual destructor.
    virtual ~Aura() = default;

    //! Sets aura to be updated.
    //! \param value An value to be updated.
    void SetToBeUpdated(bool value);

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of aura.
    virtual void Activate(Entity* owner);

    //! Updates this effect to apply the effect to recently modified entities.
    virtual void Update();

    //! Removes this effect from the game to stop affecting entities.
    virtual void Remove();

    //! Removes entity to update a list of entities.
    //! \param entity An entity to remove.
    void RemoveEntity(Entity* entity);

    //! Apply aura's effect(s) to target entity.
    //! \param entity An entity to apply aura's effect(s).
    void Apply(Entity* entity);

    //! Returns the type of aura.
    //! \return The type of aura.
    AuraType GetAuraType() const;

    //! Returns the effect of aura.
    //! \return The effect of aura.
    std::vector<Effect*> GetEffects() const;

    //! Returns the applied entities affected by the aura.
    //! \return The applied entities affected by the aura.
    std::vector<Entity*> GetAppliedEntities() const;

    SelfCondition* condition = nullptr;
    bool restless = false;

 protected:
    //! Constructs aura with given \p prototype and \p owner.
    //! \param prototype An aura for prototype.
    //! \param owner An owner of aura.
    Aura(Aura& prototype, Entity& owner);

    AuraType m_type = AuraType::INVALID;
    Entity* m_owner = nullptr;

    std::vector<Effect*> m_effects;

    bool m_turnOn = true;

 private:
    //! Adds aura to battlefield.
    void AddToField();

    //! Internal method of Update().
    void UpdateInternal();

    //! Internal method of Remove().
    void RemoveInternal();

    std::string m_enchantmentID;

    std::vector<Entity*> m_appliedEntities;
    std::vector<Entity*> m_tempList;

    bool m_toBeUpdated = true;
};

//!
//! \brief AdaptiveEffect class.
//!
//! Effects of this kind of Auras are influenced by other factors in game, in
//! real time. e.g. Lightspawn, Southsea Deckhand.
//!
class AdaptiveEffect : public Aura
{
 public:
    //! Constructs adaptive effect with given \p _condition and \p tags.
    //! \param _condition The specific condition.
    //! \param tags The given tags.
    AdaptiveEffect(SelfCondition* _condition, std::vector<GameTag> tags);

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of adaptive effect.
    void Activate(Entity* owner) override;

    //! Updates this effect to apply the effect to recently modified entities.
    void Update() override;

    //! Removes this effect from the game to stop affecting entities.
    void Remove() override;

 private:
    //! Constructs adaptive effect with given \p prototype and \p owner.
    //! \param prototype An adaptive effect for prototype.
    //! \param owner An owner of adaptive effect.
    AdaptiveEffect(AdaptiveEffect& prototype, Entity& owner);

    std::vector<GameTag> m_tags;
    std::vector<int> m_lastValues;

    bool m_isSwitching = false;
};

//!
//! \brief EnrageEffect class.
//!
//! Enrage is the informal name for a minion ability where the stated effect
//! becomes active only when the minion is damaged. If the minion regains
//! undamaged status, either through healing or a forced resetting of its
//! maximum Health, the Enrage effect will be canceled.
//!
class EnrageEffect : public Aura
{
 public:
    //! Constructs enrage effect with given \p type and \p effects.
    //! \param type The type of aura.
    //! \param effects A list of effect.
    EnrageEffect(AuraType type, std::vector<Effect*> effects);

    //! Create new Aura instance to the owner's game.
    //! \param owner An owner of enrage effect.
    void Activate(Entity* owner) override;

    //! Updates this effect to apply the effect to recently modified entities.
    void Update() override;

 private:
    //! Constructs enrage effect with given \p prototype and \p owner.
    //! \param prototype An enrage effect for prototype.
    //! \param owner An owner of adaptive effect.
    EnrageEffect(EnrageEffect& prototype, Entity& owner);

    Entity* m_target = nullptr;
    bool m_enraged = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_AURA_HPP
