// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_TRIGGER_MANAGER_HPP
#define ROSETTASTONE_TRIGGER_MANAGER_HPP

#include <functional>

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
    void OnStartTurnTrigger(Entity* sender) const;

    //! Callback for trigger when player's turn is ended.
    //! \param sender An entity that is the source of trigger.
    void OnEndTurnTrigger(Entity* sender) const;

    //! Callback for trigger when player plays a card.
    //! \param sender An entity that is the source of trigger.
    void OnPlayCardTrigger(Entity* sender) const;

    //! Callback for trigger when player plays a minion.
    //! \param sender An entity that is the source of trigger.
    void OnPlayMinionTrigger(Entity* sender) const;

    //! Callback for trigger after player plays a minion.
    //! \param sender An entity that is the source of trigger.
    void OnAfterPlayMinionTrigger(Entity* sender) const;

    //! Callback for trigger when player plays a spell card.
    //! \param sender An entity that is the source of trigger.
    void OnCastSpellTrigger(Entity* sender) const;

    //! Callback for trigger after player plays a spell card.
    //! \param sender An entity that is the source of trigger.
    void OnAfterCastTrigger(Entity* sender) const;

    //! Callback for trigger when the secret is revealed.
    //! \param sender An entity that is the source of trigger.
    void OnSecretRevealedTrigger(Entity* sender) const;

    //! Callback for trigger when playable heals character.
    //! \param sender An entity that is the source of trigger.
    void OnGiveHealTrigger(Entity* sender) const;

    //! Callback for trigger when character is healed.
    //! \param sender An entity that is the source of trigger.
    void OnTakeHealTrigger(Entity* sender) const;

    //! Callback for trigger when entity attacks target.
    //! \param sender An entity that is the source of trigger.
    void OnAttackTrigger(Entity* sender) const;

    //! Callback for trigger when entity is summoned.
    //! \param sender An entity that is the source of trigger.
    void OnSummonTrigger(Entity* sender) const;

    //! Callback for trigger after entity is summoned.
    //! \param sender An entity that is the source of trigger.
    void OnAfterSummonTrigger(Entity* sender) const;

    //! Callback for trigger when entity deals damage.
    //! \param sender An entity that is the source of trigger.
    void OnDealDamageTrigger(Entity* sender) const;

    //! Callback for trigger when entity is taken damage.
    //! \param sender An entity that is the source of trigger.
    void OnTakeDamageTrigger(Entity* sender) const;

    //! Callback for trigger when entity is targeted.
    //! \param sender An entity that is the source of trigger.
    void OnTargetTrigger(Entity* sender) const;

    //! Callback for trigger when minion is dead.
    //! \param sender An entity that is the source of trigger.
    void OnDeathTrigger(Entity* sender) const;

    //! Callback for trigger when hero uses power.
    //! \param sender An entity that is the source of trigger.
    void OnUseHeroPowerTrigger(Entity* sender) const;

    std::function<void(Entity*)> startTurnTrigger;
    std::function<void(Entity*)> endTurnTrigger;
    std::function<void(Entity*)> playCardTrigger;
    std::function<void(Entity*)> playMinionTrigger;
    std::function<void(Entity*)> afterPlayMinionTrigger;
    std::function<void(Entity*)> castSpellTrigger;
    std::function<void(Entity*)> afterCastTrigger;
    std::function<void(Entity*)> secretRevealedTrigger;
    std::function<void(Entity*)> giveHealTrigger;
    std::function<void(Entity*)> takeHealTrigger;
    std::function<void(Entity*)> attackTrigger;
    std::function<void(Entity*)> summonTrigger;
    std::function<void(Entity*)> afterSummonTrigger;
    std::function<void(Entity*)> dealDamageTrigger;
    std::function<void(Entity*)> takeDamageTrigger;
    std::function<void(Entity*)> targetTrigger;
    std::function<void(Entity*)> deathTrigger;
    std::function<void(Entity*)> useHeroPowerTrigger;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_MANAGER_HPP
