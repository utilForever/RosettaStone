// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomMinionTask.hpp>

#include <effolkronium/random.hpp>

#include <utility>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
RandomMinionTask::RandomMinionTask(std::vector<TagValue> tagValues, int amount,
                                   bool opposite, bool excludeSelf)
    : m_tagValues(std::move(tagValues)),
      m_amount(amount),
      m_opposite(opposite),
      m_excludeSelf(excludeSelf)
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
        if (m_excludeSelf && card->id == m_source->card->id)
        {
            continue;
        }

        bool check = true;

        for (auto& tagValue : m_tagValues)
        {
            auto& [gameTag, value, relaSign] = tagValue;

            if (gameTag == GameTag::CARDRACE && relaSign == RelaSign::EQ)
            {
                if (card->GetCardType() != CardType::MINION ||
                    card->GetRace() != static_cast<Race>(std::get<1>(tagValue)))
                {
                    check = false;
                    break;
                }
            }
            else
            {
                if (card->GetCardType() != CardType::MINION ||
                    ((relaSign == RelaSign::EQ &&
                      card->gameTags[gameTag] != value) ||
                     (relaSign == RelaSign::GEQ &&
                      card->gameTags[gameTag] <= value) ||
                     (relaSign == RelaSign::LEQ &&
                      card->gameTags[gameTag] >= value)))
                {
                    check = false;
                    break;
                }
            }
        }

        if (check)
        {
            cardsList.emplace_back(card);
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
            const auto card = Entity::GetFromCard(
                m_opposite ? player->opponent : player, list.at(idx));

            list.erase(list.begin() + static_cast<std::ptrdiff_t>(idx));

            randomMinions.emplace_back(card);
        }
    }
    else
    {
        const auto idx = Random::get<std::size_t>(0, cardsList.size() - 1);
        const auto card = Entity::GetFromCard(
            m_opposite ? player->opponent : player, cardsList.at(idx));

        randomMinions.emplace_back(card);
    }

    player->game->taskStack.playables = randomMinions;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RandomMinionTask::CloneImpl()
{
    return std::make_unique<RandomMinionTask>(m_tagValues, m_amount, m_opposite,
                                              m_excludeSelf);
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
