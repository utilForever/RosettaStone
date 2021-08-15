// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_QUEST_PROGRESS_TASK_HPP
#define ROSETTASTONE_PLAYMODE_QUEST_PROGRESS_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
//! The type of quest progress.
enum class ProgressType
{
    DEFAULT,     //!< Increases progress count when the trigger is called.
    SPEND_MANA,  //!< Increases progress count when the player spends mana.
    SPEND_MANA_ON_SPELLS,   //!< Increases progress count when the player spends
                            //!< mana on spells.
    PLAY_ELEMENTAL_MINONS,  //!< Increases progress count when the player plays
                            //!< an elemental minion in this turn.
    GAIN_ATTACK,     //!< Increases progress count when the hero gains attack.
    RESTORE_HEALTH,  //!< Increases progress count when the hero or friendly
                     //!< minion(s) restores health.
};

//!
//! \brief QuestProgressTask class.
//!
//! This class represents the task for processing quest progress.
//!
class QuestProgressTask : public ITask
{
 public:
    //! Constructs task with given \p questRewardID.
    //! \param questRewardID The card ID that is a reward of the quest.
    explicit QuestProgressTask(const std::string& questRewardID);

    //! Constructs task with given \p questRewardID and \p progressType.
    //! \param questRewardID The card ID that is a reward of the quest.
    //! \param progressType The type of quest progress.
    explicit QuestProgressTask(const std::string& questRewardID,
                               ProgressType progressType);

    //! Constructs task with given \p rewardTasks, \p progressType
    //! and \p nextQuestID.
    //! \param rewardTasks A list of tasks to run that is a reward of the quest.
    //! \param progressType The type of quest progress.
    //! \param nextQuestID The card ID that is next quest for
    //! keyword 'Questline'.
    explicit QuestProgressTask(
        std::vector<std::shared_ptr<ITask>> rewardTasks,
        ProgressType progressType = ProgressType::DEFAULT,
        std::string&& nextQuestID = "");

    //! Constructs task with given various parameters.
    //! \param questRewardID The card ID that is a reward of the quest.
    //! \param progressType The type of quest progress.
    //! \param rewardTasks A list of tasks to run that is a reward of the quest.
    //! \param nextQuestID The card ID that is next quest for
    //! keyword 'Questline'.
    explicit QuestProgressTask(const std::string& questRewardID,
                               const std::string& nextQuestID,
                               ProgressType progressType,
                               std::vector<std::shared_ptr<ITask>> rewardTasks);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    Card* m_questRewardCard = nullptr;
    Card* m_nextQuestCard = nullptr;
    ProgressType m_progressType = ProgressType::DEFAULT;
    std::vector<std::shared_ptr<ITask>> m_tasks;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_QUEST_PROGRESS_TASK_HPP
