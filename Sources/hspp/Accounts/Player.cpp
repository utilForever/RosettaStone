// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Accounts/Player.h>
#include <hspp/Commons/Constants.h>
#include <hspp/Tasks/TaskMeta.h>

namespace Hearthstonepp
{
Player::Player(const Account* account, const Deck* deck)
    : id(USER_INVALID),
      totalMana(0),
      existMana(0),
      exhausted(0),
      email(account->GetEmail()),
      hero(nullptr),
      power(nullptr)
{
    Cards* cardsInstance = Cards::GetInstance();
    const CardClass cardclass = deck->GetClass();

    const Card* heroCard = cardsInstance->GetHeroCard(cardclass);
    if (heroCard != nullptr)
    {
        hero = new Hero(heroCard);
    }

    const Card* powerCard = cardsInstance->GetDefaultHeroPower(cardclass);
    if (powerCard != nullptr)
    {
        power = new HeroPower(powerCard);
    }

    for (auto& card : deck->GetPrimitiveDeck())
    {
        if (card == nullptr)
        {
            continue;
        }

        Entity* entity = nullptr;
        switch (card->cardType)
        {
            case CardType::MINION:
                entity = new Minion(card);
                break;
            case CardType::WEAPON:
                entity = new Weapon(card);
                break;
            default:
                entity = new Entity(card);
                break;
        }

        cards.emplace_back(entity);
    }
}

Player::~Player()
{
    for (auto& card : cards)
    {
        delete card;
    }
    cards.clear();

    for (auto& minion : field)
    {
        delete minion;
    }
    field.clear();

    for (auto& card : hand)
    {
        delete card;
    }
    hand.clear();

    for (auto& spell : usedSpell)
    {
        delete spell;
    }
    usedSpell.clear();

    for (auto& minion : usedMinion)
    {
        delete minion;
    }
    usedMinion.clear();
}

Player::Player(const Player& p)
{
    *this = p;
}

Player::Player(Player&& p)
{
    *this = std::move(p);
}

Player& Player::operator=(const Player& p)
{
    hero = p.hero;
    power = p.power;
    field = p.field;
    hand = p.hand;
    usedSpell = p.usedSpell;
    usedMinion = p.usedMinion;

    return *this;
}

Player& Player::operator=(Player&& p)
{
    hero = p.hero;
    power = p.power;
    field = std::move(p.field);
    hand = std::move(p.hand);
    usedSpell = std::move(p.usedSpell);
    usedMinion = std::move(p.usedMinion);

    return *this;
}
}  // namespace Hearthstonepp
