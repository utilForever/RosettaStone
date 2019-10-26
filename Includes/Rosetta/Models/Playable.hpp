// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYABLE_HPP
#define ROSETTASTONE_PLAYABLE_HPP

#include <Rosetta/Models/Entity.hpp>

#include <array>

namespace RosettaStone
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
    //! Constructs entity with given \p _player, \p _card and \p _tags.
    //! \param _player The player.
    //! \param _card The card.
    //! \param _tags The game tags.
    Playable(Player* _player, Card* _card, std::map<GameTag, int> _tags);

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

    //! Resets the value of the cost.
    void ResetCost();

    //! Destroys entity.
    virtual void Destroy();

    //! Activates the task.
    //! \param type The type of power.
    //! \param target The target.
    //! \param chooseOne The index of chosen card from two cards.
    //! \param chooseBase The base card to apply card effect.
    void ActivateTask(PowerType type, Character* target = nullptr,
                      int chooseOne = 0, Playable* chooseBase = nullptr);

    CostManager* costManager = nullptr;
    IAura* onGoingEffect = nullptr;
    Trigger* activatedTrigger = nullptr;

    std::array<Playable*, 2> chooseOneCard{};

    int orderOfPlay = 0;
    bool isDestroyed = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_PLAYABLE_HPP