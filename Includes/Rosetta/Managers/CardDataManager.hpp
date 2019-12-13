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
using PlayReqs = std::vector<std::tuple<PlayReq, int>>;
using PlayReqsType = std::map<std::string, PlayReqs>;

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

    //! Returns a pointer to card that matches \p cardID.
    //! \param cardID The ID of the card.
    //! \return A pointer to card that matches \p cardID.
    static Power FindPowerByCardID(const std::string& cardID);

 private:
    //! Constructor: Loads card data (powers and play requirements).
    CardDataManager();

    //! Destructor: Releases card data (powers and play requirements).
    ~CardDataManager();

    static PowersType m_powers;
    static PlayReqsType m_playReqs;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CARD_DATA_MANAGER_HPP
