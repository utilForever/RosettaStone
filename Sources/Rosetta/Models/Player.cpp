// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Commons/Utils.hpp>
#include <Rosetta/Models/HeroPower.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SecretZone.hpp>
#include <Rosetta/Zones/SetasideZone.hpp>

namespace RosettaStone
{
Player::Player() : playerID(USER_INVALID)
{
    m_deckZone = new DeckZone(this);
    m_fieldZone = new FieldZone(this);
    m_graveyardZone = new GraveyardZone(this);
    m_handZone = new HandZone(this);
    m_secretZone = new SecretZone(this);
    m_setasideZone = new SetasideZone(this);
}

Player::~Player()
{
    delete m_setasideZone;
    delete m_secretZone;
    delete m_handZone;
    delete m_graveyardZone;
    delete m_fieldZone;
    delete m_deckZone;

    // TODO: This code will refactor.
    if (m_hero)
    {
        delete m_hero->heroPower;
    }
    delete m_hero;
}

void Player::RefCopy(const Player& rhs)
{
    nickname = rhs.nickname;
    playerType = rhs.playerType;
    playerID = rhs.playerID;

    playState = rhs.playState;
    mulliganState = rhs.mulliganState;
    choice = rhs.choice;

    m_hero = rhs.m_hero;
    opponent = rhs.opponent;

    m_deckZone = rhs.m_deckZone;
    m_fieldZone = rhs.m_fieldZone;
    m_graveyardZone = rhs.m_graveyardZone;
    m_handZone = rhs.m_handZone;
    m_secretZone = rhs.m_secretZone;
    m_setasideZone = rhs.m_setasideZone;

    m_gameTags = rhs.m_gameTags;
    currentSpellPower = rhs.currentSpellPower;
}

FieldZone* Player::GetFieldZone() const
{
    return m_fieldZone;
}

DeckZone* Player::GetDeckZone() const
{
    return m_deckZone;
}

GraveyardZone* Player::GetGraveyardZone() const
{
    return m_graveyardZone;
}

HandZone* Player::GetHandZone() const
{
    return m_handZone;
}

SecretZone* Player::GetSecretZone() const
{
    return m_secretZone;
}

SetasideZone* Player::GetSetasideZone() const
{
    return m_setasideZone;
}

Hero* Player::GetHero() const
{
    return m_hero;
}

HeroPower& Player::GetHeroPower() const
{
    return *m_hero->heroPower;
}

Weapon& Player::GetWeapon() const
{
    return *m_hero->weapon;
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

int Player::GetTimeOut()
{
    return GetGameTag(GameTag::TIMEOUT) + playerAuraEffects[GameTag::TIMEOUT];
}

void Player::SetTimeOut(int value)
{
    SetGameTag(GameTag::TIMEOUT, value);
}

bool Player::IsHealingDoesDamage()
{
    return playerAuraEffects[GameTag::HEALING_DOES_DAMAGE] > 0;
}

int Player::GetTotalMana() const
{
    return GetGameTag(GameTag::RESOURCES);
}

void Player::SetTotalMana(int amount)
{
    SetGameTag(GameTag::RESOURCES, amount);
}

int Player::GetUsedMana() const
{
    return GetGameTag(GameTag::RESOURCES_USED);
}

void Player::SetUsedMana(int amount)
{
    SetGameTag(GameTag::RESOURCES_USED, amount);
}

int Player::GetTemporaryMana() const
{
    return GetGameTag(GameTag::TEMP_RESOURCES);
}

void Player::SetTemporaryMana(int amount)
{
    SetGameTag(GameTag::TEMP_RESOURCES, amount);
}

int Player::GetOverloadOwed() const
{
    return GetGameTag(GameTag::OVERLOAD_OWED);
}

void Player::SetOverloadOwed(int amount)
{
    SetGameTag(GameTag::OVERLOAD_OWED, amount);
}

int Player::GetOverloadLocked() const
{
    return GetGameTag(GameTag::OVERLOAD_LOCKED);
}

void Player::SetOverloadLocked(int amount)
{
    SetGameTag(GameTag::OVERLOAD_LOCKED, amount);
}

int Player::GetRemainingMana() const
{
    return GetTotalMana() + GetTemporaryMana() -
           (GetUsedMana() + GetOverloadLocked());
}

bool Player::IsComboActive() const
{
    return GetGameTag(GameTag::COMBO_ACTIVE) == 1;
}

void Player::SetComboActive(bool isActive)
{
    SetGameTag(GameTag::COMBO_ACTIVE, isActive ? 1 : 0);
}

int Player::GetNumMinionsPlayedThisTurn() const
{
    return GetGameTag(GameTag::NUM_MINIONS_PLAYED_THIS_TURN);
}

void Player::SetNumMinionsPlayedThisTurn(int value)
{
    SetGameTag(GameTag::NUM_MINIONS_PLAYED_THIS_TURN, value);
}

int Player::GetNumFriendlyMinionsDiedThisTurn() const
{
    return GetGameTag(GameTag::NUM_FRIENDLY_MINIONS_THAT_DIED_THIS_TURN);
}

void Player::SetNumFriendlyMinionsDiedThisTurn(int value)
{
    SetGameTag(GameTag::NUM_FRIENDLY_MINIONS_THAT_DIED_THIS_TURN, value);
}

void Player::AddHeroAndPower(Card* heroCard, Card* powerCard)
{
    Weapon* weapon = nullptr;
    AuraEffects* auraEffects = nullptr;

    if (m_hero != nullptr)
    {
        m_setasideZone->MoveTo(m_hero, m_setasideZone->GetCount());
        m_setasideZone->MoveTo(m_hero->heroPower, m_setasideZone->GetCount());

        if (m_hero->weapon != nullptr)
        {
            weapon = m_hero->weapon;
        }

        auraEffects = m_hero->auraEffects;
    }

    m_hero = dynamic_cast<Hero*>(GetFromCard(this, heroCard));
    m_hero->SetZoneType(ZoneType::PLAY);

    m_hero->heroPower = dynamic_cast<HeroPower*>(GetFromCard(this, powerCard));

    m_hero->weapon = weapon;
    m_hero->auraEffects = auraEffects;
}
}  // namespace RosettaStone
