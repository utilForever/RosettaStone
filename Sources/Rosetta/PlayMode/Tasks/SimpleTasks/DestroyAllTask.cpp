// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Tasks/SimpleTasks/DestroyAllTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DestroyAllTask::DestroyAllTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus DestroyAllTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        std::string name = playable->card->name;

        // Field
        for (const auto& minion : player->GetFieldZone()->GetAll())
        {
            if (minion->card->name == name)
            {
                minion->Destroy();
            }
        }

        // Enemy Field
        for (const auto& minion : player->opponent->GetFieldZone()->GetAll())
        {
            if (minion->card->name == name)
            {
                minion->Destroy();
            }
        }

        // Hand
        for (const auto& card : player->GetHandZone()->GetAll())
        {
            if (card->card->name == name)
            {
                card->player->GetHandZone()->Remove(card);
                card->player->GetGraveyardZone()->Add(card);
            }
        }

        // Enemy Hand
        for (const auto& card : player->opponent->GetHandZone()->GetAll())
        {
            if (card->card->name == name)
            {
                card->player->GetHandZone()->Remove(card);
                card->player->GetGraveyardZone()->Add(card);
            }
        }

        // Deck
        for (const auto& card : player->GetDeckZone()->GetAll())
        {
            if (card->card->name == name)
            {
                card->player->GetDeckZone()->Remove(card);
                card->player->GetGraveyardZone()->Add(card);
            }
        }

        // Enemy Deck
        for (const auto& card : player->opponent->GetDeckZone()->GetAll())
        {
            if (card->card->name == name)
            {
                card->player->GetDeckZone()->Remove(card);
                card->player->GetGraveyardZone()->Add(card);
            }
        }

        // Hero
        if (player->GetHero()->card->name == name)
        {
            player->GetHero()->Destroy();
        }

        // Enemy Hero
        if (player->opponent->GetHero()->card->name == name)
        {
            player->opponent->GetHero()->Destroy();
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DestroyAllTask::CloneImpl()
{
    return std::make_unique<DestroyAllTask>(m_entityType);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
