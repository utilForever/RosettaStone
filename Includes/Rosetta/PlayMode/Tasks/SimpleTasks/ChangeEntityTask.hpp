// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CHANGE_ENTITY_TASK_HPP
#define ROSETTASTONE_PLAYMODE_CHANGE_ENTITY_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//!
//! \brief ChangeEntityTask class.
//!
//! This class represents the task for transforming the given type of entities
//! into random cards satisfying the criteria.
//!
class ChangeEntityTask : public ITask
{
 public:
    //! Constructs task with given various arguments.
    //! \param entityType The entity type to change.
    //! \param protoType The another entity type to change.
    //! \param cardType The type of card to filter.
    //! \param cardClass The class of card to filter.
    //! \param race The race of card to filter.
    //! \param rarity The rarity of card to filter.
    //! \param cardID The card ID.
    //! \param removeEnchantments The flag that removes any applied enchantments
    //! during this transformation.
    //! \param useRandomCard The flag that indicates it uses random card.
    explicit ChangeEntityTask(
        EntityType entityType, EntityType protoType, CardType cardType,
        CardClass cardClass = CardClass::INVALID, Race race = Race::INVALID,
        Rarity rarity = Rarity::INVALID, const std::string& cardID = "",
        bool removeEnchantments = false, bool useRandomCard = false);

    //! Constructs task with given various arguments.
    //! \param entityType The entity type to change.
    //! \param cardType The type of card to filter.
    //! \param cardClass The class of card to filter.
    //! \param race The race of card to filter.
    //! \param rarity The rarity of card to filter.
    //! \param removeEnchantments The flag that removes any applied enchantments
    //! during this transformation.
    explicit ChangeEntityTask(EntityType entityType, CardType cardType,
                              CardClass cardClass = CardClass::INVALID,
                              Race race = Race::INVALID,
                              Rarity rarity = Rarity::INVALID,
                              bool removeEnchantments = false);

    //! Constructs task with given \p cardID and \p entityType.
    //! \param cardID The card ID.
    //! \param entityType The entity type to change.
    explicit ChangeEntityTask(const std::string& cardID,
                              EntityType entityType = EntityType::SOURCE);

    //! Constructs task with given \p sourceType and \p protoType.
    //! \param sourceType The entity type to change.
    //! \param protoType The another entity type to change.
    explicit ChangeEntityTask(EntityType sourceType, EntityType protoType);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    EntityType m_protoType = EntityType::INVALID;
    CardType m_cardType = CardType::INVALID;
    CardClass m_cardClass = CardClass::INVALID;
    Race m_race = Race::INVALID;
    Rarity m_rarity = Rarity::INVALID;
    Card* m_card = nullptr;
    bool m_removeEnchantments = false;
    bool m_useRandomCard = false;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_CHANGE_ENTITY_TASK_HPP
