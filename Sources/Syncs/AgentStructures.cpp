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
Player::Player(Account* account, Deck* deck)
    : totalMana(0),
      existMana(0),
      exhausted(0),
      email(account->GetEmail()),
      weapon(nullptr)
{
    Cards* cards = Cards::GetInstance();

    const CardClass cardclass = deck->GetClass();

    const Card* heroCard = cards->GetHeroCard(cardclass);
    const Card* powerCard = cards->GetDefaultHeroPower(cardclass);

    cardsInDeck.reserve(sizeof(Card) * (MAXIMUM_NUM_CARDS_IN_DECK + 2));
    for (auto& ptrCard : deck->GetPrimitiveDeck())
    {
        // Deep copy of card data
        cardsInDeck.emplace_back(Card(*ptrCard));
        cardsPtrInDeck.emplace_back(&cardsInDeck.back());
    }

    cardsInDeck.emplace_back(Hero(*reinterpret_cast<const Hero*>(heroCard)));
    hero = reinterpret_cast<Hero*>(&cardsInDeck.back());

    cardsInDeck.emplace_back(
        HeroPower(*reinterpret_cast<const HeroPower*>(powerCard)));
    power = reinterpret_cast<HeroPower*>(&cardsInDeck.back());

    field.reserve(FIELD_SIZE);
    field.assign({nullptr});
}
}  // namespace Hearthstonepp