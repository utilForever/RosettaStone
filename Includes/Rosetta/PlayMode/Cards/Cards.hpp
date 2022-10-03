// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_CARDS_HPP
#define ROSETTASTONE_PLAYMODE_CARDS_HPP

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Cards/Card.hpp>

#include <vector>

namespace RosettaStone::PlayMode
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
    GameTag gameTag = GameTag::INVALID;

    std::string name;
    int costMin = 0, costMax = 0;
    int attackMin = 0, attackMax = 0;
    int healthMin = 0, healthMax = 0;
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
    static const std::vector<Card*>& GetAllCards();

    //! Returns a list of standard cards that matches specific card class.
    //! \param cardClass The card class to match.
    //! \return A list of standard cards that matches specific card class.
    static const std::vector<Card*>& GetStandardCards(CardClass cardClass);

    //! Returns a list of wild cards that matches specific card class.
    //! \param cardClass The card class to match.
    //! \return A list of wild cards that matches specific card class.
    static const std::vector<Card*>& GetWildCards(CardClass cardClass);

    //! Returns a list of all standard cards.
    //! \return A list of all standard cards.
    static const std::vector<Card*>& GetAllStandardCards();

    //! Returns a list of all wild cards.
    //! \return A list of all wild cards.
    static const std::vector<Card*>& GetAllWildCards();

    //! Returns a list of discover cards.
    //! \param baseClass The base class of the player.
    //! \param format The format type of the game.
    //! \return A list of discover cards.
    static const std::vector<Card*> GetDiscoverCards(CardClass baseClass,
                                                     FormatType format);

    //! Returns a list of basic Totem cards.
    //! \return A list of basic Totem cards.
    static std::vector<Card*> GetBasicTotems();

    //! Returns a list of Lackey cards.
    //! \return A list of Lackey cards.
    static std::vector<Card*> GetLackeys();

    //! Returns a list of Poison cards.
    //! \return A list of Poison cards.
    static std::vector<Card*> GetPoisons();

    //! Returns a card that matches \p id.
    //! \param id The ID of the card.
    //! \return A card that matches \p id.
    static Card* FindCardByID(const std::string_view& id);

    //! Returns a card that matches \p dbfID.
    //! \param dbfID The dbfID of the card.
    //! \return A card that matches \p dbfID.
    static Card* FindCardByDbfID(int dbfID);

    //! Returns a list of cards that matches \p rarity.
    //! \param rarity The rarity of the card.
    //! \return A list of cards that matches condition.
    static std::vector<Card*> FindCardByRarity(Rarity rarity);

    //! Returns a list of cards that matches \p cardClass.
    //! \param cardClass The class of the card.
    //! \return A list of cards that matches condition.
    static std::vector<Card*> FindCardByClass(CardClass cardClass);

    //! Returns a list of cards that matches \p cardSet.
    //! \param cardSet The set of the card.
    //! \return A list of cards that matches condition.
    static std::vector<Card*> FindCardBySet(CardSet cardSet);

    //! Returns a list of cards that matches \p cardType.
    //! \param cardType The type of the card.
    //! \return A list of cards that matches condition.
    static std::vector<Card*> FindCardByType(CardType cardType);

    //! Returns a list of cards that matches \p race.
    //! \param race The race of the card.
    //! \return A list of cards that matches condition.
    static std::vector<Card*> FindCardByRace(Race race);

    //! Returns a card that matches \p name and \p format.
    //! \param name The name of the card.
    //! \param format The format type of the game.
    //! \return A card that matches condition.
    static Card* FindCardByName(const std::string_view& name,
                                FormatType format = FormatType::WILD);

    //! Returns a list of cards whose cost is between \p minVal and \p maxVal.
    //! \param minVal The minimum cost value of the card.
    //! \param maxVal The maximum cost value of the card.
    //! \return A list of cards that matches condition.
    static std::vector<Card*> FindCardByCost(int minVal, int maxVal);

    //! Returns a list of cards whose attack is between \p minVal and \p maxVal.
    //! \param minVal The minimum attack value of the card.
    //! \param maxVal The maximum attack value of the card.
    //! \return A list of cards that matches condition.
    static std::vector<Card*> FindCardByAttack(int minVal, int maxVal);

    //! Returns a list of cards whose health is between \p minVal and \p maxVal.
    //! \param minVal The minimum health value of the card.
    //! \param maxVal The maximum health value of the card.
    //! \return A list of cards that matches condition.
    static std::vector<Card*> FindCardByHealth(int minVal, int maxVal);

    //! Returns a list of cards whose spell power is between
    //! \p minVal and \p maxVal.
    //! \param minVal The minimum spell power value of the card.
    //! \param maxVal The maximum spell power value of the card.
    //! \return A list of cards that matches condition.
    static std::vector<Card*> FindCardBySpellPower(int minVal, int maxVal);

    //! Returns a list of cards that has \p gameTags.
    //! \param gameTags A list of game tag of the card.
    //! \return A list of cards that matches condition.
    static std::vector<Card*> FindCardByGameTag(std::vector<GameTag> gameTags);

    //! Returns a hero card that matches \p cardClass.
    //! \param cardClass The class of the card.
    //! \return A hero card that matches condition.
    static Card* GetHeroCard(CardClass cardClass);

    //! Returns a default hero power card that matches \p cardClass.
    //! \param cardClass The class of the card.
    //! \return A default hero power card that matches condition.
    static Card* GetDefaultHeroPower(CardClass cardClass);

 private:
    //! Constructor: Loads card data.
    Cards();

    //! Destructor: Releases card data.
    ~Cards();

    static std::vector<Card*> m_cards;
    static std::array<std::vector<Card*>, NUM_PLAYER_CLASS> m_standardCards;
    static std::array<std::vector<Card*>, NUM_PLAYER_CLASS> m_wildCards;
    static std::vector<Card*> m_allStandardCards;
    static std::vector<Card*> m_allWildCards;
    static std::vector<Card*> m_allClassicCards;
    static std::vector<Card*> m_basicTotems;
    static std::vector<Card*> m_lackeys;
    static std::vector<Card*> m_poisons;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_CARDS_HPP
