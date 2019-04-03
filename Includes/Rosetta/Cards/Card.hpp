// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CARD_HPP
#define ROSETTASTONE_CARD_HPP

#include <Rosetta/Enchants/Power.hpp>
#include <Rosetta/Enums/CardEnums.hpp>

#include <map>
#include <optional>
#include <string>
#include <vector>

namespace RosettaStone
{
class Power;

//!
//! \brief Card class.
//!
//! This class stores card information such as attack, health and cost.
//!
class Card
{
 public:
    //! Default constructor.
    Card() = default;

    //! Default destructor.
    virtual ~Card() = default;

    //! Default copy constructor.
    Card(const Card& card) = default;

    //! Default move constructor.
    Card(Card&& card) = default;

    //! Default copy assignment operator.
    Card& operator=(const Card& card) = default;

    //! Default move assignment operator.
    Card& operator=(Card&& card) = default;

    //! Initializes card data.
    void Initialize();

    //! Finds out if this card has game tag.
    //! \param gameTag The game tag of card.
    //! \return true if this card has game tag, and false otherwise.
    bool HasGameTag(GameTag gameTag) const;

    //! Returns the number of cards that can be inserted into the deck.
    //! \return The number of cards that can be inserted into the deck.
    std::size_t GetMaxAllowedInDeck() const;

    //! Prints brief card information.
    virtual void ShowBriefInfo() const;

    //! Prints card information.
    virtual void ShowInfo() const;

    Rarity rarity = Rarity::INVALID;
    Faction faction = Faction::INVALID;
    CardSet cardSet = CardSet::INVALID;
    CardClass cardClass = CardClass::INVALID;
    CardType cardType = CardType::INVALID;
    Race race = Race::INVALID;

    std::string id;
    std::string name;
    std::string text;

    std::optional<std::size_t> spellPower;
    std::optional<std::size_t> durability;

    std::size_t cost = 0;

    std::map<GameTag, int> gameTags;
    std::map<PlayReq, int> playRequirements;
    std::vector<std::string> entourages;

    Power power;

    std::size_t maxAllowedInDeck = 0;
    bool isCollectible = false;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CARD_HPP
