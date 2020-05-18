// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/PlayMode/Views/Types/UnknownCards.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::Views::Types
{
UnknownCardsSet::UnknownCardsSet(std::vector<std::string> cards)
    : m_cards(std::move(cards)), m_cardsSize(0)
{
    // Do nothing
}

void UnknownCardsSet::Add(const std::string& cardID)
{
    m_cards.push_back(cardID);
}

void UnknownCardsSet::Remove(const std::string& cardID)
{
    for (auto iter = m_cards.begin(); iter != m_cards.end(); ++iter)
    {
        if (*iter == cardID)
        {
            m_cards.erase(iter);
            return;
        }
    }
}

void UnknownCardsSet::ResetState()
{
    m_cardsSize = m_cards.size();
}

std::size_t UnknownCardsSets::AddCardsSet(const std::vector<std::string>& cards)
{
    SetItem newItem(cards);
    newItem.refCards = 0;

    const std::size_t idx = m_sets.size();
    m_sets.push_back(newItem);
    return idx;
}

std::size_t UnknownCardsSets::AssignCardToSet(size_t setIdx)
{
    const size_t idx = m_sets[setIdx].refCards;
    ++m_sets[setIdx].refCards;
    return idx;
}

void UnknownCardsSets::RemoveCardFromSet(size_t setIdx,
                                         const std::string& cardID)
{
    m_sets[setIdx].cards.Remove(cardID);
}

void UnknownCardsSets::ResetState()
{
    for (auto& set : m_sets)
    {
        set.cards.ResetState();
    }
}

UnknownCardsSetsManager::UnknownCardsSetsManager() : m_data(nullptr)
{
    // Do nothing
}

void UnknownCardsSetsManager::Setup(UnknownCardsSets& data)
{
    m_data = &data;
}

void UnknownCardsSetsManager::Prepare()
{
    m_data->ResetState();
    m_shuffledCards.clear();

    std::vector<std::string> cardsPool;
    m_data->ForEach([&](const UnknownCardsSet& set, size_t refCards) {
        set.ForEachRestCard(
            [&](const std::string& cardID) { cardsPool.push_back(cardID); });

        m_shuffledCards.emplace_back();
        for (std::size_t i = 0; i < refCards; ++i)
        {
            const int randIdx = Random::get<int>(0, cardsPool.size() - 1);
            std::swap(cardsPool[randIdx], cardsPool.back());
            m_shuffledCards.back().push_back(cardsPool.back());
            cardsPool.pop_back();
        }
    });
}

std::string UnknownCardsSetsManager::GetCardID(size_t setIdx,
                                               size_t cardIdx) const
{
    return m_shuffledCards[setIdx][cardIdx];
}
}  // namespace RosettaStone::PlayMode::Views::Types
