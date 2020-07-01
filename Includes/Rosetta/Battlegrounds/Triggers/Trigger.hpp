// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_TRIGGER_HPP
#define ROSETTASTONE_BATTLEGROUNDS_TRIGGER_HPP

#include <Rosetta/Battlegrounds/Conditions/SelfCondition.hpp>
#include <Rosetta/Battlegrounds/Tasks/TaskType.hpp>
#include <Rosetta/Common/Enums/TriggerEnums.hpp>

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

    //! Sets the value of trigger source.
    //! \param val The value of trigger source.
    void SetTriggerSource(TriggerSource val);

    //! Sets a list of tasks to run.
    //! \param tasks A list of tasks to run.
    void SetTasks(std::vector<TaskType> tasks);

    //! Sets the condition of the trigger.
    //! \param condition the condition of the trigger.
    void SetCondition(SelfCondition&& condition);

 private:
    TriggerType m_triggerType = TriggerType::NONE;
    TriggerSource m_triggerSource = TriggerSource::NONE;

    std::vector<TaskType> m_tasks;
    SelfCondition m_condition;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_TRIGGER_HPP
