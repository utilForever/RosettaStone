// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_TRIGGER_HPP
#define ROSETTASTONE_TRIGGER_HPP

#include <Rosetta/Enums/TriggerEnums.hpp>

namespace RosettaStone
{
class Entity;
class Player;
class ITask;

//!
//! \brief Trigger class.
//!
//! This class represents triggered effects that are effects that activate in
//! response to specific events.
//!
class Trigger
{
 public:
    //! Constructs trigger with given \p type.
    //! \param type The trigger type.
    explicit Trigger(TriggerType type);

    //! Constructs trigger with given \p prototype and \p owner.
    //! \param prototype An trigger for prototype.
    //! \param owner An owner of trigger.
    Trigger(Trigger& prototype, Entity& owner);

    //! Activates trigger to battlefield.
    //! \param source An source of trigger.
    void Activate(Entity& source);

    //! Removes this object from game and unsubscribe from the related event.
    void Remove();

    TriggerSource triggerSource = TriggerSource::NONE;

    ITask* singleTask = nullptr;

 private:
    //! Processes trigger to apply the effect.
    //! \param player A pointer to player.
    //! \param source A pointer to source of trigger.
    void Process(Player* player, Entity* source);

    //! Internal method of Process().
    //! \param player A pointer to player.
    //! \param source A pointer to source of trigger.
    void ProcessInternal(Player* player, Entity* source);

    //! Validates triggers related to the current sequence at once before the
    //! sequence starts.
    //! \param player A pointer to player.
    //! \param source A pointer to source of trigger.
    void Validate(Player* player, Entity* source);

    TriggerType m_triggerType = TriggerType::NONE;
    SequenceType m_sequenceType = SequenceType::NONE;
    bool m_isValidated = false;

    Entity* m_owner = nullptr;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_EFFECT_HPP
