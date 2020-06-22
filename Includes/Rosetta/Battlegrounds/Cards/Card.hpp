// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_CARD_HPP
#define ROSETTASTONE_BATTLEGROUNDS_CARD_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>

#include <map>
#include <string>

namespace RosettaStone::Battlegrounds
{
//!
//! \brief Card class.
//!
//! This class stores card information such as attack, health and cost.
//!
class Card
{
 public:
    //! Returns the value of card type.
    //! \return The value of card type.
    CardType GetCardType() const;

    //! Returns the value of race.
    //! \return The value of race.
    Race GetRace() const;

    //! Returns the value of attack.
    //! \return The value of attack.
    int GetAttack() const;

    //! Returns the value of health.
    //! \return The value of health.
    int GetHealth() const;

    //! Returns the value of tier.
    //! \return The value of tier.
    int GetTier() const;

    //! Returns the flag that indicates whether it is a Tier 1 minion in pool.
    //! \return the flag that indicates whether it is a Tier 1 minion in pool.
    bool IsTier1MinionInPool() const;

    //! Returns the flag that indicates whether it is a Tier 2 minion in pool.
    //! \return the flag that indicates whether it is a Tier 2 minion in pool.
    bool IsTier2MinionInPool() const;

    //! Returns the flag that indicates whether it is a Tier 3 minion in pool.
    //! \return the flag that indicates whether it is a Tier 3 minion in pool.
    bool IsTier3MinionInPool() const;

    //! Returns the flag that indicates whether it is a Tier 4 minion in pool.
    //! \return the flag that indicates whether it is a Tier 4 minion in pool.
    bool IsTier4MinionInPool() const;

    //! Returns the flag that indicates whether it is a Tier 5 minion in pool.
    //! \return the flag that indicates whether it is a Tier 5 minion in pool.
    bool IsTier5MinionInPool() const;

    //! Returns the flag that indicates whether it is a Tier 6 minion in pool.
    //! \return the flag that indicates whether it is a Tier 6 minion in pool.
    bool IsTier6MinionInPool() const;

    std::string id;
    int dbfID;
    int normalDbfID;
    int premiumDbfID;

    std::string name;
    std::string text;

    std::map<GameTag, int> gameTags;

    bool isCurHero;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_CARD_HPP
