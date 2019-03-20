// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Games/GameAgent.hpp>
#include <Rosetta/Models/HeroPower.hpp>
#include <Rosetta/Models/Player.hpp>

namespace Hearthstonepp
{
Player::Player() : m_id(USER_INVALID)
{
    m_field.SetOwner(*this);
    m_deck.SetOwner(*this);
    m_graveyard.SetOwner(*this);
    m_hand.SetOwner(*this);
}

Player::~Player()
{
    delete m_hero;
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

std::size_t Player::GetID() const
{
    return m_id;
}

void Player::SetID(std::size_t id)
{
    m_id = id;
}

Game* Player::GetGame() const
{
    return m_game;
}

void Player::SetGame(Game* game)
{
    m_game = game;
}

Battlefield& Player::GetField()
{
    return m_field;
}

Deck& Player::GetDeck()
{
    return m_deck;
}

Graveyard& Player::GetGraveyard()
{
    return m_graveyard;
}

Hand& Player::GetHand()
{
    return m_hand;
}

Hero* Player::GetHero() const
{
    return m_hero;
}

IPolicy& Player::GetPolicy() const
{
    return *m_policy;
}

void Player::SetPolicy(IPolicy* policy)
{
    m_policy = policy;
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
    m_hero =
        dynamic_cast<Hero*>(Entity::GetFromCard(*this, std::move(heroCard)));
    m_hero->heroPower = dynamic_cast<HeroPower*>(
        Entity::GetFromCard(*this, std::move(powerCard)));
}
}  // namespace Hearthstonepp
