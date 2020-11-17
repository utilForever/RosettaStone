// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_PLAYABLE_HPP
#define ROSETTASTONE_PLAYMODE_PLAYABLE_HPP

#include <Rosetta/PlayMode/Models/Entity.hpp>

#include <array>

namespace RosettaStone::PlayMode
{
class Character;

//!
//! \brief Playable class.
//!
//! This class is an entity which can be played from hand zone into play zone.
//! In other words, the entity can be played.
//!
class Playable : public Entity
{
 public:
    //! Constructs entity with given \p _player, \p _card, \p _tags and \p _id.
    //! \param _player The player.
    //! \param _card The card.
    //! \param _tags The game tags.
    //! \param _id The ID.
    Playable(Player* _player, Card* _card, std::map<GameTag, int> _tags,
             int _id);

    //! Destructor.
    virtual ~Playable();

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

    //! Returns the flag that indicates whether it is exhausted.
    //! \return The flag that indicates whether it is exhausted.
    bool IsExhausted() const;

    //! Sets the flag that indicates whether it is exhausted.
    //! \param exhausted The flag that indicates whether it is exhausted.
    void SetExhausted(bool exhausted);

    //! Returns the flag that indicates whether it has combo.
    //! \return The flag that indicates whether it has combo.
    bool HasCombo() const;

    //! Returns the flag that indicates whether it has overload.
    //! \return The flag that indicates whether it has overload.
    bool HasOverload() const;

    //! Returns the value of overload.
    //! \return The value of overload.
    int GetOverload() const;

    //! Returns the flag that indicates whether it has battlecry.
    //! \return The flag that indicates whether it has battlecry.
    bool HasBattlecry() const;

    //! Returns the flag that indicates whether it has deathrattle.
    //! \return The flag that indicates whether it has deathrattle.
    bool HasDeathrattle() const;

    //! Returns the flag that indicates whether it has outcast.
    //! \return The flag that indicates whether it has outcast.
    bool HasOutcast() const;

    //! Returns the flag that indicates whether it has choose one.
    //! \return The flag that indicates whether it has choose one.
    bool HasChooseOne() const;

    //! Returns the flag that indicates whether it has lifesteal.
    //! \return The flag that indicates whether it has lifesteal.
    virtual bool HasLifesteal() const;

    //! Returns the flag that indicates whether it is echo.
    //! \return The flag that indicates whether it is echo.
    bool IsEcho() const;

    //! Returns the flag that indicates whether it has corrupt.
    //! \return The flag that indicates whether it has corrupt.
    bool HasCorrupt() const;

    //! Resets the value of the cost.
    void ResetCost();

    //! Destroys entity.
    virtual void Destroy();

    //! Gets a value indicating whether this entity is playable. Some entities
    //! require specific requirements before they can be played. This method
    //! will process the requirements and produce a result for the current state
    //! of the game.
    //! \return true if this entity is playable, false otherwise.
    bool IsPlayable();

    //! Calculates if a target is valid by testing the game state for each
    //! hardcoded requirement.
    //! \param card A card to check targeting requirements.
    //! \param target The proposed target.
    //! \return true if the proposed target is valid, false otherwise.
    virtual bool TargetingRequirements(Card* card, Character* target) const;

    //! Gets a value indicating whether source entity is playable by player.
    //! Dynamic requirements are checked, eg: If a spell costs health instead of
    //! mana, this method will return false if the health cost would be higher
    //! than the available health.
    //! \return true if it is playable by player, false otherwise.
    virtual bool IsPlayableByPlayer();

    //! Gets a value indicating whether source entity is playable by card
    //! requirements. Static requirements are checked.
    //! \return true if it is playable by card requirements, false otherwise.
    bool IsPlayableByCardReq() const;

    //! Gets the valid play targets.
    //! This method defaults to targeting in the context of spells/hero powers.
    //! \return A list of valid play targets.
    std::vector<Character*> GetValidPlayTargets() const;

    //! Gets a random valid target in valid play targets.
    //! \return A randomly selected valid target.
    Character* GetRandomValidTarget();

    //! Determines whether the specified character is a valid target.
    //! \param target The proposed target.
    //! \return true if the specified target is valid, false otherwise.
    bool IsValidPlayTarget(Character* target);

    //! Gets whether the current field has any valid play targets
    //! for this playable.
    //! \param card A card to check the current field has any valid play
    //! targets.
    //! \return true if the current field has any valid play targets,
    //! false otherwise.
    bool HasAnyValidPlayTargets(Card* card) const;

    //! Checks the targeting type of a card.
    //! \param card A card to check the targeting type.
    //! \param target The proposed target.
    //! \return true if the targeting type is valid, false otherwise.
    bool CheckTargetingType(Card* card, Character* target);

    //! Activates the task.
    //! \param type The type of power.
    //! \param target The target.
    //! \param chooseOne The index of chosen card from two cards.
    //! \param chooseBase The base card to apply card effect.
    void ActivateTask(PowerType type, Character* target = nullptr,
                      int chooseOne = 0, Playable* chooseBase = nullptr);

    CostManager* costManager = nullptr;
    IAura* ongoingEffect = nullptr;
    std::shared_ptr<Trigger> activatedTrigger;

    int orderOfPlay = 0;
    bool isDestroyed = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_PLAYABLE_HPP