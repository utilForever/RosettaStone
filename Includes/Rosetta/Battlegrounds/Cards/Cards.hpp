// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_CARDS_HPP
#define ROSETTASTONE_BATTLEGROUNDS_CARDS_HPP

#include <Rosetta/Battlegrounds/Cards/Card.hpp>
#include <Rosetta/Common/Constants.hpp>

#include <array>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Cards class.
//!
//! This class stores a list of cards and provides several search methods.
//!
class Cards
{
 public:
    //! Deleted copy constructor.
    Cards(const Cards& cards) = delete;

    //! Deleted move constructor.
    Cards(Cards&& cards) = delete;

    //! Deleted copy assignment operator.
    Cards& operator=(const Cards& cards) = delete;

    //! Deleted move assignment operator.
    Cards& operator=(Cards&& cards) = delete;

    //! Returns an instance of Cards class.
    //! \return An instance of Cards class.
    static Cards& GetInstance();

    //! Returns a list of all cards.
    //! \return A list of all cards.
    static const std::array<Card, NUM_BATTLEGROUNDS_CARDS>& GetAllCards();

    //! Returns a card that matches \p id.
    //! \param id The ID of the card.
    //! \return A card that matches \p id.
    static Card FindCardByID(const std::string_view& id);

    //! Returns a card that matches \p dbfID.
    //! \param dbfID The dbfID of the card.
    //! \return A card that matches \p dbfID.
    static Card FindCardByDbfID(int dbfID);

    //! Returns a card that matches \p name.
    //! \param name The name of the card.
    //! \return A card that matches \p name.
    static Card FindCardByName(const std::string_view& name);

    //! Returns a list of current heroes.
    //! \return A list of current heroes.
    static const std::array<Card, NUM_BATTLEGROUNDS_HEROES>& GetCurrentHeroes();

    //! Returns a list of tier 1 minions in Battlegrounds Tavern.
    //! \return A list of tier 1 minions in Battlegrounds Tavern.
    static const std::array<Card, NUM_TIER1_MINIONS>& GetTier1Minions();

    //! Returns a list of tier 2 minions in Battlegrounds Tavern.
    //! \return A list of tier 2 minions in Battlegrounds Tavern.
    static const std::array<Card, NUM_TIER2_MINIONS>& GetTier2Minions();

    //! Returns a list of tier 3 minions in Battlegrounds Tavern.
    //! \return A list of tier 3 minions in Battlegrounds Tavern.
    static const std::array<Card, NUM_TIER3_MINIONS>& GetTier3Minions();

    //! Returns a list of tier 4 minions in Battlegrounds Tavern.
    //! \return A list of tier 4 minions in Battlegrounds Tavern.
    static const std::array<Card, NUM_TIER4_MINIONS>& GetTier4Minions();

    //! Returns a list of tier 5 minions in Battlegrounds Tavern.
    //! \return A list of tier 5 minions in Battlegrounds Tavern.
    static const std::array<Card, NUM_TIER5_MINIONS>& GetTier5Minions();

    //! Returns a list of tier 6 minions in Battlegrounds Tavern.
    //! \return A list of tier 6 minions in Battlegrounds Tavern.
    static const std::array<Card, NUM_TIER6_MINIONS>& GetTier6Minions();

 private:
    //! Constructor: Loads card data.
    Cards();

    static std::array<Card, NUM_BATTLEGROUNDS_CARDS> m_cards;
    static std::array<Card, NUM_BATTLEGROUNDS_HEROES> m_curHeroes;
    static std::array<Card, NUM_TIER1_MINIONS> m_tier1Minions;
    static std::array<Card, NUM_TIER2_MINIONS> m_tier2Minions;
    static std::array<Card, NUM_TIER3_MINIONS> m_tier3Minions;
    static std::array<Card, NUM_TIER4_MINIONS> m_tier4Minions;
    static std::array<Card, NUM_TIER5_MINIONS> m_tier5Minions;
    static std::array<Card, NUM_TIER6_MINIONS> m_tier6Minions;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_CARDS_HPP
