#ifndef HEARTHSTONEPP_CARDS_H
#define HEARTHSTONEPP_CARDS_H

#include <Cards/Card.h>

#include <vector>

namespace Hearthstonepp
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
    size_t costMin, costMax;
    size_t attackMin, attackMax;
    size_t healthMin, healthMax;
};

//!
//! \brief Cards class.
//!
//! This class stores a list of cards and provides several search methods.
//!
class Cards
{
 public:
    //! Returns a pointer to instance of Cards class.
    //! \return A pointer to instance of Cards class.
    static Cards* GetInstance();

    //! Returns a list of pointers to all cards.
    //! \return A list of pointers to all cards.
    const std::vector<Card*>& GetAllCards() const;

    //! Returns a pointer to card that matches \p id.
    //! \param id The ID of the card.
    //! \return A pointer to card that matches \p id.
    const Card* FindCardByID(const std::string& id);

    //! Returns a list of pointers to each card that matches \p rarity.
    //! \param rarity The rarity of the card.
    //! \return A list of pointers to each card that matches \p rarity.
    std::vector<Card*> FindCardByRarity(Rarity rarity);

    //! Returns a list of pointers to each card that matches \p cardClass.
    //! \param cardClass The class of the card.
    //! \return A list of pointers to each card that matches \p cardClass.
    std::vector<Card*> FindCardByClass(CardClass cardClass);

    //! Returns a list of pointers to each card that matches \p cardSet.
    //! \param cardSet The set of the card.
    //! \return A list of pointers to each card that matches \p cardSet.
    std::vector<Card*> FindCardBySet(CardSet cardSet);

    //! Returns a list of pointers to each card that matches \p cardType.
    //! \param cardType The type of the card.
    //! \return A list of pointers to each card that matches \p cardType.
    std::vector<Card*> FindCardByType(CardType cardType);

    //! Returns a list of pointers to each card that matches \p race.
    //! \param race The race of the card.
    //! \return A list of pointers to each card that matches \p race.
    std::vector<Card*> FindCardByRace(Race race);

    //! Returns a pointer to card that matches \p name.
    //! \param name The name of the card.
    //! \return A pointer to card that matches \p name.
    Card* FindCardByName(const std::string& name);

    //! Returns a list of pointers to each card whose cost is between \p minVal and \p maxVal.
    //! \param minVal The minimum cost value of the card.
    //! \param maxVal The maximum cost value of the card.
    //! \return A list of pointers to each card whose cost is between \p minVal and \p maxVal.
    std::vector<Card*> FindCardByCost(size_t minVal, size_t maxVal);

    //! Returns a list of pointers to each card whose attack is between \p minVal and \p maxVal.
    //! \param minVal The minimum attack value of the card.
    //! \param maxVal The maximum attack value of the card.
    //! \return A list of pointers to each card whose attack is between \p minVal and \p maxVal.
    std::vector<Card*> FindCardByAttack(size_t minVal, size_t maxVal);

    //! Returns a list of pointers to each card whose health is between \p minVal and \p maxVal.
    //! \param minVal The minimum health value of the card.
    //! \param maxVal The maximum health value of the card.
    //! \return A list of pointers to each card whose health is between \p minVal and \p maxVal.
    std::vector<Card*> FindCardByHealth(size_t minVal, size_t maxVal);

    //! Returns a list of pointers to each card whose spell damage is between \p minVal and \p maxVal.
    //! \param minVal The minimum spell damage value of the card.
    //! \param maxVal The maximum spell damage value of the card.
    //! \return A list of pointers to each card whose spell damage is between \p minVal and \p maxVal.
    std::vector<Card*> FindCardBySpellDamage(size_t minVal, size_t maxVal);

    //! Returns a list of pointers to each card that has \p mechanics.
    //! \param mechanics The mechanics of the card.
    //! \return A list of pointers to each card that has \p mechanics.
    std::vector<Card*> FindCardByMechanics(std::vector<GameTag> mechanics);

    //! Returns a pointer to hero card that matches \p cardClass.
    //! \param cardClass The class of the card.
    //! \return A pointer to hero card that matches \p cardClass.
    const Card* GetHeroCard(CardClass cardClass);

    //! Returns a pointer to default hero power card that matches \p cardClass.
    //! \param cardClass The class of the card.
    //! \return A pointer to default hero power card that matches \p cardClass.
    const Card* GetDefaultHeroPower(CardClass cardClass);

 private:
    //! Constructor that loads card data.
    Cards();

    //! Destructor.
    ~Cards();

    //! Deleted copy constructor.
    Cards(const Cards&) = delete;

    //! Deleted move constructor.
    Cards(Cards&&) = delete;

    //! Deleted copy assignment operator.
    Cards& operator=(const Cards&) = delete;

    //! Deleted move assignment operator.
    Cards& operator=(Cards&&) = delete;

    static Cards* m_instance;

    std::vector<Card*> m_cards;
};
}

#endif