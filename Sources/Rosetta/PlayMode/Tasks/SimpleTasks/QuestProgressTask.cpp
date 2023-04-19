// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Spell.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/QuestProgressTask.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
QuestProgressTask::QuestProgressTask(const std::string& questRewardID)
    : m_questRewardCard(Cards::FindCardByID(questRewardID))
{
    // Do nothing
}

QuestProgressTask::QuestProgressTask(const std::string& questRewardID,
                                     ProgressType progressType)
    : m_questRewardCard(Cards::FindCardByID(questRewardID)),
      m_progressType(progressType)
{
    // Do nothing
}

QuestProgressTask::QuestProgressTask(
    std::vector<std::shared_ptr<ITask>> rewardTasks, ProgressType progressType,
    std::string&& nextQuestID)
    : m_nextQuestCard(Cards::FindCardByID(nextQuestID)),
      m_progressType(progressType),
      m_tasks(std::move(rewardTasks))
{
    // Do nothing
}

QuestProgressTask::QuestProgressTask(
    const std::string& questRewardID, const std::string& nextQuestID,
    ProgressType progressType, std::vector<std::shared_ptr<ITask>> rewardTasks)
    : m_questRewardCard(Cards::FindCardByID(questRewardID)),
      m_nextQuestCard(Cards::FindCardByID(nextQuestID)),
      m_progressType(progressType),
      m_tasks(std::move(rewardTasks))
{
    // Do nothing
}

TaskStatus QuestProgressTask::Impl(Player* player)
{
    if (player->GetGameTag(GameTag::CAST_RANDOM_SPELLS) == 1)
    {
        return TaskStatus::STOP;
    }

    const auto spell = dynamic_cast<Spell*>(m_source);

    if (!spell)
    {
        return TaskStatus::STOP;
    }

    switch (m_progressType)
    {
        case ProgressType::DEFAULT:
            spell->IncreaseQuestProgress();
            break;
        case ProgressType::SPEND_MANA:
        case ProgressType::SPEND_MANA_ON_SPELLS:
        {
            const auto source = player->game->currentEventData->eventSource;
            const auto cost = source->GetCost();

            for (int i = 0; i < cost; ++i)
            {
                spell->IncreaseQuestProgress();
            }
            break;
        }
        case ProgressType::PLAY_ELEMENTAL_MINONS:
            if (player->GetNumElementalPlayedThisTurn() == 1)
            {
                spell->IncreaseQuestProgress();
            }
            break;
        case ProgressType::RESTORE_HEALTH:
        case ProgressType::GAIN_ATTACK:
            const int amount = player->game->currentEventData->eventNumber;

            for (int i = 0; i < amount; ++i)
            {
                spell->IncreaseQuestProgress();
            }
            break;
    }

    if (spell->GetQuestProgress() >= spell->GetQuestProgressTotal())
    {
        if (!m_questRewardCard->id.empty())
        {
            Playable* reward = Entity::GetFromCard(player, m_questRewardCard);

            // Reward card is hero power or minion
            if (const auto heroPower = dynamic_cast<HeroPower*>(reward);
                heroPower)
            {
                delete player->GetHero()->heroPower;
                player->GetHero()->heroPower = heroPower;

                // Process aura
                if (heroPower->card->power.GetAura())
                {
                    heroPower->card->power.GetAura()->Activate(heroPower);
                }

                // Process trigger
                if (heroPower->card->power.GetTrigger())
                {
                    heroPower->card->power.GetTrigger()->Activate(heroPower);
                }
            }
            else
            {
                Generic::AddCardToHand(player, reward);
            }

            spell->SetGameTag(GameTag::REVEALED, 1);

            // Move quest to graveyard
            player->GetSecretZone()->Remove(spell);
            player->GetSecretZone()->quest = nullptr;
            player->GetGraveyardZone()->Add(spell);

            return TaskStatus::COMPLETE;
        }

        if (!m_tasks.empty())
        {
            for (const auto& task : m_tasks)
            {
                const std::unique_ptr<ITask> clonedTask = task->Clone();

                clonedTask->SetPlayer(player);
                clonedTask->SetSource(m_source);
                clonedTask->SetTarget(m_target);

                clonedTask->Run();
            }

            spell->SetGameTag(GameTag::REVEALED, 1);

            // Move quest to graveyard
            player->GetSecretZone()->Remove(spell);
            player->GetSecretZone()->quest = nullptr;
            player->GetGraveyardZone()->Add(spell);

            // Set next quest for keyword 'Questline'
            if (!m_nextQuestCard->id.empty())
            {
                Playable* nextQuest =
                    Entity::GetFromCard(player, m_nextQuestCard);

                // Process trigger
                if (nextQuest->card->power.GetTrigger())
                {
                    nextQuest->card->power.GetTrigger()->Activate(nextQuest);
                }
                player->GetSecretZone()->Add(nextQuest);
            }

            return TaskStatus::COMPLETE;
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> QuestProgressTask::CloneImpl()
{
    const std::string questRewardCardID =
        m_questRewardCard ? m_questRewardCard->id : "";
    const std::string nextQuestCardID =
        m_nextQuestCard ? m_nextQuestCard->id : "";
    return std::make_unique<QuestProgressTask>(
        questRewardCardID, nextQuestCardID, m_progressType, m_tasks);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
