// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_MULTI_TRIGGER_HPP
#define ROSETTASTONE_PLAYMODE_MULTI_TRIGGER_HPP

#include <Rosetta/PlayMode/Triggers/Trigger.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief MultiTrigger class.
//!
//! This class stores a list of trigger to support in a turn based cards.
//! e.g. Dragon Soul, Chenvaala.
//!
class MultiTrigger : public Trigger
{
 public:
    //! Constructs multi trigger with given \p triggers.
    //! \param triggers A list of trigger.
    explicit MultiTrigger(std::vector<std::shared_ptr<Trigger>> triggers);

    //! Constructs trigger with given \p triggers, \p prototype and \p owner.
    //! \param triggers A list of trigger.
    //! \param prototype The multi trigger for prototype.
    //! \param owner The owner of multi trigger.
    MultiTrigger(std::vector<std::shared_ptr<Trigger>> triggers,
                 const MultiTrigger& prototype, Entity& owner);

    //! Creates a new instance of MultiTrigger object in source's game.
    //! \param source The source of trigger.
    //! \param activation The activation of trigger.
    //! \param cloning The flag to indicate that it is cloned.
    //! \param isMulti The flag to indicate that it is multi trigger.
    //! \return A new instance of MultiTrigger object.
    std::shared_ptr<Trigger> Activate(
        Playable* source,
        TriggerActivation activation = TriggerActivation::PLAY,
        bool cloning = false, [[maybe_unused]] bool isMulti = false) override;

    //! Removes this object from game and unsubscribe from the related event.
    void Remove() override;

    std::vector<std::shared_ptr<Trigger>> m_triggers;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_MULTI_TRIGGER_HPP
