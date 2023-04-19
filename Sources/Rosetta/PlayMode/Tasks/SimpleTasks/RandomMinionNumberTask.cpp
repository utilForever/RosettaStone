// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomMinionNumberTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
RandomMinionNumberTask::RandomMinionNumberTask(GameTag tag, bool toOpponent)
    : m_gameTag(tag), m_toOpponent(toOpponent)
{
    // Do nothing
}

TaskStatus RandomMinionNumberTask::Impl(Player* player)
{
    const auto cards = m_source->game->GetFormatType() == FormatType::STANDARD
                           ? Cards::GetAllStandardCards()
                           : Cards::GetAllWildCards();

    std::vector<Card*> cardsList;
    const int num = player->game->taskStack.num[0];

    for (const auto& card : cards)
    {
        if (card->GetCardType() == CardType::MINION &&
            card->gameTags[m_gameTag] == num)
        {
            cardsList.emplace_back(card);
        }
    }

    if (cardsList.empty())
    {
        return TaskStatus::STOP;
    }

    std::vector<Playable*> randomMinions;
    randomMinions.reserve(1);

    const auto idx = Random::get<std::size_t>(0, cardsList.size() - 1);
    auto card = Entity::GetFromCard(m_toOpponent ? player->opponent : player,
                                    cardsList.at(idx));
    randomMinions.emplace_back(card);

    player->game->taskStack.playables = randomMinions;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RandomMinionNumberTask::CloneImpl()
{
    return std::make_unique<RandomMinionNumberTask>(m_gameTag, m_toOpponent);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
