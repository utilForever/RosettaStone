/*************************************************************************
> File Name: Card.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card class that stores card information.
> Created Time: 2017/08/21
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_CARD_H
#define HEARTHSTONEPP_CARD_H

#include <Commons/Macros.h>
#include <Enchants/Power.h>
#include <Enums/CardEnums.h>

#include <map>
#ifndef HEARTHSTONEPP_MACOSX
#include <optional>
#else
#include <experimental/optional>
#endif
#include <string>
#include <vector>

namespace Hearthstonepp
{
struct Power;

struct Card
{
    Card() = default;
    virtual ~Card() = default;

    void Initialize();

    bool HasMechanic(GameTag mechanic) const;

    unsigned int GetMaxAllowedInDeck() const;

    virtual void ShowBriefInfo() const;

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

#ifndef HEARTHSTONEPP_MACOSX
    std::optional<size_t> attack;
    std::optional<size_t> health;
    std::optional<size_t> spellDamage;;
    std::optional<size_t> durability;
#else
    std::experimental::optional<size_t> attack;
    std::experimental::optional<size_t> health;
    std::experimental::optional<size_t> spellDamage;;
    std::experimental::optional<size_t> durability;
#endif
    size_t cost;


    std::vector<GameTag> mechanics;
    std::map<PlayReq, int> playRequirements;
    std::vector<std::string> entourages;

    Power* power;

    unsigned int maxAllowedInDeck;
    bool isCollectible;
};
}  // namespace Hearthstonepp

#endif
