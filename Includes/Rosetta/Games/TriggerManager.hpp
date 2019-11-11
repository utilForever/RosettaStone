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
class Player;

//!
//! \brief TriggerManager class.
//!
//! This class monitors trigger and invokes method when a trigger is activated.
//!
class TriggerManager
{
 public:
    //! Callback for trigger when player's turn is started.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnStartTurnTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when player's turn is ended.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnEndTurnTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when player plays a card.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnPlayCardTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when player plays a minion.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnPlayMinionTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger after player plays a minion.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnAfterPlayMinionTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when player plays a spell card.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnCastSpellTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger after player plays a spell card.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnAfterCastTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when entity is healed.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnHealTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when entity attacks target.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnAttackTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when entity is summoned.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnSummonTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger after entity is summoned.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnAfterSummonTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when entity deals damage.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnDealDamageTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when entity is taken damage.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnTakeDamageTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when entity is targeted.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnTargetTrigger(Player* player, Entity* sender) const;

    //! Callback for trigger when minion is dead.
    //! \param player A player to execute trigger.
    //! \param sender An entity that is the source of trigger.
    void OnDeathTrigger(Player* player, Entity* sender) const;

    std::function<void(Player*, Entity*)> startTurnTrigger;
    std::function<void(Player*, Entity*)> endTurnTrigger;
    std::function<void(Player*, Entity*)> playCardTrigger;
    std::function<void(Player*, Entity*)> playMinionTrigger;
    std::function<void(Player*, Entity*)> afterPlayMinionTrigger;
    std::function<void(Player*, Entity*)> castSpellTrigger;
    std::function<void(Player*, Entity*)> afterCastTrigger;
    std::function<void(Player*, Entity*)> healTrigger;
    std::function<void(Player*, Entity*)> attackTrigger;
    std::function<void(Player*, Entity*)> summonTrigger;
    std::function<void(Player*, Entity*)> afterSummonTrigger;
    std::function<void(Player*, Entity*)> dealDamageTrigger;
    std::function<void(Player*, Entity*)> takeDamageTrigger;
    std::function<void(Player*, Entity*)> targetTrigger;
    std::function<void(Player*, Entity*)> deathTrigger;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_TRIGGER_MANAGER_HPP
