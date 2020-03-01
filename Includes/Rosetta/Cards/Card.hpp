// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CARD_HPP
#define ROSETTASTONE_CARD_HPP

#include <Rosetta/Enchants/Power.hpp>
#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Enums/TargetingEnums.hpp>
#include <Rosetta/Loaders/TargetingPredicates.hpp>

#include <map>
#include <string>
#include <vector>

namespace RosettaStone
{
class Character;
class Power;

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

    //! Returns the value of card class.
    //! \return The value of card class.
    CardClass GetCardClass() const;

    //! Returns the value of card set.
    //! \return The value of card set.
    CardSet GetCardSet() const;

    //! Returns the value of card type.
    //! \return The value of card type.
    CardType GetCardType() const;

    //! Returns the value of faction.
    //! \return The value of faction.
    Faction GetFaction() const;

    //! Returns the value of race.
    //! \return The value of race.
    Race GetRace() const;

    //! Returns the value of rarity.
    //! \return The value of rarity.
    Rarity GetRarity() const;

    //! Returns the value of cost.
    //! \return The value of cost.
    int GetCost() const;

    //! Finds out if this card has game tag.
    //! \param gameTag The game tag of card.
    //! \return true if this card has game tag, and false otherwise.
    bool HasGameTag(GameTag gameTag) const;

    //! Returns the flag that indicates whether it is Lackey.
    //! \return The flag that indicates whether it is Lackey.
    bool IsLackey() const;

    //! Returns the flag that indicates whether it is Galakrond.
    //! \return The flag that indicates whether it is Galakrond.
    bool IsGalakrond() const;

    //! Returns the flag that indicates whether it is untouchable.
    //! \return The flag that indicates whether it is untouchable.
    bool IsUntouchable() const;

    //! Returns the flag that indicates whether it is secret card.
    //! \return The flag that indicates whether it is secret card.
    bool IsSecret() const;

    //! Returns the flag that indicates whether it is collectible.
    //! \return The flag that indicates whether it is collectible.
    bool IsCollectible() const;

    //! Finds out if this card is in STANDARD set.
    //! \return true if this card is in STANDARD set, and false otherwise.
    bool IsStandardSet() const;

    //! Finds out if this card is in WILD set.
    //! \return true if this card is in WILD set, and false otherwise.
    bool IsWildSet() const;

    //! Returns the number of cards that can be inserted into the deck.
    //! \return The number of cards that can be inserted into the deck.
    std::size_t GetMaxAllowedInDeck() const;

    //! Calculates if a target is valid by testing the game state
    //! for each hardcoded requirement.
    //! \param player The player of the source.
    //! \param target The proposed target.
    //! \return true if the proposed target is valid, false otherwise.
    bool TargetingRequirements(Player* player, Character* target);

    //! Gets the valid play targets.
    //! This method defaults to targeting in the context of spells/hero powers.
    //! \param player The player of the source.
    //! \return A list of valid play targets.
    std::vector<Character*> GetValidPlayTargets(Player* player);

    //! Prints brief card information.
    void ShowBriefInfo() const;

    //! Prints card information.
    void ShowInfo() const;

    std::string id;
    int dbfID;
    std::string name;
    std::string text;

    std::map<GameTag, int> gameTags;
    std::map<PlayReq, int> playRequirements;
    std::vector<std::string> chooseCardIDs;
    std::vector<std::string> entourages;

    std::vector<TargetingPredicate> targetingPredicate;
    std::vector<AvailabilityPredicate> targetingAvailabilityPredicate;

    TargetingType targetingType;
    Power power;

    std::size_t maxAllowedInDeck = 0;

    bool mustHaveToTargetToPlay = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CARD_HPP
