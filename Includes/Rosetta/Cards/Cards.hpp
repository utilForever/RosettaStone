// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CARDS_HPP
#define ROSETTASTONE_CARDS_HPP

#include <Rosetta/Cards/Card.hpp>

#include <vector>

namespace RosettaStone
{
//!
//! \brief Search filter structure.
//!
//! This structure stores the filter value for searching the card.
//!
struct SearchFilter
{
    Rarity rarity = Rarity::INVALID;
    CardClass playerClass = CardClass::INVALID;
    CardType cardType = CardType::INVALID;
    Race race = Race::INVALID;
    GameTag mechanic = GameTag::INVALID;

    std::string name;
    size_t costMin = 0, costMax = 0;
    size_t attackMin = 0, attackMax = 0;
    size_t healthMin = 0, healthMax = 0;
};

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
    const std::vector<Card>& GetAllCards() const;

    //! Returns a card that matches \p id.
    //! \param id The ID of the card.
    //! \return A card that matches \p id.
    Card FindCardByID(const std::string& id);

    //! Returns a list of cards that matches \p rarity.
    //! \param rarity The rarity of the card.
    //! \return A list of cards that matches condition.
    std::vector<Card> FindCardByRarity(Rarity rarity);

    //! Returns a list of cards that matches \p cardClass.
    //! \param cardClass The class of the card.
    //! \return A list of cards that matches condition.
    std::vector<Card> FindCardByClass(CardClass cardClass);

    //! Returns a list of cards that matches \p cardSet.
    //! \param cardSet The set of the card.
    //! \return A list of cards that matches condition.
    std::vector<Card> FindCardBySet(CardSet cardSet);

    //! Returns a list of cards that matches \p cardType.
    //! \param cardType The type of the card.
    //! \return A list of cards that matches condition.
    std::vector<Card> FindCardByType(CardType cardType);

    //! Returns a list of cards that matches \p race.
    //! \param race The race of the card.
    //! \return A list of cards that matches condition.
    std::vector<Card> FindCardByRace(Race race);

    //! Returns a card that matches \p name.
    //! \param name The name of the card.
    //! \return A card that matches condition.
    Card FindCardByName(const std::string& name);

    //! Returns a list of cards whose cost is between \p minVal and \p maxVal.
    //! \param minVal The minimum cost value of the card.
    //! \param maxVal The maximum cost value of the card.
    //! \return A list of cards that matches condition.
    std::vector<Card> FindCardByCost(std::size_t minVal, std::size_t maxVal);

    //! Returns a list of cards whose attack is between \p minVal and \p maxVal.
    //! \param minVal The minimum attack value of the card.
    //! \param maxVal The maximum attack value of the card.
    //! \return A list of cards that matches condition.
    std::vector<Card> FindCardByAttack(std::size_t minVal, std::size_t maxVal);

    //! Returns a list of cards whose health is between \p minVal and \p maxVal.
    //! \param minVal The minimum health value of the card.
    //! \param maxVal The maximum health value of the card.
    //! \return A list of cards that matches condition.
    std::vector<Card> FindCardByHealth(std::size_t minVal, std::size_t maxVal);

    //! Returns a list of cards whose damage is between \p minVal and \p maxVal.
    //! \param minVal The minimum spell damage value of the card.
    //! \param maxVal The maximum spell damage value of the card.
    //! \return A list of cards that matches condition.
    std::vector<Card> FindCardBySpellDamage(std::size_t minVal,
                                            std::size_t maxVal);

    //! Returns a list of cards that has \p mechanics.
    //! \param mechanics The mechanics of the card.
    //! \return A list of cards that matches condition.
    std::vector<Card> FindCardByMechanics(std::vector<GameTag> mechanics);

    //! Returns a hero card that matches \p cardClass.
    //! \param cardClass The class of the card.
    //! \return A hero card that matches condition.
    Card GetHeroCard(CardClass cardClass);

    //! Returns a default hero power card that matches \p cardClass.
    //! \param cardClass The class of the card.
    //! \return A default hero power card that matches condition.
    Card GetDefaultHeroPower(CardClass cardClass);

 private:
    //! Constructor: Loads card data.
    Cards();

    //! Destructor: Releases card data.
    ~Cards();

    std::vector<Card> m_cards;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CARDS_HPP
