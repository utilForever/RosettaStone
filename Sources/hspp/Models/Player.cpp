// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Commons/Constants.hpp>
#include <hspp/Managers/GameAgent.hpp>
#include <hspp/Models/HeroPower.hpp>
#include <hspp/Models/Minion.hpp>
#include <hspp/Models/Player.hpp>
#include <hspp/Models/Weapon.hpp>

namespace Hearthstonepp
{
Player::Player() : m_id(USER_INVALID)
{
    m_field.SetOwner(*this);
    m_hand.SetOwner(*this);
}

Player::~Player()
{
    FreeMemory();
}

bool Player::operator==(const Player& p) const
{
    return m_id == p.m_id;
}

bool Player::operator!=(const Player& p) const
{
    return !(m_id == p.m_id);
}

std::string Player::GetNickname() const
{
    return m_nickname;
}

void Player::SetNickname(std::string nickname)
{
    m_nickname = nickname;
}

PlayerType Player::GetPlayerType() const
{
    return m_playerType;
}

void Player::SetPlayerType(PlayerType type)
{
    m_playerType = type;
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

Battlefield& Player::GetField()
{
    return m_field;
}

Deck& Player::GetDeck()
{
    return m_deck;
}

Hand& Player::GetHand()
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

GameAgent* Player::GetGameAgent() const
{
    return m_gameAgent;
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

void Player::AddHeroAndPower(Card&& heroCard, Card&& powerCard)
{
    auto* gameAgent = GetGameAgent();

    m_hero = new Hero(gameAgent, heroCard);
    m_hero->heroPower = new HeroPower(gameAgent, powerCard);
}

void Player::FreeMemory()
{
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
}  // namespace Hearthstonepp
