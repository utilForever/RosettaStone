// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_AURA_HPP
#define ROSETTASTONE_PLAYMODE_AURA_HPP

#include <Rosetta/Common/Enums/AuraEnums.hpp>
#include <Rosetta/Common/Enums/TriggerEnums.hpp>
#include <Rosetta/Common/PriorityQueue.hpp>
#include <Rosetta/PlayMode/Auras/AuraUpdateInstruction.hpp>
#include <Rosetta/PlayMode/Auras/IAura.hpp>
#include <Rosetta/PlayMode/Conditions/SelfCondition.hpp>
#include <Rosetta/PlayMode/Enchants/Enchant.hpp>
#include <Rosetta/PlayMode/Triggers/Trigger.hpp>

#include <memory>
#include <string>

namespace RosettaStone::PlayMode
{
class Card;
class Playable;

//!
//! \brief Aura class.
//!
//! This class represent aura. Auras can affect entities and change the applied
//! entities attack, cost and so on. Aura must be activated first to affect
//! entities.
//!
class Aura : public IAura
{
 public:
    //! Default constructor.
    Aura() = default;

    //! Constructs aura with given \p type and \p effects.
    //! \param type The type of aura.
    //! \param effects A list of effect.
    Aura(AuraType type, std::vector<std::shared_ptr<IEffect>> effects);

    //! Constructs aura with given \p type and \p enchantmentID.
    //! \param type The type of aura.
    //! \param enchantmentID The enchantment card ID.
    Aura(AuraType type, std::string&& enchantmentID);

    //! Default virtual destructor.
    virtual ~Aura() = default;

    //! Gets the type of aura.
    //! \return The type of aura.
    AuraType GetType() const;

    //! Create new Aura instance to the owner's game.
    //! \param owner The owner of aura.
    //! \param cloning The flag to indicate that it is cloned.
    void Activate(Playable* owner, bool cloning = false) override;

    //! Apply this aura to the target entities or remove this aura
    //! if the owner is nullified.
    void Update() override;

    //! Removes this effect from the game to stop affecting entities.
    void Remove() override;

    //! Clones aura effect to \p clone.
    //! \param clone The entity to clone aura effect.
    void Clone(Playable* clone) override;

    //! Applies aura's effect(s) to target entity.
    //! \param entity The entity to apply aura's effect(s).
    virtual void Apply(Playable* entity);

    //! Disapplies aura's effect(s) to target entity.
    //! \param entity The entity to disapply aura's effect(s).
    virtual void Disapply(Playable* entity);

    //! Notifies this aura instance that the given entity is added to
    //! the corresponding zone.
    //! \param entity The entity to notify that it is added.
    void NotifyEntityAdded(Playable* entity);

    //! Notifies this aura instance that the given entity is removed from
    //! the corresponding zone.
    //! \param entity The entity to notify that it is removed.
    void NotifyEntityRemoved(Playable* entity);

    std::shared_ptr<SelfCondition> condition;
    std::pair<TriggerType, std::shared_ptr<SelfCondition>> removeTrigger;
    bool restless = false;

 protected:
    //! Constructs aura with given \p prototype and \p owner.
    //! \param prototype An aura for prototype.
    //! \param owner An owner of aura.
    Aura(const Aura& prototype, Playable& owner);

    //! Adds aura to the game.
    //! \param owner An owner of aura.
    //! \param aura The dynamically allocated Aura instance.
    static void AddToGame(Playable& owner, Aura& aura);

    AuraType m_type = AuraType::INVALID;
    Playable* m_owner = nullptr;

    PriorityQueue<AuraUpdateInstruction> m_auraUpdateInstQueue;
    std::vector<Playable*> m_appliedEntities;

    TriggerEventHandler m_removeHandler;

    Card* m_enchantmentCard = nullptr;
    std::vector<std::shared_ptr<IEffect>> m_effects;

    bool m_turnOn = true;

 private:
    //! Internal method of Update().
    void UpdateInternal();

    //! Internal method of Remove().
    virtual void RemoveInternal();

    //! Renews the condition of the applied entities.
    void RenewAll();
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_AURA_HPP
