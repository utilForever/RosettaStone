// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Models/HeroPower.hpp>
#include <Rosetta/Models/Player.hpp>

namespace RosettaStone
{
Player::Player() : playerID(USER_INVALID)
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

int Player::GetGameTag(GameTag tag) const
{
    if (m_gameTags.find(tag) == m_gameTags.end())
    {
        return 0;
    }

    return m_gameTags.at(tag);
}

void Player::SetGameTag(GameTag tag, int value)
{
    m_gameTags.insert_or_assign(tag, value);
}

int Player::GetTotalMana() const
{
    return GetGameTag(GameTag::RESOURCES);
}

void Player::SetTotalMana(int value)
{
    SetGameTag(GameTag::RESOURCES, value);
}

int Player::GetUsedMana() const
{
    return GetGameTag(GameTag::RESOURCES_USED);
}

void Player::SetUsedMana(int value)
{
    SetGameTag(GameTag::RESOURCES_USED, value);
}

int Player::GetTemporaryMana() const
{
    return GetGameTag(GameTag::TEMP_RESOURCES);
}

void Player::SetTemporaryMana(int value)
{
    SetGameTag(GameTag::TEMP_RESOURCES, value);
}

void Player::AddHeroAndPower(Card&& heroCard, Card&& powerCard)
{
    m_hero =
        dynamic_cast<Hero*>(Entity::GetFromCard(*this, std::move(heroCard)));
    m_hero->heroPower = dynamic_cast<HeroPower*>(
        Entity::GetFromCard(*this, std::move(powerCard)));
}
}  // namespace RosettaStone
