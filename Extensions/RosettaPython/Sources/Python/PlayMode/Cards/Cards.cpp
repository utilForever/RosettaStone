// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Python/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

using namespace RosettaStone;
using namespace PlayMode;

using CardListCasterBase =
    pybind11::detail::list_caster<std::vector<Card*>, Card*>;

namespace pybind11::detail
{
template <>
struct type_caster<std::vector<Card*>> : CardListCasterBase
{
    static handle cast(const std::vector<Card*>& src, return_value_policy,
                       handle parent)
    {
        return CardListCasterBase::cast(src, return_value_policy::reference,
                                        parent);
    }

    static handle cast(const std::vector<Card*>* src,
                       return_value_policy policy, handle parent)
    {
        return cast(*src, policy, parent);
    }
};
}  // namespace pybind11::detail

namespace
{
struct CardsWrapper
{
    static const std::vector<Card*>& GetAllCards()
    {
        return Cards::GetInstance().GetAllCards();
    }

    static std::vector<Card*> GetAllStandardCards()
    {
        return Cards::GetInstance().GetAllStandardCards();
    }

    static std::vector<Card*> GetAllWildCards()
    {
        return Cards::GetInstance().GetAllWildCards();
    }

    static Card* FindCardByID(const std::string& id)
    {
        return Cards::GetInstance().FindCardByID(id);
    }

    static Card* FindCardByDbfID(int dbfID)
    {
        return Cards::GetInstance().FindCardByDbfID(dbfID);
    }

    static std::vector<Card*> FindCardByRarity(Rarity rarity)
    {
        return Cards::GetInstance().FindCardByRarity(rarity);
    }

    static std::vector<Card*> FindCardByClass(CardClass cardClass)
    {
        return Cards::GetInstance().FindCardByClass(cardClass);
    }

    static std::vector<Card*> FindCardBySet(CardSet cardSet)
    {
        return Cards::GetInstance().FindCardBySet(cardSet);
    }

    static std::vector<Card*> FindCardByType(CardType cardType)
    {
        return Cards::GetInstance().FindCardByType(cardType);
    }

    static std::vector<Card*> FindCardByRace(Race race)
    {
        return Cards::GetInstance().FindCardByRace(race);
    }

    static Card* FindCardByName(const std::string& name)
    {
        return Cards::GetInstance().FindCardByName(name);
    }

    static std::vector<Card*> FindCardByCost(int minVal, int maxVal)
    {
        return Cards::GetInstance().FindCardByCost(minVal, maxVal);
    }

    static std::vector<Card*> FindCardByAttack(int minVal, int maxVal)
    {
        return Cards::GetInstance().FindCardByAttack(minVal, maxVal);
    }

    static std::vector<Card*> FindCardByHealth(int minVal, int maxVal)
    {
        return Cards::GetInstance().FindCardByHealth(minVal, maxVal);
    }

    static std::vector<Card*> FindCardBySpellPower(int minVal, int maxVal)
    {
        return Cards::GetInstance().FindCardBySpellPower(minVal, maxVal);
    }

    static std::vector<Card*> FindCardByGameTag(std::vector<GameTag> gameTags)
    {
        return Cards::GetInstance().FindCardByGameTag(gameTags);
    }

    static Card* GetHeroCard(CardClass cardClass)
    {
        return Cards::GetInstance().GetHeroCard(cardClass);
    }

    static Card* GetDefaultHeroPower(CardClass cardClass)
    {
        return Cards::GetInstance().GetDefaultHeroPower(cardClass);
    }
};
}  // namespace

void AddCards(pybind11::module& m)
{
    pybind11::class_<SearchFilter>(
        m, "SearchFilter",
        R"pbdoc(This structure stores the filter value for searching the card.)pbdoc")
        .def_readwrite("rarity", &SearchFilter::rarity)
        .def_readwrite("player_class", &SearchFilter::playerClass)
        .def_readwrite("card_type", &SearchFilter::cardType)
        .def_readwrite("race", &SearchFilter::race)
        .def_readwrite("game_tag", &SearchFilter::gameTag)
        .def_readwrite("name", &SearchFilter::name)
        .def_readwrite("cost_min", &SearchFilter::costMin)
        .def_readwrite("cost_max", &SearchFilter::costMax)
        .def_readwrite("attack_min", &SearchFilter::attackMin)
        .def_readwrite("attack_max", &SearchFilter::attackMax)
        .def_readwrite("health_min", &SearchFilter::healthMin)
        .def_readwrite("health_max", &SearchFilter::healthMax);

    pybind11::class_<CardsWrapper>(
        m, "Cards",
        R"pbdoc(This class stores a list of cards and provides several search methods.)pbdoc")
        .def_static("all_cards", &CardsWrapper::GetAllCards,
                    R"pbdoc(Returns a list of all cards.)pbdoc")
        .def_static("all_standard_cards", &CardsWrapper::GetAllStandardCards,
                    R"pbdoc(Returns a list of all standard cards.)pbdoc")
        .def_static("all_wild_cards", &CardsWrapper::GetAllWildCards,
                    R"pbdoc(Returns a list of all wild cards.)pbdoc")
        .def_static("find_card_by_id", &CardsWrapper::FindCardByID,
                    R"pbdoc(Returns a card that matches id.

                    Parameters
                    ----------
                    id : The ID of the card.)pbdoc",
                    pybind11::return_value_policy::reference,
                    pybind11::arg("id"))
        .def_static("find_card_by_dbf_id", &CardsWrapper::FindCardByDbfID,
                    R"pbdoc(Returns a card that matches dbf_id.

                    Parameters
                    ----------
                    dbf_id : The dbfID of the card.)pbdoc",
                    pybind11::return_value_policy::reference,
                    pybind11::arg("dbf_id"))
        .def_static("find_card_by_rarity", &CardsWrapper::FindCardByRarity,
                    R"pbdoc(Returns a list of cards that matches rarity.

                    Parameters
                    ----------
                    rarity : The rarity of the card.)pbdoc",
                    pybind11::arg("rarity"))
        .def_static("find_card_by_class", &CardsWrapper::FindCardByClass,
                    R"pbdoc(Returns a list of cards that matches card_class.

                    Parameters
                    ----------
                    card_class : The class of the card.)pbdoc",
                    pybind11::arg("card_class"))
        .def_static("find_card_by_set", &CardsWrapper::FindCardBySet,
                    R"pbdoc(Returns a list of cards that matches card_set.

                    Parameters
                    ----------
                    card_set : The set of the card.)pbdoc",
                    pybind11::arg("card_set"))
        .def_static("find_card_by_type", &CardsWrapper::FindCardByType,
                    R"pbdoc(Returns a list of cards that matches card_type.

                    Parameters
                    ----------
                    card_type : The type of the card.)pbdoc",
                    pybind11::arg("card_type"))
        .def_static("find_card_by_race", &CardsWrapper::FindCardByRace,
                    R"pbdoc(Returns a list of cards that matches race.

                    Parameters
                    ----------
                    race : The race of the card.)pbdoc",
                    pybind11::arg("race"))
        .def_static("find_card_by_name", &CardsWrapper::FindCardByName,
                    R"pbdoc(Returns a card that matches name.

                    Parameters
                    ----------
                    name : The name of the card.)pbdoc",
                    pybind11::return_value_policy::reference,
                    pybind11::arg("name"))
        .def_static(
            "find_card_by_cost", &CardsWrapper::FindCardByCost,
            R"pbdoc(Returns a list of cards whose cost is between min_val and max_val.

            Parameters
            ----------
            min_val : The minimum cost value of the card.
            max_val : The maximum cost value of the card.)pbdoc",
            pybind11::arg("min_val"), pybind11::arg("max_val"))
        .def_static(
            "find_card_by_attack", &CardsWrapper::FindCardByAttack,
            R"pbdoc(Returns a list of cards whose cost is between min_val and max_val.

            Parameters
            ----------
            min_val : The minimum cost value of the card.
            max_val : The maximum cost value of the card.)pbdoc",
            pybind11::arg("min_val"), pybind11::arg("max_val"))
        .def_static(
            "find_card_by_health", &CardsWrapper::FindCardByHealth,
            R"pbdoc(Returns a list of cards whose health is between min_val and max_val.

            Parameters
            ----------
            min_val : The minimum health value of the card.
            max_val : The maximum health value of the card.)pbdoc",
            pybind11::arg("min_val"), pybind11::arg("max_val"))
        .def_static(
            "find_card_by_spell_power", &CardsWrapper::FindCardBySpellPower,
            R"pbdoc(Returns a list of cards whose spell power is between min_val and max_val

            Parameters
            ----------
            min_val : The minimum spell power value of the card.
            max_val : The maximum spell power value of the card.)pbdoc",
            pybind11::arg("min_val"), pybind11::arg("max_val"))
        .def_static("find_card_by_game_tag", &CardsWrapper::FindCardByGameTag,
                    R"pbdoc(Returns a list of cards that has game_tags.

                    Parameters
                    ----------
                    game_tags : A list of game tag of the card.)pbdoc",
                    pybind11::arg("game_tags"))
        .def_static("hero_card", &CardsWrapper::GetHeroCard,
                    R"pbdoc(Returns a hero card that matches card_class.

                    Parameters
                    ----------
                    card_class : The class of the card.)pbdoc",
                    pybind11::return_value_policy::reference,
                    pybind11::arg("card_class"))
        .def_static(
            "default_hero_power", &CardsWrapper::GetDefaultHeroPower,
            R"pbdoc(Returns a default hero power card that matches card_class.

            Parameters
            ----------
            card_class : The class of the card.)pbdoc",
            pybind11::return_value_policy::reference,
            pybind11::arg("card_class"));
}
