// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Commons/Constants.hpp>
#include <hspp/Models/Entity.hpp>
#include <hspp/Models/Game.hpp>
#include <hspp/Models/Minion.hpp>
#include <hspp/Models/Weapon.hpp>
#include <hspp/Tasks/SimpleTasks/DrawCardTask.hpp>

#include <utility>

namespace Hearthstonepp::SimpleTasks
{
DrawCardTask::DrawCardTask(Card card) : m_card(std::move(card))
{
    // Do nothing
}

TaskID DrawCardTask::GetTaskID() const
{
    return TaskID::DRAW;
}

TaskStatus DrawCardTask::Impl(Player& player)
{
    // auto& deck = player.GetDeck();
    auto& hand = player.GetHand();

    auto* game = player.GetGame();

    switch (m_card.cardType)
    {
        case +CardType::MINION:
        {
            const auto minion = new Minion(game, m_card);
            hand.AddCard(*minion);
            break;
        }
        case +CardType::WEAPON:
        {
            const auto weapon = new Weapon(game, m_card);
            hand.AddCard(*weapon);
            break;
        }
        default:
            throw std::invalid_argument(
                "DrawCardTask::Impl() - Invalid card type!");
    }

    // if (!deck.empty())
    //{
    //    deck.pop_back();
    //}

    return TaskStatus::DRAW_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks