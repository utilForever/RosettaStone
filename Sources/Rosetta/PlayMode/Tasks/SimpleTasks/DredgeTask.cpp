// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DredgeTask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>

namespace RosettaStone::PlayMode::SimpleTasks
{
DredgeTask::DredgeTask(bool addToStack) : m_addToStack(addToStack)
{
    // Do nothing
}

TaskStatus DredgeTask::Impl(Player* player)
{
    const auto deck = player->GetDeckZone();

    if (deck->IsEmpty())
    {
        return TaskStatus::STOP;
    }

    std::vector<int> cardList;
    cardList.reserve(3);

    for (int i = 1; i <= 3; ++i)
    {
        const auto card = deck->GetNthBottomCard(i);
        if (!card)
        {
            break;
        }

        cardList.emplace_back(card->GetGameTag(GameTag::ENTITY_ID));
    }

    Generic::CreateChoice(player, m_source, ChoiceType::GENERAL,
                          ChoiceAction::DREDGE, cardList);

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> DredgeTask::CloneImpl()
{
    return std::make_unique<DredgeTask>(m_addToStack);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
