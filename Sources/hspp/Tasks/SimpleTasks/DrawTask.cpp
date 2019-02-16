// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Draw.hpp>
#include <hspp/Tasks/SimpleTasks/DrawTask.hpp>

namespace Hearthstonepp::SimpleTasks
{
DrawTask::DrawTask(size_t num) : m_num(num)
{
    // Do nothing
}

TaskID DrawTask::GetTaskID() const
{
    return TaskID::DRAW;
}

TaskStatus DrawTask::Impl(Player& player)
{
    for (std::size_t i = 0; i < m_num; ++i)
    {
        Generic::Draw(player, nullopt);
    }

    // auto& deck = player.GetDeck();
    // auto& hand = player.GetHand();

    //// After reaching fatigue
    // if (deck.GetNumOfCards() < num)
    //{
    //    const size_t numDrawAfterFatigue = num - deck.GetNumOfCards();

    //    // Sigma (i = 1 to numDrawAfterFatigue) { current.exhausted + i }
    //    const auto fatigueDamage = static_cast<int>(
    //        player.GetNumCardAfterExhaust() * numDrawAfterFatigue +
    //        numDrawAfterFatigue * (numDrawAfterFatigue + 1) / 2);

    //    player.GetHero()->health = player.GetHero()->health - fatigueDamage;
    //    player.SetNumCardAfterExhaust(static_cast<BYTE>(
    //        player.GetNumCardAfterExhaust() + numDrawAfterFatigue));

    //    num = deck.GetNumOfCards();
    //    result = TaskStatus::DRAW_EXHAUST;
    //}

    //// When hand size over HAND_SIZE, overdraw
    // if (hand.GetNumOfCards() + num > HAND_SIZE)
    //{
    //    // The number of overdraw
    //    const size_t over = hand.GetNumOfCards() + num - HAND_SIZE;

    //    std::vector<Entity*> burnt;
    //    burnt.reserve(over);

    //    // Draw burnt card
    //    for (size_t i = 0; i < over; ++i)
    //    {
    //        //burnt[i] = deck.back();
    //        //deck.pop_back();
    //    }

    //    num = HAND_SIZE - hand.GetNumOfCards();

    //    if (result == TaskStatus::DRAW_EXHAUST)
    //    {
    //        result = TaskStatus::DRAW_EXHAUST_OVERDRAW;
    //    }
    //    else
    //    {
    //        result = TaskStatus::DRAW_OVERDRAW;
    //    }

    //    // Send burnt cards to policy
    //    TaskMetaTrait trait(TaskID::OVERDRAW, TaskStatus::DRAW_OVERDRAW,
    //                        player.GetID());
    //    player.GetPolicy().Notify(TaskMeta(trait, std::move(burnt)));
    //}

    //// Draw success
    // for (size_t i = 0; i < num; ++i)
    //{
    //    //const auto entity = deck.back();
    //    //const auto entityClone = new Entity(*entity);
    //    //hand.AddCard(*entityClone);
    //    //deck.pop_back();
    //}

    return TaskStatus::DRAW_SUCCESS;
}
}  // namespace Hearthstonepp::SimpleTasks