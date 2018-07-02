/*************************************************************************
> File Name: AgentStructure.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Agent Data Structure for Interact with Interface
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Commons/Constants.h>
#include <Syncs/AgentStructures.h>

namespace Hearthstonepp
{
template <typename T>
std::unique_ptr<Card> CopyCard(const Card *card)
{
    auto ptr = dynamic_cast<const T *>(card);
    if (ptr != nullptr)
    {
        return std::make_unique<T>(*ptr);
    }
    else
    {
        return std::make_unique<Card>(*card);
    }
}

Player::Player(const Account *account, const Deck *deck)
    : totalMana(0),
      existMana(0),
      exhausted(0),
      email(account->GetEmail()),
      weapon(nullptr)
{
    cardsInDeck.reserve(MAXIMUM_NUM_CARDS_IN_DECK * 2);
    for (auto ptrCard : deck->GetPrimitiveDeck())
    {
        std::unique_ptr<Card> card;
        switch (ptrCard->cardType)
        {
            case +CardType::ENCHANTMENT:
                card = CopyCard<Enchantment>(ptrCard);
                break;
            case +CardType::HERO:
                card = CopyCard<Hero>(ptrCard);
                break;
            case +CardType::HERO_POWER:
                card = CopyCard<HeroPower>(ptrCard);
                break;
            case +CardType::MINION:
                card = CopyCard<Minion>(ptrCard);
                break;
            case +CardType::SPELL:
                card = CopyCard<Spell>(ptrCard);
                break;
            case +CardType::WEAPON:
                card = CopyCard<Weapon>(ptrCard);
                break;
            default:
                card = std::make_unique<Card>(*ptrCard);
        }

        // Deep copy of card data
        cardsInDeck.emplace_back(std::move(card));
    }

    for (auto &card : cardsInDeck)
    {
        cardsPtrInDeck.emplace_back(card.get());
    }

    Cards *cards = Cards::GetInstance();
    const CardClass cardClass = deck->GetClass();

    auto heroCard = dynamic_cast<const Hero *>(cards->GetHeroCard(cardClass));
    if (heroCard != nullptr)
    {
        cardsInDeck.emplace_back(std::make_unique<Hero>(*heroCard));
        Card *back = cardsInDeck.back().get();
        hero = dynamic_cast<Hero *>(back);
    }

    auto powerCard =
        dynamic_cast<const HeroPower *>(cards->GetDefaultHeroPower(cardClass));
    if (powerCard != nullptr)
    {
        cardsInDeck.emplace_back(std::make_unique<HeroPower>(*powerCard));
        Card *back = cardsInDeck.back().get();
        power = dynamic_cast<HeroPower *>(back);
    }
}
}  // namespace Hearthstonepp