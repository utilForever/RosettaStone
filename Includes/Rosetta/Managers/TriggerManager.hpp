// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TRIGGER_MANAGER_HPP
#define ROSETTASTONE_TRIGGER_MANAGER_HPP

#include <Rosetta/Managers/TriggerEvent.hpp>

namespace RosettaStone
{
class Entity;

//!
//! \brief TriggerManager class.
//!
//! This class monitors trigger and invokes method when a trigger is activated.
//!
class TriggerManager
{
 public:
    //! Callback for trigger when player's turn is started.
    //! \param sender An entity that is the source of trigger.
    void OnStartTurnTrigger(Entity* sender);

    //! Callback for trigger when player's turn is ended.
    //! \param sender An entity that is the source of trigger.
    void OnEndTurnTrigger(Entity* sender);

    //! Callback for trigger when player plays a card.
    //! \param sender An entity that is the source of trigger.
    void OnPlayCardTrigger(Entity* sender);

    //! Callback for trigger when player plays a minion.
    //! \param sender An entity that is the source of trigger.
    void OnPlayMinionTrigger(Entity* sender);

    //! Callback for trigger after player plays a minion.
    //! \param sender An entity that is the source of trigger.
    void OnAfterPlayMinionTrigger(Entity* sender);

    //! Callback for trigger when player plays a spell card.
    //! \param sender An entity that is the source of trigger.
    void OnCastSpellTrigger(Entity* sender);

    //! Callback for trigger after player plays a spell card.
    //! \param sender An entity that is the source of trigger.
    void OnAfterCastTrigger(Entity* sender);

    //! Callback for trigger when the secret is revealed.
    //! \param sender An entity that is the source of trigger.
    void OnSecretRevealedTrigger(Entity* sender);

    //! Callback for trigger when playable heals character.
    //! \param sender An entity that is the source of trigger.
    void OnGiveHealTrigger(Entity* sender);

    //! Callback for trigger when character is healed.
    //! \param sender An entity that is the source of trigger.
    void OnTakeHealTrigger(Entity* sender);

    //! Callback for trigger when entity attacks target.
    //! \param sender An entity that is the source of trigger.
    void OnAttackTrigger(Entity* sender);

    //! Callback for trigger when entity is summoned.
    //! \param sender An entity that is the source of trigger.
    void OnSummonTrigger(Entity* sender);

    //! Callback for trigger after entity is summoned.
    //! \param sender An entity that is the source of trigger.
    void OnAfterSummonTrigger(Entity* sender);

    //! Callback for trigger when entity deals damage.
    //! \param sender An entity that is the source of trigger.
    void OnDealDamageTrigger(Entity* sender);

    //! Callback for trigger when entity is taken damage.
    //! \param sender An entity that is the source of trigger.
    void OnTakeDamageTrigger(Entity* sender);

    //! Callback for trigger when entity is targeted.
    //! \param sender An entity that is the source of trigger.
    void OnTargetTrigger(Entity* sender);

    //! Callback for trigger when minion is dead.
    //! \param sender An entity that is the source of trigger.
    void OnDeathTrigger(Entity* sender);

    //! Callback for trigger when hero uses power.
    //! \param sender An entity that is the source of trigger.
    void OnUseHeroPowerTrigger(Entity* sender);

    TriggerEvent startTurnTrigger;
    TriggerEvent endTurnTrigger;
    TriggerEvent playCardTrigger;
    TriggerEvent playMinionTrigger;
    TriggerEvent afterPlayMinionTrigger;
    TriggerEvent castSpellTrigger;
    TriggerEvent afterCastTrigger;
    TriggerEvent secretRevealedTrigger;
    TriggerEvent giveHealTrigger;
    TriggerEvent takeHealTrigger;
    TriggerEvent attackTrigger;
    TriggerEvent summonTrigger;
    TriggerEvent afterSummonTrigger;
    TriggerEvent dealDamageTrigger;
    TriggerEvent takeDamageTrigger;
    TriggerEvent targetTrigger;
    TriggerEvent deathTrigger;
    TriggerEvent useHeroPowerTrigger;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_MANAGER_HPP
