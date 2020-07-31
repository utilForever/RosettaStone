// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_MINION_HPP
#define ROSETTASTONE_BATTLEGROUNDS_MINION_HPP

#include <Rosetta/Battlegrounds/Cards/Card.hpp>
#include <Rosetta/Common/Enums/TaskEnums.hpp>

#include <initializer_list>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Minion class.
//!
//! Minions are persistent creatures on the battlefield that will fight for
//! their hero. Minion cards can be recognized by their Attack (a number
//! displayed on a yellow sword, in the bottom left corner) and Health (a number
//! displayed on a red blood drop, in the bottom right corner).
//!
class Minion
{
 public:
    //! Default constructor.
    Minion() = default;

    //! Constructs Minion instance with given \p card and \p poolIdx.
    //! \param card A card that contains the minion data.
    //! \param poolIdx The index of minion pool.
    explicit Minion(Card card, int poolIdx = -1);

    //! Returns the value of index.
    //! \return The value of index.
    int GetIndex() const;

    //! Sets the value of index.
    //! \param index The value of index.
    void SetIndex(int index);

    //! Returns the value of pool index.
    //! \return The value of pool index.
    int GetPoolIndex() const;

    //! Returns the value of name.
    //! \return The value of name.
    std::string_view GetName() const;

    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    int GetGameTag(GameTag tag) const;

    //! Sets the value of game tag.
    //! \param tag The game tag to set.
    //! \param value The value of game tag to set.
    void SetGameTag(GameTag tag, int value);

    //! Returns the value of race.
    //! \return The value of race.
    Race GetRace() const;

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
    //! \param pos The value of zone position.
    void SetZonePosition(int pos);

    //! Returns the value of last field position.
    //! \return The value of last field position.
    int GetLastFieldPos() const;

    //! Sets the value of last field position.
    //! \param pos The value of last field position.
    void SetLastFieldPos(int pos);

    //! Returns the value of tier.
    //! \return The value of tier.
    int GetTier() const;

    //! Returns the value of attack.
    //! \return The value of attack.
    int GetAttack() const;

    //! Sets the value of attack.
    //! \param val The value of attack to set.
    void SetAttack(int val);

    //! Returns the value of health.
    //! \return The value of health.
    int GetHealth() const;

    //! Sets the value of health.
    //! \param val The value of health to set.
    void SetHealth(int val);

    //! Returns the flag that indicates whether it has deathrattle.
    //! \return The flag that indicates whether it has deathrattle.
    bool HasDeathrattle() const;

    //! Returns the flag that indicates whether it has taunt.
    //! \return The flag that indicates whether it has taunt.
    bool HasTaunt() const;

    //! Returns the flag that indicates whether it has divine shield.
    //! \return The flag that indicates whether it has divine shield.
    bool HasDivineShield() const;

    //! Takes damage from a certain other minion.
    //! \param source A minion to give damage.
    void TakeDamage(Minion& source);

    //! Takes damage to the minion.
    //! \param amount The amount of damage.
    void TakeDamage(int amount);

    //! Returns the flag that indicates whether it is destroyed.
    //! \return The flag that indicates whether it is destroyed.
    bool IsDestroyed() const;

    //! Gets a value indicating whether source entity is playable by card
    //! requirements. Static requirements are checked.
    //! \param player The owner of the minion.
    //! \return true if it is playable by card requirements, false otherwise.
    bool IsPlayableByCardReq(Player& player) const;

    //! Gets whether the current field has any valid play targets
    //! for this playable.
    //! \param player The owner of the minion.
    //! \return true if the current field has any valid play targets,
    //! false otherwise.
    bool HasAnyValidPlayTargets(Player& player) const;

    //! Determines whether the specified character is a valid target.
    //! \param player The owner of the minion.
    //! \param targetIdx The index of proposed target.
    //! \return true if the specified target is valid, false otherwise.
    bool IsValidPlayTarget(Player& player, int targetIdx);

    //! Checks the targeting type of a card.
    //! \param target The proposed target.
    //! \return true if the targeting type is valid, false otherwise.
    bool CheckTargetingType(Minion& target);

    //! Activates the trigger.
    //! \param type The type of trigger.
    //! \param source The source of trigger.
    void ActivateTrigger(TriggerType type, Minion& source);

    //! Activates the task.
    //! \param type The type of power.
    //! \param player The owner of the minion.
    void ActivateTask(PowerType type, Player& player);

    //! Activates the task.
    //! \param type The type of power.
    //! \param player The owner of the minion.
    //! \param target The target.
    void ActivateTask(PowerType type, Player& player, Minion& target);

    Trigger activatedTrigger;

    std::function<Player&()> getPlayerCallback;

 private:
    //! Gets a list of tasks according to the power type.
    //! \param type The type of power.
    //! \return A list of tasks according to the power type.
    std::vector<TaskType> GetTasks(PowerType type);

    Card m_card;
    int m_index = -1;
    int m_poolIdx = -1;

    ZoneType m_zoneType = ZoneType::INVALID;
    int m_zonePos = -1;
    int m_lastFieldPos = -1;

    int m_attack = 0;
    int m_health = 0;

    bool m_hasDeathrattle = false;
    bool m_hasTaunt = false;
    bool m_hasDivineShield = false;
    bool m_isDestroyed = false;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_MINION_HPP
