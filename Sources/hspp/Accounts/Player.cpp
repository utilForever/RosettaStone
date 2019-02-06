// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Accounts/Player.hpp>
#include <hspp/Cards/HeroPower.hpp>
#include <hspp/Cards/Minion.hpp>
#include <hspp/Cards/Weapon.hpp>
#include <hspp/Commons/Constants.hpp>

namespace Hearthstonepp
{
Player::Player() : m_id(USER_INVALID)
{
    m_deck.reserve(MAXIMUM_NUM_CARDS_IN_DECK);
    m_field.reserve(FIELD_SIZE);
    m_hand.reserve(MAXIMUM_NUM_CARDS_IN_HAND);
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

Hero* Player::GetHero() const
{
    return m_hero;
}

std::vector<Entity*>& Player::GetDeck()
{
    return m_deck;
}

std::vector<Character*>& Player::GetField()
{
    return m_field;
}

std::vector<Entity*>& Player::GetHand()
{
    return m_hand;
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

        m_deck.emplace_back(entity);
    }
}

void Player::AddHeroAndPower(Card&& heroCard, Card&& powerCard)
{
    m_hero = new Hero(heroCard);
    m_hero->heroPower = new HeroPower(powerCard);
}

void Player::FreeMemory()
{
    for (auto& card : m_deck)
    {
        delete card;
    }
    m_deck.clear();

    for (auto& minion : m_field)
    {
        delete minion;
    }
    m_field.clear();

    for (auto& card : m_hand)
    {
        delete card;
    }
    m_hand.clear();

    for (auto& spell : m_playedSpell)
    {
        delete spell;
    }
    m_playedSpell.clear();

    for (auto& minion : m_playedMinion)
    {
        delete minion;
    }
    m_playedMinion.clear();

    delete m_hero;
}

IPolicy& Player::GetPolicy() const
{
    return *m_policy;
}

void Player::SetPolicy(IPolicy* policy)
{
    m_policy = policy;
}
}  // namespace Hearthstonepp
