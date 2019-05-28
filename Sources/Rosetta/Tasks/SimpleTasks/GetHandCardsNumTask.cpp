// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/GetHandCardsNumTask.hpp>

namespace RosettaStone::SimpleTasks
{
GetHandCardsNumTask::GetHandCardsNumTask(EntityType entityType, int numIndex)
    : ITask(entityType),
    m_numIndex(numIndex)
{
    // Do nothing
}

TaskID GetHandCardsNumTask::GetTaskID() const
{
    return TaskID::GET_HAND_CARDS_NUM;
}

TaskStatus GetHandCardsNumTask::Impl(Player& player)
{
    int cardsnum = 0;
    if(m_entityType == EntityType::HAND)
        cardsnum = (int)player.GetHand().GetNumOfCards();
    else if(m_entityType == EntityType::ENEMY_HAND)
        cardsnum = (int)player.opponent->GetHand().GetNumOfCards();
    else
        throw std::invalid_argument(
            "GetHandCardsNumTask::Impl() - Invalid entity type (should HAND | ENEMY_HAND)");

    switch(m_numIndex)
    {
        case 0:
            player.GetGame()->taskStack.num = cardsnum;
            break;
        case 1:
            player.GetGame()->taskStack.num1 =cardsnum;
            break;
        default:
            throw std::invalid_argument(
                "GetHandCardsNumTask::Impl() - Invalid number index");
    }

    return TaskStatus::COMPLETE;
}
}  // namespace RosettaStone::SimpleTasks
