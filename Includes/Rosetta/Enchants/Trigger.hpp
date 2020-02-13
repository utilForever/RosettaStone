// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_TRIGGER_HPP
#define ROSETTASTONE_TRIGGER_HPP

#include <Rosetta/Conditions/SelfCondition.hpp>
#include <Rosetta/Enums/TriggerEnums.hpp>
#include <Rosetta/Managers/TriggerEventHandler.hpp>

#include <memory>
#include <vector>

namespace RosettaStone
{
class Game;
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
    //! \param prototype The trigger for prototype.
    //! \param owner The owner of trigger.
    Trigger(Trigger& prototype, Entity& owner);

    //! Activates trigger to battlefield.
    //! \param source The source of trigger.
    //! \param activation The activation of trigger.
    //! \param cloning The flag to indicate that it is cloned.
    void Activate(Playable* source,
                  TriggerActivation activation = TriggerActivation::PLAY,
                  bool cloning = false);

    //! Removes this object from game and unsubscribe from the related event.
    void Remove() const;

    //! Checks triggers related to the current Sequence at once before sequence
    //! starts.
    //! \param game The game.
    //! \param source The source entity.
    //! \param type The sequence type.
    static void ValidateTriggers(Game* game, Entity* source, SequenceType type);

    TriggerSource triggerSource = TriggerSource::NONE;

    std::vector<std::shared_ptr<ITask>> tasks;
    std::shared_ptr<SelfCondition> condition;

    float percentage = 1.0f;
    bool eitherTurn = false;
    bool fastExecution = false;
    bool removeAfterTriggered = false;

 private:
    //! Processes trigger to apply the effect.
    //! \param source The source of trigger.
    void Process(Entity* source);

    //! Internal method of Process().
    //! \param source The source of trigger.
    void ProcessInternal(Entity* source);

    //! Validates triggers related to the current sequence at once before the
    //! sequence starts.
    //! \param source The source of trigger.
    void Validate(Entity* source);

    Playable* m_owner = nullptr;

    TriggerType m_triggerType = TriggerType::NONE;
    TriggerActivation m_triggerActivation = TriggerActivation::PLAY;
    SequenceType m_sequenceType = SequenceType::NONE;

    TriggerEventHandler m_handler;

    bool m_isValidated = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_EFFECT_HPP
