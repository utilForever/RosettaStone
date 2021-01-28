// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DiscardTask.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
DiscardTask::DiscardTask(int amount, DiscardType discardType, bool saveCard)
    : m_amount(amount), m_discardType(discardType), m_saveCard(saveCard)
{
    // Do nothing
}

TaskStatus DiscardTask::Impl(Player* player)
{
    std::vector<Playable*> handCards = player->GetHandZone()->GetAll();

    switch (m_discardType)
    {
        case DiscardType::DEFAULT:
            std::shuffle(handCards.begin(), handCards.end(),
                         Random::get_engine());
            break;
        case DiscardType::LOWEST_COST:
            std::sort(handCards.begin(), handCards.end(),
                      [](const Playable* card1, const Playable* card2) {
                          return card1->GetCost() < card2->GetCost();
                      });
            break;
        case DiscardType::HIGHEST_COST:

            std::sort(handCards.begin(), handCards.end(),
                      [](const Playable* card1, const Playable* card2) {
                          return card1->GetCost() > card2->GetCost();
                      });
            break;
    }

    const int handSize = static_cast<int>(handCards.size());

    for (int i = 0; i < m_amount; ++i)
    {
        if (i >= handSize)
        {
            break;
        }

        player->game->taskQueue.StartEvent();

        player->game->triggerManager.OnDiscardTrigger(handCards[i]);

        player->GetHandZone()->Remove(handCards[i]);
        player->GetGraveyardZone()->Add(handCards[i]);

        if (m_amount == 1 && m_saveCard == true)
        {
            m_source->SetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1,
                                 handCards[i]->GetGameTag(GameTag::ENTITY_ID));
        }

        player->game->ProcessTasks();
        player->game->taskQueue.EndEvent();
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DiscardTask::CloneImpl()
{
    return std::make_unique<DiscardTask>(m_amount, m_discardType, m_saveCard);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
