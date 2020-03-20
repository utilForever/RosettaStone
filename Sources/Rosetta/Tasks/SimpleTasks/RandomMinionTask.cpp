// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/SimpleTasks/RandomMinionTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::SimpleTasks
{
RandomMinionTask::RandomMinionTask(GameTag tag, int value, int amount,
                                   RelaSign relaSign, bool opposite)
    : m_gameTag(tag),
      m_value(value),
      m_amount(amount),
      m_relaSign(relaSign),
      m_opposite(opposite)
{
    // Do nothing
}

TaskStatus RandomMinionTask::Impl(Player* player)
{
    const auto cards = m_source->game->GetFormatType() == FormatType::STANDARD
                           ? Cards::GetAllStandardCards()
                           : Cards::GetAllWildCards();

    std::vector<Card*> cardsList;
    for (const auto& card : cards)
    {
        if (m_gameTag == GameTag::CARDRACE && m_relaSign == RelaSign::EQ)
        {
            if (card->GetCardType() == CardType::MINION &&
                card->GetRace() == static_cast<Race>(m_value))
            {
                cardsList.emplace_back(card);
            }
        }
        else
        {
            if (card->GetCardType() == CardType::MINION &&
                ((m_relaSign == RelaSign::EQ &&
                  card->gameTags[m_gameTag] == m_value) ||
                 (m_relaSign == RelaSign::GEQ &&
                  card->gameTags[m_gameTag] >= m_value) ||
                 (m_relaSign == RelaSign::LEQ &&
                  card->gameTags[m_gameTag] <= m_value)))
            {
                cardsList.emplace_back(card);
            }
        }
    }

    if (cardsList.empty())
    {
        return TaskStatus::STOP;
    }

    std::vector<Playable*> randomMinions;
    randomMinions.reserve(m_amount);

    if (m_amount > 1)
    {
        std::vector<Card*> list = cardsList;

        while (randomMinions.size() < static_cast<std::size_t>(m_amount) &&
               !cardsList.empty())
        {
            const auto idx = Random::get<std::size_t>(0, list.size() - 1);
            auto card = Entity::GetFromCard(
                m_opposite ? player->opponent : player, list.at(idx));

            list.erase(list.begin() + idx);

            randomMinions.emplace_back(card);
        }
    }
    else
    {
        const auto idx = Random::get<std::size_t>(0, cardsList.size() - 1);
        auto card = Entity::GetFromCard(m_opposite ? player->opponent : player,
                                        cardsList.at(idx));
        randomMinions.emplace_back(card);
    }

    player->game->taskStack.playables = randomMinions;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RandomMinionTask::CloneImpl()
{
    return std::make_unique<RandomMinionTask>(m_gameTag, m_value, m_amount);
}
}  // namespace RosettaStone::SimpleTasks
