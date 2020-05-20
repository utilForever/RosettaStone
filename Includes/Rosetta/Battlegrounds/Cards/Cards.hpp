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
    //! Returns an instance of Cards class.
    //! \return An instance of Cards class.
    static Cards& GetInstance();

    //! Returns a list of all cards.
    //! \return A list of all cards.
    static const std::array<Card, NUM_BATTLEGROUNDS_CARDS>& GetAllCards();

    //! Returns a list of current hero cards.
    //! \return A list of current hero cards.
    static const std::array<Card, NUM_HEROES_IN_BATTLEGROUNDS>&
    GetCurrentHeroCards();

 private:
    //! Constructor: Loads card data.
    Cards();

    static std::array<Card, NUM_BATTLEGROUNDS_CARDS> m_cards;
    static std::array<Card, NUM_HEROES_IN_BATTLEGROUNDS> m_curHeroes;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_CARDS_HPP
