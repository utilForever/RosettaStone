// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/TransformMinionTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
TransformMinionTask::TransformMinionTask(EntityType entityType, Race race,
                                         int costChange)
    : ITask(entityType), m_race(race), m_costChange(costChange)
{
    // Do nothing
}

TransformMinionTask::TransformMinionTask(EntityType entityType, Race race)
    : ITask(entityType), m_race(race)
{
    // Do nothing
}

TransformMinionTask::TransformMinionTask(EntityType entityType, int costChange)
    : ITask(entityType), m_costChange(costChange)
{
    // Do nothing
}

TaskStatus TransformMinionTask::Impl(Player* player)
{
    const auto playables =
        IncludeTask::GetEntities(m_entityType, player, m_source, m_target);
    const FormatType format = player->game->GetFormatType();
    std::vector<Card*> minionCards;

    if (format == FormatType::STANDARD)
    {
        for (auto& card : Cards::GetAllStandardCards())
        {
            if (card->GetCardType() == CardType::MINION)
            {
                minionCards.emplace_back(card);
            }
        }
    }
    else
    {
        for (auto& card : Cards::GetAllWildCards())
        {
            if (card->GetCardType() == CardType::MINION)
            {
                minionCards.emplace_back(card);
            }
        }
    }

    if (m_race != Race::INVALID)
    {
        std::vector<Card*> cards;

        for (auto& card : minionCards)
        {
            if (card->GetRace() == m_race || card->GetRace() == Race::ALL)
            {
                cards.emplace_back(card);
            }
        }

        for (auto& playable : playables)
        {
            const auto idx = Random::get<std::size_t>(0, cards.size() - 1);
            Generic::ChangeEntity(m_player, playable, cards[idx], true);
        }

        return TaskStatus::COMPLETE;
    }

    for (auto& playable : playables)
    {
        int newCost = playable->card->GetCost() + m_costChange;
        std::vector<Card*> cards;

        while (true)
        {
            for (auto& card : minionCards)
            {
                if (card->GetCost() == newCost)
                {
                    cards.emplace_back(card);
                }
            }

            if (!cards.empty())
            {
                break;
            }

            // NOTE: Cards that "transform a minion into a random one that
            // costs (1) more/less", like Evolve or Devolve, will now always
            // re-roll the minion, even if no minion exists in the
            // target-cost minion pool. The minion will be re-rolled at the
            // nearest possible cost. For example, when a 0-mana Target
            // Dummy is Devolved, because there is no negative-cost minion,
            // it will transform into a random 0-cost minion. For example,
            // when a 25-mana Shirvallah, the Tiger is Evolved, because
            // there is no 26-cost minion or another 25-cost minion, it will
            // transform into a new Shirvallah, the Tiger. References:
            // https://hearthstone.gamepedia.com/Transform
            newCost = m_costChange < 0 ? newCost + 1 : newCost - 1;
        }

        const auto idx = Random::get<std::size_t>(0, cards.size() - 1);
        Generic::ChangeEntity(m_player, playable, cards[idx], true);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> TransformMinionTask::CloneImpl()
{
    return std::make_unique<TransformMinionTask>(m_entityType, m_race,
                                                 m_costChange);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
