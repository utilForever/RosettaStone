// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Draw.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/DrawMinionTask.hpp>
#include <Rosetta/Zones/DeckZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
DrawMinionTask::DrawMinionTask(bool lowestCost, int amount, bool addToStack)
    : m_amount(amount), m_lowestCost(lowestCost), m_addToStack(addToStack)
{
    // Do nothing
}

TaskStatus DrawMinionTask::Impl(Player* player)
{
    auto deck = player->GetDeckZone()->GetAll();
    if (deck.empty())
    {
        return TaskStatus::STOP;
    }

    if (m_addToStack)
    {
        player->game->taskStack.playables.clear();
    }

    std::vector<Playable*> cards;
    cards.reserve(m_amount);

    if (m_lowestCost)
    {
        int minCost = std::numeric_limits<int>::max();

        for (auto& deckCard : deck)
        {
            if (deckCard->card->GetCardType() != CardType::MINION)
            {
                continue;
            }

            const int cost = deckCard->card->GetCost();
            if (cost < minCost)
            {
                minCost = cost;

                cards.clear();
                cards.emplace_back(deckCard);
            }
            else if (cost == minCost)
            {
                cards.emplace_back(deckCard);
            }
        }
    }
    else
    {
        for (auto& deckCard : deck)
        {
            if (deckCard->card->GetCardType() == CardType::MINION)
            {
                cards.emplace_back(deckCard);
            }
        }
    }

    if (cards.empty())
    {
        return TaskStatus::STOP;
    }

    if (static_cast<int>(cards.size()) <= m_amount)
    {
        for (int i = 0; i < m_amount; ++i)
        {
            if (m_addToStack)
            {
                player->game->taskStack.playables.emplace_back(cards[i]);
            }

            Generic::Draw(player, cards[i]);
        }
    }
    else
    {
        for (int i = 0; i < m_amount; ++i)
        {
            const auto pick = Random::get<std::size_t>(0, cards.size() - 1);

            if (m_addToStack)
            {
                player->game->taskStack.playables.emplace_back(cards[pick]);
            }

            Generic::Draw(player, cards[pick]);
            cards.erase(std::begin(cards) + pick);
        }
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DrawMinionTask::CloneImpl()
{
    return std::make_unique<DrawMinionTask>(m_lowestCost, m_amount,
                                            m_addToStack);
}
}  // namespace RosettaStone::SimpleTasks