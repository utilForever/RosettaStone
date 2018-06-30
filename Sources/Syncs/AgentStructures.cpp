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
Player::Player(const Account* account, const Deck* deck)
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

    cardsInDeck.reserve(sizeof(Card) * MAXIMUM_NUM_CARDS_IN_DECK * 2);
	for (auto ptrCard : deck->GetPrimitiveDeck())
    {
        // Deep copy of card data
        cardsInDeck.emplace_back(*ptrCard);
    }

	for (auto& card : cardsInDeck)
	{
        cardsPtrInDeck.emplace_back(&card);
	}

	if (heroCard != nullptr)
	{
        cardsInDeck.emplace_back(*heroCard);
        Card* back = &cardsInDeck.back();
        hero = dynamic_cast<Hero*>(back);
	}

	if (powerCard != nullptr)
	{
        cardsInDeck.emplace_back(*powerCard);
        Card* back = &cardsInDeck.back();
        power = dynamic_cast<HeroPower*>(back);
	}
}
}  // namespace Hearthstonepp