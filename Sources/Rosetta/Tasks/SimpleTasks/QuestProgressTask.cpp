// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Spell.hpp>
#include <Rosetta/Tasks/SimpleTasks/QuestProgressTask.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>

namespace RosettaStone::SimpleTasks
{
QuestProgressTask::QuestProgressTask(const std::string& questRewardID)
    : m_card(Cards::FindCardByID(questRewardID))
{
    // Do nothing
}

QuestProgressTask::QuestProgressTask(
    std::vector<std::shared_ptr<ITask>> rewardTasks, ProgressType progressType)
    : m_progressType(progressType), m_tasks(std::move(rewardTasks))
{
    // Do nothing
}

QuestProgressTask::QuestProgressTask(
    const std::string& questRewardID, ProgressType progressType,
    std::vector<std::shared_ptr<ITask>> rewardTasks)
    : m_card(Cards::FindCardByID(questRewardID)),
      m_progressType(progressType),
      m_tasks(std::move(rewardTasks))
{
    // Do nothing
}

TaskStatus QuestProgressTask::Impl(Player* player)
{
    auto spell = dynamic_cast<Spell*>(m_source);
    if (spell == nullptr)
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
    }

    if (spell->GetQuestProgress() >= spell->GetQuestProgressTotal())
    {
        if (!m_card->id.empty())
        {
            Playable* reward = Entity::GetFromCard(player, m_card);

            // Reward card is hero power or minion
            if (const auto heroPower = dynamic_cast<HeroPower*>(reward);
                heroPower)
            {
                delete player->GetHero()->heroPower;
                player->GetHero()->heroPower = heroPower;
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
            for (auto& task : m_tasks)
            {
                std::unique_ptr<ITask> clonedTask = task->Clone();

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

            return TaskStatus::COMPLETE;
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> QuestProgressTask::CloneImpl()
{
    const std::string cardID = m_card ? m_card->id : "";
    return std::make_unique<QuestProgressTask>(cardID, m_progressType, m_tasks);
}
}  // namespace RosettaStone::SimpleTasks
