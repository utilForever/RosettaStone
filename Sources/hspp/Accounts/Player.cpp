// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Accounts/Player.h>
#include <hspp/Cards/Cards.h>
#include <hspp/Tasks/TaskMeta.h>

namespace Hearthstonepp
{
Player::Player(const Account* account, const Deck* deck)
    : id(USER_INVALID), email(account->GetEmail()), m_opponent(*this)
{
    const CardClass cardClass = deck->GetClass();

    Card heroCard = Cards::GetInstance().GetHeroCard(cardClass);
    if (!heroCard.id.empty())
    {
        hero = new Hero(heroCard);
    }

    Card powerCard = Cards::GetInstance().GetDefaultHeroPower(cardClass);
    if (!powerCard.id.empty())
    {
        power = new HeroPower(powerCard);
    }

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

Player::~Player()
{
    FreeMemory();
}

Player::Player(const Player& p) : m_opponent(p.m_opponent)
{
    FreeMemory();

    CopyData(p);
}

Player::Player(Player&& p) noexcept : m_opponent(p.m_opponent)
{
    FreeMemory();

    MoveData(std::move(p));
}

Player& Player::operator=(const Player& p)
{
    if (this == &p)
    {
        return *this;
    }

    FreeMemory();

    CopyData(p);

    return *this;
}

Player& Player::operator=(Player&& p) noexcept
{
    if (this == &p)
    {
        return *this;
    }

    FreeMemory();

    MoveData(std::move(p));

    return *this;
}

bool Player::operator==(const Player& player) const
{
    return email == player.email;
}

Player& Player::GetOpponent() const
{
    return m_opponent;
}

void Player::SetOpponent(Player& player) const
{
    m_opponent = player;
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
    delete power;
}

void Player::CopyData(const Player& p)
{
    email = p.email;

    id = p.id;
    totalMana = p.totalMana;
    existMana = p.existMana;
    exhausted = p.exhausted;

    if (p.hero != nullptr)
    {
        hero = p.hero->Clone();
    }
    if (p.power != nullptr)
    {
        power = p.power->Clone();
    }

    field.resize(p.field.size());
    std::transform(p.field.begin(), p.field.end(), field.begin(),
                   [](Character* c) -> Character* { return c->Clone(); });

    hand.resize(p.hand.size());
    std::transform(p.hand.begin(), p.hand.end(), hand.begin(),
                   [](Entity* e) -> Entity* { return e->Clone(); });

    usedSpell.resize(p.usedSpell.size());
    std::transform(p.usedSpell.begin(), p.usedSpell.end(), usedSpell.begin(),
                   [](Spell* s) -> Spell* { return s->Clone(); });

    usedMinion.resize(p.usedMinion.size());
    std::transform(p.usedMinion.begin(), p.usedMinion.end(), usedMinion.begin(),
                   [](Character* c) -> Character* { return c->Clone(); });
}

void Player::MoveData(Player&& p)
{
    email = std::move(p.email);

    id = p.id;
    totalMana = p.totalMana;
    existMana = p.existMana;
    exhausted = p.exhausted;

    hero = p.hero;
    p.hero = nullptr;
    power = p.power;
    p.power = nullptr;

    field = std::move(p.field);
    hand = std::move(p.hand);
    usedSpell = std::move(p.usedSpell);
    usedMinion = std::move(p.usedMinion);
}
}  // namespace Hearthstonepp
