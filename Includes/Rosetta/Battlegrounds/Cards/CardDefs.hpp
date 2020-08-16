// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_BATTLEGROUNDS_CARD_DEFS_HPP
#define ROSETTASTONE_BATTLEGROUNDS_CARD_DEFS_HPP

#include <Rosetta/Battlegrounds/Cards/CardDef.hpp>

#include <map>
#include <string>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief CardDefs class.
//!
//! This class manages a list of CardDef data.
//!
class CardDefs
{
 public:
    //! Deleted copy constructor.
    CardDefs(const CardDefs& powers) = delete;

    //! Deleted move constructor.
    CardDefs(CardDefs&& powers) noexcept = delete;

    //! Deleted copy assignment operator.
    CardDefs& operator=(const CardDefs& powers) = delete;

    //! Deleted move assignment operator.
    CardDefs& operator=(CardDefs&& powers) noexcept = delete;

    //! Returns a reference to instance of CardDefs class.
    //! \return A reference to instance of CardDefs class.
    static CardDefs& GetInstance();

    //! Returns the card def data that matches \p id.
    //! \param id The ID of the card.
    //! \return The card def data that matches \p id.
    static CardDef FindCardDefByID(const std::string_view& id);

 private:
    //! Constructor: Loads card data (powers and play requirements).
    CardDefs();

    //! Destructor: Releases card data (powers and play requirements).
    ~CardDefs();

    static std::map<std::string, CardDef> m_data;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_CARD_DEFS_HPP
