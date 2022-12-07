// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_CARD_HPP
#define ROSETTASTONE_PLAYMODE_CARD_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/Common/Enums/TargetingEnums.hpp>
#include <Rosetta/Common/Enums/TaskEnums.hpp>
#include <Rosetta/PlayMode/Enchants/Power.hpp>
#include <Rosetta/PlayMode/Loaders/TargetingPredicates.hpp>

#include <map>
#include <string>
#include <vector>

namespace RosettaStone::PlayMode
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

    //! Returns the value of multi class group.
    //! \return The value of multi class group.
    MultiClassGroup GetMultiClassGroup() const;

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

    //! Returns the value of spell school.
    //! \return The value of spell school.
    SpellSchool GetSpellSchool() const;

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

    //! Returns the flag that indicates whether the card class is \p cardClass.
    //! \param cardClass The value of card class to check.
    //! \return The flag that indicates whether the card class is \p cardClass.
    bool IsCardClass(CardClass cardClass) const;

    //! Returns the flag that indicates whether it is quest.
    //! \return The flag that indicates whether it is quest.
    bool IsQuest() const;

    //! Returns the flag that indicates whether it is basic Totem.
    //! \return The flag that indicates whether it is basic Totem.
    bool IsBasicTotem() const;

    //! Returns the flag that indicates whether it is Lackey.
    //! \return The flag that indicates whether it is Lackey.
    bool IsLackey() const;

    //! Returns the flag that indicates whether it is Poison.
    //! \return The flag that indicates whether it is Poison.
    bool IsPoison() const;

    //! Returns the flag that indicates whether it is Watch Post.
    //! \return The flag that indicates whether it is Watch Post.
    bool IsWatchPost() const;

    //! Returns the flag that indicates whether it is Adventurer.
    //! \return the flag that indicates whether it is Adventurer.
    bool IsAdventurer() const;

    //! Returns the flag that indicates whether it is a card with two Choose One
    //! options involving transform or specific summon effects is played while
    //! controlling Ossirian Tear.
    //! \return The flag that indicates whether it is a card with two Choose One
    //! options involving transform or specific summon effects is played while
    //! controlling Ossirian Tear, false otherwise.
    bool IsTransformMinion() const;

    //! Returns the flag that indicates whether it is Galakrond.
    //! \return The flag that indicates whether it is Galakrond.
    bool IsGalakrond() const;

    //! Returns the flag that indicates whether it is Colossal.
    //! \return The flag that indicates whether it is Colossal.
    bool IsColossal() const;

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

    //! Finds out if this card is in CLASSIC set.
    //! \return true if this card is in CLASSIC set, and false otherwise.
    bool IsClassicSet() const;

    //! Returns the number of cards that can be inserted into the deck.
    //! \return The number of cards that can be inserted into the deck.
    std::size_t GetMaxAllowedInDeck() const;

    //! Gets a value indicating whether source entity is playable by card
    //! requirements. Static requirements are checked.
    //! \param player The player of the source.
    //! \return true if it is playable by card requirements, false otherwise.
    bool IsPlayableByCardReq(Player* player) const;

    //! Gets a value indicating whether source entity is playable by location
    //! requirements. Static requirements are checked.
    //! \param player The player of the source.
    //! \return true if it is playable by location requirements,
    //! false otherwise.
    bool IsPlayableByLocationReq(Player* player) const;

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

    std::string id;
    int dbfID;
    std::string name;
    std::string text;

    std::map<GameTag, int> gameTags;
    std::map<PlayReq, int> playRequirements;
    std::map<PlayReq, int> locationPlayRequirements;
    std::vector<std::string> chooseCardIDs;
    std::vector<std::string> entourages;
    std::vector<std::tuple<std::string, SummonSide>> appendages;

    std::vector<TargetingPredicate> targetingPredicate;
    std::vector<AvailabilityPredicate> targetingAvailabilityPredicate;

    TargetingType targetingType;
    Power power;

    std::size_t maxAllowedInDeck = 0;

    bool mustHaveToTargetToPlay = false;

 private:
    //! Sets targeting-related values regarding to play requirements.
    //! \param playReqType The play requirement type.
    void SetTargetingType(PlayReqType playReqType);

    //! Internal method of IsPlayableByCardReq().
    //! \param player The player of the source.
    //! \param playReqType The play requirement type.
    //! \return true if it is playable by card requirements, false otherwise.
    bool IsPlayableByCardReqInternal(Player* player,
                                     PlayReqType playReqType) const;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_CARD_HPP
