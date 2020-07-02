// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_TRIGGER_HPP
#define ROSETTASTONE_BATTLEGROUNDS_TRIGGER_HPP

#include <Rosetta/Battlegrounds/Conditions/SelfCondition.hpp>
#include <Rosetta/Battlegrounds/Managers/TriggerEventHandler.hpp>
#include <Rosetta/Battlegrounds/Tasks/TaskType.hpp>
#include <Rosetta/Common/Enums/TriggerEnums.hpp>

#include <vector>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Trigger class.
//!
//! This class represents triggered effects that are effects that activate in
//! response to specific events.
//!
class Trigger
{
 public:
    //! Default constructor.
    Trigger() = default;

    //! Constructs trigger with given \p type.
    //! \param type The trigger type.
    explicit Trigger(TriggerType type);

    //! Constructs trigger with given \p prototype and \p owner.
    //! \param prototype The trigger for prototype.
    //! \param owner The owner of trigger.
    Trigger(Trigger& prototype, Minion& owner);

    //! Sets the value of trigger source.
    //! \param val The value of trigger source.
    void SetTriggerSource(TriggerSource val);

    //! Sets a list of tasks to run.
    //! \param tasks A list of tasks to run.
    void SetTasks(std::vector<TaskType> tasks);

    //! Sets the condition of the trigger.
    //! \param condition the condition of the trigger.
    void SetCondition(SelfCondition&& condition);

    //! Creates a new instance of Trigger object in source's game.
    //! \param source The source of trigger.
    //! \param activation The activation of trigger.
    //! \param cloning The flag to indicate that it is cloned.
    //! \return A new instance of Trigger object.
    void Activate(Player& player, Minion& source,
                  TriggerActivation activation = TriggerActivation::PLAY,
                  bool cloning = false);

 private:
    //! Processes trigger to apply the effect.
    //! \param source The source of trigger.
    void Process(Minion& source);

    TriggerType m_triggerType = TriggerType::NONE;
    TriggerActivation m_triggerActivation = TriggerActivation::PLAY;
    TriggerSource m_triggerSource = TriggerSource::NONE;

    std::vector<TaskType> m_tasks;
    SelfCondition m_condition;

    TriggerEventHandler handler;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_TRIGGER_HPP
