// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Player.hpp>
#include <Rosetta/Models/Spell.hpp>

namespace RosettaStone
{
Entity::Entity(Player& _owner, Card& _card) : owner(&_owner), card(_card)
{
    auraEffects = new AuraEffects(this);

    for (auto& gameTag : _card.gameTags)
    {
        Entity::SetGameTag(gameTag.first, gameTag.second);
    }
}

Entity::Entity(const Entity& ent)
{
    FreeMemory();

    owner = ent.owner;
    card = ent.card;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;
}

Entity::Entity(Entity&& ent) noexcept
{
    FreeMemory();

    owner = ent.owner;
    card = ent.card;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;
}

Entity::~Entity()
{
    FreeMemory();
}

Entity& Entity::operator=(const Entity& ent)
{
    if (this == &ent)
    {
        return *this;
    }

    FreeMemory();

    owner = ent.owner;
    card = ent.card;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;

    return *this;
}

Entity& Entity::operator=(Entity&& ent) noexcept
{
    if (this == &ent)
    {
        return *this;
    }

    FreeMemory();

    owner = ent.owner;
    card = ent.card;

    auraEffects = ent.auraEffects;
    onGoingEffect = ent.onGoingEffect;
    m_gameTags = ent.m_gameTags;

    return *this;
}

void Entity::Reset()
{
    SetGameTag(GameTag::DAMAGE, 0);
    SetGameTag(GameTag::EXHAUSTED, 0);
    SetGameTag(GameTag::ATK, 0);
    SetGameTag(GameTag::HEALTH, 0);
    SetGameTag(GameTag::COST, 0);
    SetGameTag(GameTag::TAUNT, 0);
    SetGameTag(GameTag::FROZEN, 0);
    SetGameTag(GameTag::CHARGE, 0);
    SetGameTag(GameTag::WINDFURY, 0);
    SetGameTag(GameTag::DIVINE_SHIELD, 0);
    SetGameTag(GameTag::STEALTH, 0);
    SetGameTag(GameTag::NUM_ATTACKS_THIS_TURN, 0);
}

int Entity::GetGameTag(GameTag tag) const
{
    int value = 0;

    if (m_gameTags.find(tag) == m_gameTags.end())
    {
        if (auraEffects != nullptr)
        {
            value += auraEffects->GetGameTag(tag);
        }
    }
    else
    {
        value += m_gameTags.at(tag);

        if (auraEffects != nullptr)
        {
            value += auraEffects->GetGameTag(tag);
        }
    }

    return value > 0 ? value : 0;
}

void Entity::SetGameTag(GameTag tag, int value)
{
    m_gameTags.insert_or_assign(tag, value);
}

int Entity::GetCost() const
{
    return GetGameTag(GameTag::COST);
}

void Entity::SetCost(int cost)
{
    SetGameTag(GameTag::COST, cost);
}

bool Entity::GetExhausted() const
{
    return static_cast<bool>(GetGameTag(GameTag::EXHAUSTED));
}

void Entity::SetExhausted(bool exhausted)
{
    SetGameTag(GameTag::EXHAUSTED, static_cast<int>(exhausted));
}

bool Entity::HasCombo() const
{
    return GetGameTag(GameTag::COMBO) == 1;
}

void Entity::Destroy()
{
    isDestroyed = true;
}

Entity* Entity::GetFromCard(Player& player, Card&& card)
{
    Entity* result;

    switch (card.GetCardType())
    {
        case CardType::HERO:
            result = new Hero(player, card);
            break;
        case CardType::HERO_POWER:
            result = new HeroPower(player, card);
            break;
        case CardType::MINION:
            result = new Minion(player, card);
            break;
        case CardType::SPELL:
            result = new Spell(player, card);
            break;
        case CardType::WEAPON:
            result = new Weapon(player, card);
            break;
        default:
            throw std::invalid_argument(
                "Generic::DrawCard() - Invalid card type!");
    }

    // Set entity ID
    result->id = player.GetGame()->GetNextID();

    return result;
}

void Entity::FreeMemory()
{
    delete auraEffects;
    delete onGoingEffect;

    m_gameTags.clear();
}
}  // namespace RosettaStone
