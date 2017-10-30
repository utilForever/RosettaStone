/*************************************************************************
> File Name: AgentStructure.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Agent Data Structure for Interact with Interface
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/AgentStructures.h>
#include <Enums/EnumsToString.h>

namespace Hearthstonepp
{
	User::User(Player* player, int deckID) :
		player(player) , weapon(nullptr)
	{
		Cards* cards = Cards::GetInstance();

		Deck* tmpDeck = player->GetDeck(deckID);
		const CardClass cardclass = tmpDeck->GetClass();

		const Card* heroCard = cards->FindCardByID(std::move(ConvertFromCardClassToHeroID.at(cardclass)));
		const Card* powerCard = cards->FindCardByID(std::move(ConvertFromCardClassToHeroPowerID.at(cardclass)));

		deck = tmpDeck->GetPrimitiveDeck();
		hero = static_cast<Hero*>(const_cast<Card*>(heroCard));
		power = static_cast<HeroPower*>(const_cast<Card*>(powerCard));
	}

	DrawStructure::DrawStructure(BYTE drawID, BYTE userID, BYTE numDraw, BYTE numHands, Card** cards) :
		id(drawID), userID(userID), numDraw(numDraw), numHands(numHands), cards(cards)
	{
		// Do Nothing
	}

	BeginFirstStructure::BeginFirstStructure(std::string&& userFirst, std::string&& userLast) :
		userFirst(std::move(userFirst)), userLast(std::move(userLast))
	{
		// Do Nothing
	}

	BeginShuffleStructure::BeginShuffleStructure(int userID) : userID(userID)
	{
		// Do Nothing
	}

	BeginMulliganStructure::BeginMulliganStructure(int userID) : userID(userID)
	{
		// Do Nothing
	}
}