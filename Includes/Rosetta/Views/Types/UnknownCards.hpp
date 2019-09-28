// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_VIEWS_TYPES_UNKNOWN_CARDS_HPP
#define ROSETTASTONE_VIEWS_TYPES_UNKNOWN_CARDS_HPP

#include <effolkronium/random.hpp>

#include <map>
#include <string>
#include <utility>
#include <vector>

using Random = effolkronium::random_static;

namespace RosettaStone::Views::Types
{
//!
//! \brief UnknownCardsSet class.
//!
//! This class store a list of unknown card and contains simple methods
//! such as Add() and Remove().
//!
class UnknownCardsSet
{
 public:
    //! Constructs unknown cards set with given \p cards.
    //! \param cards A list of unknown card.
    UnknownCardsSet(std::vector<std::string> cards)
        : m_cards(std::move(cards)), m_cardsSize(0)
    {
        // Do nothing
    }

    //! Adds a card to a list of unknown card.
    //! \param cardID The card ID to add.
    void Add(const std::string& cardID)
    {
        m_cards.push_back(cardID);
    }

    //! Removes a card to a list of unknown card.
    //! \param cardID The card ID to remove.
    void Remove(const std::string& cardID)
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

    //! Resets a list of unknown card.
    void ResetState()
    {
        m_cardsSize = m_cards.size();
    }

    //! Runs \p functor on each rest card.
    //! \param functor A function to run for each rest card.
    template <class Functor>
    void ForEachRestCard(Functor&& functor) const
    {
        for (std::size_t i = 0; i < m_cardsSize; ++i)
        {
            functor(m_cards[i]);
        }
    }

 private:
    std::vector<std::string> m_cards;
    size_t m_cardsSize;
};

//!
//! \brief UnknownCardsSets class.
//!
//! This class store a list of unknown cards set and contains simple methods
//! such as AddCardsSet(), AssignCardToSet() and RemoveCardFromSet().
//!
class UnknownCardsSets
{
 public:
    //! Adds a list of cards to a list of unknown cards set.
    //! \param cards A list of cards to add.
    std::size_t AddCardsSet(const std::vector<std::string>& cards)
    {
        SetItem newItem(cards);
        newItem.refCards = 0;

        const std::size_t idx = m_sets.size();
        m_sets.push_back(newItem);
        return idx;
    }

    //! Returns the index after reference count is increased.
    //! \param setIdx The index of unknown cards set.
    std::size_t AssignCardToSet(size_t setIdx)
    {
        const size_t idx = m_sets[setIdx].refCards;
        ++m_sets[setIdx].refCards;
        return idx;
    }

    //! Removes a card from a specified unknown cards set.
    //! \param setIdx The index of unknown cards set.
    //! \param cardID The card ID to remove.
    void RemoveCardFromSet(size_t setIdx, const std::string& cardID)
    {
        m_sets[setIdx].cards.Remove(cardID);
    }

    //! Resets a list of unknown cards set.
    void ResetState()
    {
        for (auto& set : m_sets)
        {
            set.cards.ResetState();
        }
    }

    //! Runs \p functor on each unknown cards set.
    //! \param functor A function to run for each unknown cards set.
    template <class Functor>
    void ForEach(Functor&& functor) const
    {
        for (auto& set : m_sets)
        {
            functor(set.cards, set.refCards);
        }
    }

 private:
    struct SetItem
    {
        SetItem(const std::vector<std::string>& _cards)
            : cards(_cards), refCards()
        {
        }

        UnknownCardsSet cards;
        std::size_t refCards;
    };

    std::vector<SetItem> m_sets;
};

//!
//! \brief UnknownCardsInfo struct.
//!
//! This struct stores the information of unknown cards.
//!
struct UnknownCardsInfo
{
    constexpr static int DECK_BLOCK_ID = -1;

    std::vector<std::string> deckCards;
    UnknownCardsSets unknownCardsSets;
    std::map<int, std::size_t> setsIndices;
};

//!
//! \brief UnknownCardsSetsManager class.
//!
//! This class is the manager of a set of unknown cards and contains method
//! Setup() and Prepare().
//!
class UnknownCardsSetsManager
{
 public:
    //! Default constructor.
    UnknownCardsSetsManager() : m_data(nullptr)
    {
        // Do nothing
    }

    //! Deleted copy constructor.
    UnknownCardsSetsManager(const UnknownCardsSetsManager&) = delete;

    //! Default move constructor.
    UnknownCardsSetsManager(UnknownCardsSetsManager&&) noexcept = default;

    //! Deleted copy assignment operator.
    UnknownCardsSetsManager& operator=(UnknownCardsSetsManager const&) = delete;

    //! Default move assignment operator.
    UnknownCardsSetsManager& operator=(UnknownCardsSetsManager&&) noexcept =
        default;

    //! Setups a set of unknown cards.
    //! \param data A set of unknown cards.
    void Setup(UnknownCardsSets& data)
    {
        m_data = &data;
    }

    //! Prepares the unknown cards sets manager.
    void Prepare()
    {
        m_data->ResetState();
        m_shuffledCards.clear();

        std::vector<std::string> cardsPool;
        m_data->ForEach([&](const UnknownCardsSet& set, size_t refCards) {
            set.ForEachRestCard([&](const std::string& cardID) {
                cardsPool.push_back(cardID);
            });

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

    //! Returns the card ID in a set of unknown cards.
    //! \param setIdx The index of unknown cards set.
    //! \param cardIdx The index of card in unknown cards set.
    //! \return The card ID in a set of unknown cards.
    std::string GetCardID(size_t setIdx, size_t cardIdx) const
    {
        return m_shuffledCards[setIdx][cardIdx];
    }

 private:
    UnknownCardsSets* m_data;
    std::vector<std::vector<std::string>> m_shuffledCards;
};
}  // namespace RosettaStone::Views::Types

#endif  // ROSETTASTONE_VIEWS_TYPES_UNKNOWN_CARDS_HPP
