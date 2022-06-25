// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_TRIGGER_HPP
#define ROSETTASTONE_PLAYMODE_TRIGGER_HPP

#include <Rosetta/Common/Enums/ConditionEnums.hpp>
#include <Rosetta/Common/Enums/TriggerEnums.hpp>
#include <Rosetta/PlayMode/Conditions/SelfCondition.hpp>
#include <Rosetta/PlayMode/Managers/TriggerEventHandler.hpp>

#include <memory>
#include <vector>

namespace RosettaStone::PlayMode
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
    Trigger(const Trigger& prototype, Entity& owner);

    //! Default virtual destructor.
    virtual ~Trigger() = default;

    //! Creates a new instance of Trigger object in source's game.
    //! \param source The source of trigger.
    //! \param activation The activation of trigger.
    //! \param cloning The flag to indicate that it is cloned.
    //! \param isMulti The flag to indicate that it is multi trigger.
    //! \return A new instance of Trigger object.
    virtual std::shared_ptr<Trigger> Activate(
        Playable* source,
        TriggerActivation activation = TriggerActivation::PLAY,
        bool cloning = false, bool isMulti = false);

    //! Removes this object from game and unsubscribe from the related event.
    virtual void Remove();

    //! Checks triggers related to the current Sequence at once before sequence
    //! starts.
    //! \param game The game.
    //! \param source The source entity.
    //! \param type The sequence type.
    static void ValidateTriggers(const Game* game, Entity* source,
                                 SequenceType type);

    TriggerActivation triggerActivation = TriggerActivation::PLAY;
    TriggerSource triggerSource = TriggerSource::NONE;

    std::vector<std::shared_ptr<ITask>> tasks;
    std::vector<std::shared_ptr<SelfCondition>> conditions;
    MultiCondLogic conditionLogic = MultiCondLogic::AND;

    TriggerEventHandler handler;

    int curTurn = 0;
    int lastTurn = 0;

    float percentage = 1.0f;

    bool eitherTurn = false;
    bool fastExecution = false;
    bool removeAfterTriggered = false;
    bool isMultiTrigger = false;

 protected:
    Playable* m_owner = nullptr;

 private:
    //! Processes trigger to apply the effect.
    //! \param source The source of trigger.
    void Process(Entity* source);

    //! Internal method of Process().
    //! \param source The source of trigger.
    void ProcessInternal(Entity* source);

    //! Processes a list of tasks.
    //! \param source The source of trigger.
    void ProcessTasks(Entity* source) const;

    //! Validates triggers related to the current sequence at once before the
    //! sequence starts.
    //! \param source The source of trigger.
    void Validate(Entity* source);

    TriggerType m_triggerType = TriggerType::NONE;
    SequenceType m_sequenceType = SequenceType::NONE;

    bool m_isRemoved = false;
    bool m_isValidated = false;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_TRIGGER_HPP
