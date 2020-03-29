// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Tasks/SimpleTasks/DestroyAllTask.hpp>
#include <Rosetta/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>

namespace RosettaStone::SimpleTasks
{
DestroyAllTask::DestroyAllTask(EntityType entityType) : ITask(entityType)
{
    // Do nothing
}

TaskStatus DestroyAllTask::Impl(Player* player)
{
    auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);

    for (auto& playable : playables)
    {
        std::string name = playable->card->name;

        // Field
        for (auto& minion : player->GetFieldZone()->GetAll())
        {
            if (minion->card->name == name)
            {
                minion->Destroy();
            }
        }

        // Enemy Field
        for (auto& minion : player->opponent->GetFieldZone()->GetAll())
        {
            if (minion->card->name == name)
            {
                minion->Destroy();
            }
        }

        // Hand
        for (auto& card : player->GetHandZone()->GetAll())
        {
            if (card->card->name == name)
            {
                card->player->GetHandZone()->Remove(card);
                card->player->GetGraveyardZone()->Add(card);
            }
        }

        // Enemy Hand
        for (auto& card : player->opponent->GetHandZone()->GetAll())
        {
            if (card->card->name == name)
            {
                card->player->GetHandZone()->Remove(card);
                card->player->GetGraveyardZone()->Add(card);
            }
        }

        // Deck
        for (auto& card : player->GetDeckZone()->GetAll())
        {
            if (card->card->name == name)
            {
                card->player->GetDeckZone()->Remove(card);
                card->player->GetGraveyardZone()->Add(card);
            }
        }

        // Enemy Deck
        for (auto& card : player->opponent->GetDeckZone()->GetAll())
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
}  // namespace RosettaStone::SimpleTasks
