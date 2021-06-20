// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Actions/Draw.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DrawMinionTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
DrawMinionTask::DrawMinionTask(int amount, bool addToStack)
    : m_amount(amount), m_addToStack(addToStack)
{
    // Do nothing
}

DrawMinionTask::DrawMinionTask(DrawMinionType drawMinionType, int amount,
                               bool addToStack)
    : m_amount(amount),
      m_drawMinionType(drawMinionType),
      m_addToStack(addToStack)
{
    // Do nothing
}

TaskStatus DrawMinionTask::Impl(Player* player)
{
    if (m_addToStack)
    {
        player->game->taskStack.playables.clear();
    }

    auto deckCards = player->GetDeckZone()->GetAll();
    if (deckCards.empty())
    {
        return TaskStatus::STOP;
    }

    EraseIf(deckCards, [=](Playable* playable) {
        return playable->card->GetCardType() != CardType::MINION;
    });

    switch (m_drawMinionType)
    {
        case DrawMinionType::DEFAULT:
            std::shuffle(deckCards.begin(), deckCards.end(),
                         Random::get_engine());
            break;
        case DrawMinionType::LOWEST_COST:
            std::sort(deckCards.begin(), deckCards.end(),
                      [](const Playable* card1, const Playable* card2) {
                          return card1->GetCost() < card2->GetCost();
                      });
            break;
        case DrawMinionType::HIGHEST_COST:

            std::sort(deckCards.begin(), deckCards.end(),
                      [](const Playable* card1, const Playable* card2) {
                          return card1->GetCost() > card2->GetCost();
                      });
            break;
    }

    for (int i = 0; i < m_amount; ++i)
    {
        if (m_addToStack)
        {
            player->game->taskStack.playables.emplace_back(deckCards[i]);
        }

        Generic::Draw(player, deckCards[i]);
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DrawMinionTask::CloneImpl()
{
    return std::make_unique<DrawMinionTask>(m_drawMinionType, m_amount,
                                            m_addToStack);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks