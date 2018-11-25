// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Accounts/Player.h>
#include <hspp/Cards/Cards.h>
#include <hspp/Commons/Constants.h>

namespace Hearthstonepp
{
Player::Player() : m_id(USER_INVALID)
{
    cards.reserve(MAXIMUM_NUM_CARDS_IN_DECK);
    field.reserve(FIELD_SIZE);
    hand.reserve(MAXIMUM_NUM_CARDS_IN_HAND);
}

Player::~Player()
{
    FreeMemory();
}

std::string Player::GetNickname() const
{
    return m_nickname;
}

void Player::SetNickname(std::string nickname)
{
    m_nickname = nickname;
}

BYTE Player::GetID() const
{
    return m_id;
}

void Player::SetID(BYTE id)
{
    m_id = id;
}

BYTE Player::GetAvailableMana() const
{
    return m_availableMana;
}

void Player::SetAvailableMana(BYTE mana)
{
    m_availableMana = mana;
}

BYTE Player::GetMaximumMana() const
{
    return m_maximumMana;
}

void Player::SetMaximumMana(BYTE mana)
{
    m_maximumMana = mana;
}

BYTE Player::GetNumCardAfterExhaust() const
{
    return m_numCardAfterExhaust;
}

void Player::SetNumCardAfterExhaust(BYTE numCard)
{
    m_numCardAfterExhaust = numCard;
}

GameAgent& Player::GetGameAgent() const
{
    return *m_gameAgent;
}

void Player::SetGameAgent(GameAgent* agent)
{
    m_gameAgent = agent;
}

Player& Player::GetOpponent() const
{
    return *m_opponent;
}

void Player::SetOpponent(Player* player)
{
    m_opponent = player;
}

void Player::SetDeck(Deck* deck)
{
    for (auto& card : deck->GetPrimitiveDeck())
    {
        if (card.id.empty())
        {
            continue;
        }

        Entity* entity = nullptr;
        switch (card.cardType)
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

void Player::AddHeroAndPower(Card heroCard, Card powerCard)
{
    hero = new Hero(heroCard);
    hero->heroPower = new HeroPower(powerCard);
}

void Player::FreeMemory()
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

    delete hero;
}
}  // namespace Hearthstonepp
