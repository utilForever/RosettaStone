// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CARD_DATA_MANAGER_HPP
#define ROSETTASTONE_CARD_DATA_MANAGER_HPP

#include <Rosetta/Enchants/Power.hpp>

#include <map>
#include <string>

namespace RosettaStone
{
using PowersType = std::map<std::string, Power>;
using PlayReqs = std::map<PlayReq, int>;
using PlayReqsType = std::map<std::string, PlayReqs>;
using Entourages = std::vector<std::string>;
using EntouragesType = std::map<std::string, Entourages>;

//!
//! \brief CardDataManager class.
//!
//! This class manages the card data such as powers and play requirements.
//!
class CardDataManager
{
 public:
    //! Deleted copy constructor.
    CardDataManager(const CardDataManager& powers) = delete;

    //! Deleted move constructor.
    CardDataManager(CardDataManager&& powers) noexcept = delete;

    //! Deleted copy assignment operator.
    CardDataManager& operator=(const CardDataManager& powers) = delete;

    //! Deleted move assignment operator.
    CardDataManager& operator=(CardDataManager&& powers) noexcept = delete;

    //! Returns a reference to instance of CardDataManager class.
    //! \return A reference to instance of CardDataManager class.
    static CardDataManager& GetInstance();

    //! Returns the power of card that matches \p cardID.
    //! \param cardID The ID of the card.
    //! \return The power of card that matches \p cardID.
    static Power FindPowerByCardID(const std::string_view& cardID);

    //! Returns the play requirements of card that matches \p cardID.
    //! \param cardID The ID of the card.
    //! \return The play requirements of card that matches \p cardID.
    static PlayReqs FindPlayReqsByCardID(const std::string_view& cardID);

    //! Returns the entourages of card that matches \p cardID.
    //! \param cardID The ID of the card.
    //! \return The entourages of card that matches \p cardID.
    static Entourages FindEntouragesByCardID(const std::string_view& cardID);

 private:
    //! Constructor: Loads card data (powers and play requirements).
    CardDataManager();

    //! Destructor: Releases card data (powers and play requirements).
    ~CardDataManager();

    static PowersType m_powers;
    static PlayReqsType m_playReqs;
    static EntouragesType m_entourages;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CARD_DATA_MANAGER_HPP
