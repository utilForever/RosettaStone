/*************************************************************************
> File Name: AgentStructure.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Agent Data Structure for Interact with Interface
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Cards/Hero.h>
#include <Commons/Constants.h>
#include <Syncs/AgentStructures.h>

namespace Hearthstonepp
{
Player::Player(Account* account, Deck* deck)
    : totalMana(0),
      existMana(0),
      exhausted(0),
      email(account->GetEmail())
{
    Cards* cardsInstance = Cards::GetInstance();

    const CardClass cardclass = deck->GetClass();

    const Card* heroCard = cardsInstance->GetHeroCard(cardclass);
    const Card* powerCard = cardsInstance->GetDefaultHeroPower(cardclass);

    cards.reserve(sizeof(Card) * (MAXIMUM_NUM_CARDS_IN_DECK + 2));
    for (auto& card : deck->GetPrimitiveDeck())
    {
        cards.emplace_back(new Entity(card));
    }

    hero = new Hero(heroCard);
    power = new HeroPower(powerCard);

    field.reserve(FIELD_SIZE);
    for (size_t i = 0; i < FIELD_SIZE; ++i)
    {
        field.emplace_back(nullptr);
    }
}
}  // namespace Hearthstonepp