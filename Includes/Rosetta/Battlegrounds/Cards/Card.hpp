// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_CARD_HPP
#define ROSETTASTONE_BATTLEGROUNDS_CARD_HPP

#include <Rosetta/Battlegrounds/Cards/TargetingPredicates.hpp>
#include <Rosetta/Battlegrounds/Enchants/Power.hpp>
#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/Common/Enums/TargetingEnums.hpp>

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
    //! Initializes card data.
    void Initialize();

    //! Returns the value of card set.
    //! \return The value of card set.
    CardSet GetCardSet() const;

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

    //! Gets a value indicating whether source entity is playable by card
    //! requirements. Static requirements are checked.
    //! \param player The player of the source.
    //! \return true if it is playable by card requirements, false otherwise.
    bool IsPlayableByCardReq(Player& player) const;

    //! Calculates if a target is valid by testing the game state
    //! for each hardcoded requirement.
    //! \param target The proposed target.
    //! \return true if the proposed target is valid, false otherwise.
    bool TargetingRequirements(Minion& target) const;

    std::string id;
    int dbfID;
    int normalDbfID;
    int premiumDbfID;

    std::string name;
    std::string text;

    std::map<GameTag, int> gameTags;
    std::map<PlayReq, int> playRequirements;

    std::vector<TargetingPredicate> targetingPredicate;

    TargetingType targetingType;
    Power power;

    bool isCurHero = false;
    bool isBattlegroundsPoolMinion = false;
    bool mustHaveToTargetToPlay = false;
};
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_CARD_HPP
