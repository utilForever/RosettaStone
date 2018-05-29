/*************************************************************************
> File Name: AgentStructure.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Agent Data Structure for Interact with Interface
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/AgentStructures.h>
#include <Commons/Constants.h>

namespace Hearthstonepp
{
	User::User(Player* player, int deckID) :
		totalMana(0), existMana(0), exhausted(0), userID(player->GetID()) , weapon(nullptr)
	{
		Cards* cards = Cards::GetInstance();

		Deck* tmpDeck = player->GetDeck(deckID);
		const CardClass cardclass = tmpDeck->GetClass();

		const Card* heroCard = cards->GetHeroCard(cardclass);
		const Card* powerCard = cards->GetDefaultHeroPower(cardclass);

		cardDeck.reserve(sizeof(Card) * (MAXIMUM_NUM_CARDS_IN_DECK + 2));
		// Primitive deck has card pointer in library, should copy to use.
		for (auto& ptrCard : tmpDeck->GetPrimitiveDeck())
		{
			// Copy card data to cardDeck vector
			cardDeck.emplace_back(Card(*ptrCard));
			// push card pointer to deck vector
			deck.emplace_back(&cardDeck.back());
		}

		cardDeck.emplace_back(Hero(*reinterpret_cast<const Hero*>(heroCard)));
		hero = reinterpret_cast<Hero*>(&cardDeck.back());

		cardDeck.emplace_back(HeroPower(*reinterpret_cast<const HeroPower*>(powerCard)));
		power = reinterpret_cast<HeroPower*>(&cardDeck.back());
	}
}