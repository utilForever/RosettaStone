// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/RandomSpellTask.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::SimpleTasks
{
RandomSpellTask::RandomSpellTask(CardClass cardClass, int amount)
    : m_cardClass(cardClass), m_amount(amount)
{
    // Do nothing
}

RandomSpellTask::RandomSpellTask(CardClass cardClass, GameTag tag, int value,
                                 int amount, RelaSign relaSign, bool opposite)
    : m_cardClass(cardClass),
      m_gameTag(tag),
      m_value(value),
      m_amount(amount),
      m_relaSign(relaSign),
      m_opposite(opposite)
{
    // Do nothing
}

TaskStatus RandomSpellTask::Impl(Player* player)
{
    std::vector<Card*> cards, result;

    if (m_cardClass == CardClass::INVALID)
    {
        cards = m_source->game->GetFormatType() == FormatType::STANDARD
                    ? Cards::GetAllStandardCards()
                    : Cards::GetAllWildCards();
    }
    else if (m_cardClass == CardClass::PLAYER_CLASS)
    {
        const auto playerClass = player->GetHero()->card->GetCardClass();
        cards = m_source->game->GetFormatType() == FormatType::STANDARD
                    ? Cards::GetStandardCards(playerClass)
                    : Cards::GetWildCards(playerClass);
    }
    else
    {
        cards = m_source->game->GetFormatType() == FormatType::STANDARD
                    ? Cards::GetStandardCards(m_cardClass)
                    : Cards::GetWildCards(m_cardClass);
    }

    for (const auto& card : cards)
    {
        if (card->GetCardType() != CardType::SPELL)
        {
            continue;
        }

        if (m_gameTag == GameTag::INVALID || Evaluate(card))
        {
            result.emplace_back(card);
        }
    }

    if (result.empty())
    {
        return TaskStatus::STOP;
    }

    std::vector<Playable*> randomSpells;
    randomSpells.reserve(m_amount);

    if (m_amount > 1)
    {
        std::vector<Card*> list = result;

        while (randomSpells.size() < static_cast<std::size_t>(m_amount) &&
               !result.empty())
        {
            const auto idx = Random::get<std::size_t>(0, list.size() - 1);
            const auto card = Entity::GetFromCard(
                m_opposite ? player->opponent : player, list.at(idx));

            list.erase(list.begin() + static_cast<std::ptrdiff_t>(idx));

            randomSpells.emplace_back(card);
        }
    }
    else
    {
        const auto idx = Random::get<std::size_t>(0, result.size() - 1);
        const auto card = Entity::GetFromCard(
            m_opposite ? player->opponent : player, result.at(idx));

        randomSpells.emplace_back(card);
    }

    player->game->taskStack.playables = randomSpells;

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> RandomSpellTask::CloneImpl()
{
    return std::make_unique<RandomSpellTask>(m_cardClass, m_gameTag, m_value,
                                             m_amount, m_relaSign, m_opposite);
}

bool RandomSpellTask::Evaluate(Card* card) const
{
    if ((m_relaSign == RelaSign::EQ && card->gameTags[m_gameTag] == m_value) ||
        (m_relaSign == RelaSign::GEQ && card->gameTags[m_gameTag] >= m_value) ||
        (m_relaSign == RelaSign::LEQ && card->gameTags[m_gameTag] <= m_value))
    {
        return true;
    }

    return false;
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
