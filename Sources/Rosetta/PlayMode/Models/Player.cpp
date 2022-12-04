// Copyright (c) 2017-2021 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/HeroPower.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/GraveyardZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SecretZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

namespace RosettaStone::PlayMode
{
Player::Player() : playerID(-1)
{
    m_deckZone = std::make_unique<DeckZone>(this);
    m_fieldZone = std::make_unique<FieldZone>(this);
    m_graveyardZone = std::make_unique<GraveyardZone>(this);
    m_handZone = std::make_unique<HandZone>(this);
    m_secretZone = std::make_unique<SecretZone>(this);
    m_setasideZone = std::make_unique<SetasideZone>(this);
}

Player::~Player()
{
    // TODO: This code will refactor.
    if (m_hero)
    {
        delete m_hero->heroPower;
    }

    delete m_hero;
}

FieldZone* Player::GetFieldZone() const
{
    return m_fieldZone.get();
}

DeckZone* Player::GetDeckZone() const
{
    return m_deckZone.get();
}

GraveyardZone* Player::GetGraveyardZone() const
{
    return m_graveyardZone.get();
}

HandZone* Player::GetHandZone() const
{
    return m_handZone.get();
}

SecretZone* Player::GetSecretZone() const
{
    return m_secretZone.get();
}

SetasideZone* Player::GetSetasideZone() const
{
    return m_setasideZone.get();
}

Hero* Player::GetHero() const
{
    return m_hero;
}

void Player::SetHero(Hero* hero)
{
    m_hero = hero;
}

HeroPower& Player::GetHeroPower() const
{
    return *m_hero->heroPower;
}

Weapon& Player::GetWeapon() const
{
    return *m_hero->weapon;
}

int Player::GetCurrentSpellPower() const
{
    int value = 0;

    m_fieldZone->ForEach([&](Placeable* placeable) {
        if (const auto minion = dynamic_cast<Minion*>(placeable);
            minion && !minion->IsUntouchable())
        {
            value += minion->GetSpellPower();
        }
    });

    value += GetHero()->GetSpellPower();
    value += GetGameTag(GameTag::SPELLPOWER);
    value += playerAuraEffects.GetValue(GameTag::SPELLPOWER);

    return value;
}

int Player::GetExtraSpellPower(SpellSchool spellSchool) const
{
    int value = 0;

    m_fieldZone->ForEach([&](Placeable* placeable) {
        if (const auto minion = dynamic_cast<Minion*>(placeable);
            minion && !minion->IsUntouchable())
        {
            switch (spellSchool)
            {
                case SpellSchool::NATURE:
                    value += minion->GetSpellPowerNature();
                    break;
                case SpellSchool::NONE:
                case SpellSchool::ARCANE:
                case SpellSchool::FIRE:
                case SpellSchool::FROST:
                case SpellSchool::HOLY:
                case SpellSchool::SHADOW:
                case SpellSchool::FEL:
                case SpellSchool::PHYSICAL_COMBAT:
                    break;
            }
        }
    });

    return value;
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

int Player::GetTimeOut() const
{
    return GetGameTag(GameTag::TIMEOUT) +
           playerAuraEffects.GetValue(GameTag::TIMEOUT);
}

void Player::SetTimeOut(int value)
{
    SetGameTag(GameTag::TIMEOUT, value);
}

bool Player::IsHealingDoesDamage() const
{
    return playerAuraEffects.GetValue(GameTag::HEALING_DOES_DAMAGE) > 0;
}

bool Player::CantBeFrozen() const
{
    return playerAuraEffects.GetValue(GameTag::CANT_BE_FROZEN) > 0;
}

bool Player::ExtraBattlecry() const
{
    return playerAuraEffects.GetValue(GameTag::EXTRA_BATTLECRIES_BASE) > 0;
}

bool Player::ExtraMinionDeathrattle() const
{
    return playerAuraEffects.GetValue(GameTag::EXTRA_MINION_DEATHRATTLES_BASE) >
           0;
}

bool Player::ExtraCastSpell() const
{
    return playerAuraEffects.GetValue(GameTag::EXTRA_CAST_SPELL) > 0;
}

bool Player::ExtraTriggerSecret() const
{
    return playerAuraEffects.GetValue(GameTag::EXTRA_TRIGGER_SECRET) > 0;
}

bool Player::ChooseBoth() const
{
    return playerAuraEffects.GetValue(GameTag::CHOOSE_BOTH) > 0;
}

int Player::GetTotalMana() const
{
    return GetGameTag(GameTag::RESOURCES);
}

void Player::SetTotalMana(int amount)
{
    SetGameTag(GameTag::RESOURCES, amount);

    // Process mana crystal trigger
    game->taskQueue.StartEvent();
    game->triggerManager.OnManaCrystalTrigger(this);
    game->ProcessTasks();
    game->taskQueue.EndEvent();
    game->ProcessDestroyAndUpdateAura();
}

int Player::GetUsedMana() const
{
    return GetGameTag(GameTag::RESOURCES_USED) +
           playerAuraEffects.GetValue(GameTag::RESOURCES_USED);
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

int Player::GetNumCardsDrawnThisTurn() const
{
    return GetGameTag(GameTag::NUM_CARDS_DRAWN_THIS_TURN);
}

void Player::SetNumCardsDrawnThisTurn(int value)
{
    SetGameTag(GameTag::NUM_CARDS_DRAWN_THIS_TURN, value);
}

int Player::GetNumCardsPlayedThisTurn() const
{
    return GetGameTag(GameTag::NUM_CARDS_PLAYED_THIS_TURN);
}

void Player::SetNumCardsPlayedThisTurn(int value)
{
    SetGameTag(GameTag::NUM_CARDS_PLAYED_THIS_TURN, value);
}

int Player::GetNumMinionsPlayedThisTurn() const
{
    return GetGameTag(GameTag::NUM_MINIONS_PLAYED_THIS_TURN);
}

void Player::SetNumMinionsPlayedThisTurn(int value)
{
    SetGameTag(GameTag::NUM_MINIONS_PLAYED_THIS_TURN, value);
}

int Player::GetNumTauntMinionsPlayedThisTurn() const
{
    return GetGameTag(GameTag::NUM_TAUNT_MINIONS_PLAYED_THIS_TURN);
}

void Player::SetNumTauntMinionsPlayedThisTurn(int value)
{
    SetGameTag(GameTag::NUM_TAUNT_MINIONS_PLAYED_THIS_TURN, value);
}

int Player::GetNumFriendlyMinionsDiedThisTurn() const
{
    return GetGameTag(GameTag::NUM_FRIENDLY_MINIONS_THAT_DIED_THIS_TURN);
}

void Player::SetNumFriendlyMinionsDiedThisTurn(int value)
{
    SetGameTag(GameTag::NUM_FRIENDLY_MINIONS_THAT_DIED_THIS_TURN, value);
}

int Player::GetNumElementalPlayedThisTurn() const
{
    return GetGameTag(GameTag::NUM_ELEMENTAL_PLAYED_THIS_TURN);
}

void Player::SetNumElementalPlayedThisTurn(int value)
{
    SetGameTag(GameTag::NUM_ELEMENTAL_PLAYED_THIS_TURN, value);
}

int Player::GetNumElementalPlayedLastTurn() const
{
    return GetGameTag(GameTag::NUM_ELEMENTAL_PLAYED_LAST_TURN);
}

void Player::SetNumElementalPlayedLastTurn(int value)
{
    SetGameTag(GameTag::NUM_ELEMENTAL_PLAYED_LAST_TURN, value);
}

int Player::GetNumWatchPostSummonedThisGame() const
{
    return GetGameTag(GameTag::NUM_WATCH_POSTS_SUMMONED_THIS_GAME);
}

void Player::SetNumWatchPostSummonedThisGame(int value)
{
    SetGameTag(GameTag::NUM_WATCH_POSTS_SUMMONED_THIS_GAME, value);
}

int Player::GetNumSpellsCastThisTurn() const
{
    return GetGameTag(GameTag::NUM_SPELLS_CAST_THIS_TURN);
}

void Player::SetNumSpellsCastThisTurn(int value)
{
    SetGameTag(GameTag::NUM_SPELLS_CAST_THIS_TURN, value);
}

int Player::GetNumSpellsCastLastTurn() const
{
    return GetGameTag(GameTag::NUM_SPELLS_CAST_LAST_TURN);
}

void Player::SetNumSpellsCastLastTurn(int value)
{
    SetGameTag(GameTag::NUM_SPELLS_CAST_LAST_TURN, value);
}

int Player::GetNumSpellsPlayedThisGame() const
{
    return GetGameTag(GameTag::NUM_SPELLS_PLAYED_THIS_GAME);
}

void Player::IncreaseNumSpellsPlayedThisGame()
{
    const int val = GetNumSpellsPlayedThisGame();
    SetGameTag(GameTag::NUM_SPELLS_PLAYED_THIS_GAME, val + 1);
}

int Player::GetAmountHealedThisTurn() const
{
    return GetGameTag(GameTag::AMOUNT_HEALED_THIS_TURN);
}

void Player::SetAmountHealedThisTurn(int value)
{
    SetGameTag(GameTag::AMOUNT_HEALED_THIS_TURN, value);
}

int Player::GetAmountHealedThisGame() const
{
    return GetGameTag(GameTag::AMOUNT_HEALED_THIS_GAME);
}

void Player::SetAmountHealedThisGame(int value)
{
    SetGameTag(GameTag::AMOUNT_HEALED_THIS_GAME, value);
}

int Player::GetNumCardsPlayedThisGameNotStartInDeck() const
{
    return GetGameTag(GameTag::NUM_CARDS_PLAYED_THIS_GAME_NOT_START_IN_DECK);
}

void Player::IncreaseNumCardsPlayedThisGameNotStartInDeck()
{
    const int val = GetNumCardsPlayedThisGameNotStartInDeck();
    SetGameTag(GameTag::NUM_CARDS_PLAYED_THIS_GAME_NOT_START_IN_DECK, val + 1);
}

void Player::UpgradeGalakrond() const
{
    // If the player has already turned into Galakrond, return false.
    if (galakrond->GetZoneType() == ZoneType::PLAY)
    {
        return;
    }

    const auto cardID = galakrond->card->id;

    // If Galakrond have already upgraded to the final stage, return false.
    if (EndsWith(cardID, "t3"))
    {
        return;
    }

    // NOTE: The length of level 1 card IDs is 7.
    // For example, "DRG_600".
    if (cardID.size() == 7)
    {
        galakrond->card = Cards::FindCardByID(cardID + "t2");
    }
    else if (EndsWith(cardID, "t2"))
    {
        galakrond->card = Cards::FindCardByID(cardID.substr(0, 7) + "t3");
    }
}

int Player::GetInvoke() const
{
    return GetGameTag(GameTag::INVOKE_COUNTER);
}

void Player::IncreaseInvoke()
{
    const int val = GetGameTag(GameTag::INVOKE_COUNTER);
    SetGameTag(GameTag::INVOKE_COUNTER, val + 1);
}

void Player::AddHeroAndPower(Card* heroCard, Card* powerCard)
{
    Weapon* weapon = nullptr;
    AuraEffects* auraEffects = nullptr;

    if (m_hero)
    {
        m_setasideZone->MoveTo(m_hero, m_setasideZone->GetCount());
        m_setasideZone->MoveTo(m_hero->heroPower, m_setasideZone->GetCount());

        if (m_hero->weapon)
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
}  // namespace RosettaStone::PlayMode
