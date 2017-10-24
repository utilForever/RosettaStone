/*************************************************************************
> File Name: AgentStructure.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Agent Data Structure for Interact with Interface
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/AgentStructures.h>

namespace Hearthstonepp
{
	User::User(Player* player, int deckID)
		: m_player(player)
		, m_weapon(nullptr)
	{
		Cards* cards = Cards::GetInstance();

		Deck* tmpDeck = player->GetDeck(deckID);
		CardClass cardclass = tmpDeck->GetClass();

		const Card* hero = cards->FindCardByID(std::move(ConvertFromCardClassToHeroID.at(cardclass)));
		const Card* power = cards->FindCardByID(std::move(ConvertFromCardClassToHeroPowerID.at(cardclass)));

		m_deck = tmpDeck->GetPrimitiveDeck();
		m_hero = static_cast<Hero*>(const_cast<Card*>(hero));
		m_power = static_cast<HeroPower*>(const_cast<Card*>(power));
	}

	DrawStructure::DrawStructure(BYTE drawID, BYTE userID, BYTE numDraw, BYTE numHands, Card** cards)
		: id(drawID)
		, userID(userID)
		, numDraw(numDraw)
		, numHands(numHands)
		, cards(cards)
	{
		// Do Nothing
	}

	BeginFirstStructure::BeginFirstStructure(std::string userFirst, std::string userLast)
		: userFirst(userFirst)
		, userLast(userLast)
	{
		// Do Nothing
	}

	BeginShuffleStructure::BeginShuffleStructure(int userID)
		: userID(userID)
	{
		// Do Nothing
	}

	BeginMulliganStructure::BeginMulliganStructure(int userID)
		: userID(userID)
	{
		// Do Nothing
	}
}