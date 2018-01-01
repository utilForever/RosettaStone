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
#include <Enums/EnumsToString.h>

namespace Hearthstonepp
{
	User::User(Player* player, int deckID) :
		totalMana(0), existMana(0), exhausted(0), userID(player->GetID()) , weapon(nullptr)
	{
		Cards* cards = Cards::GetInstance();

		Deck* tmpDeck = player->GetDeck(deckID);
		const CardClass cardclass = tmpDeck->GetClass();

		const Card* heroCard = cards->FindCardByID(std::move(ConvertFromCardClassToHeroID.at(cardclass)));
		const Card* powerCard = cards->FindCardByID(std::move(ConvertFromCardClassToHeroPowerID.at(cardclass)));

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

	GameBrief::GameBrief(
		BYTE currentUser, BYTE oppositeUser, BYTE currentMana, BYTE oppositeMana,
		BYTE numCurrentHand, BYTE numOppositeHand, BYTE numCurrentField, BYTE numOppositeField,
		Card* currentHero, Card* oppositeHero,
		Card** currentField, Card** currentHand, Card** oppositeField) :
		currentUser(currentUser), oppositeUser(oppositeUser), 
		currentMana(currentMana), oppositeMana(oppositeMana), 
		numCurrentHand(numCurrentHand), numOppositeHand(numOppositeHand),
		numCurrentField(numCurrentField), numOppositeField(numOppositeField),
		currentHero(currentHero), oppositeHero(oppositeHero),
		currentField(currentField), currentHand(currentHand), oppositeField(oppositeField)
	{
		// Do Nothing
	}

	TargetingStructure::TargetingStructure(BYTE src, BYTE dst)
		: src(src), dst(dst)
	{
		// Do Nothing
	}

	DrawStructure::DrawStructure(BYTE drawID, BYTE userID, BYTE numDraw, Card** cards) :
		id(drawID), userID(userID), numDraw(numDraw), cards(cards)
	{
		// Do Nothing
	}

	OverDrawStructure::OverDrawStructure(BYTE userID, BYTE numOver, Card** cards) :
		userID(userID), numOver(numOver), cards(cards)
	{
		// Do Nothing
	}

	ExhaustDeckStructure::ExhaustDeckStructure(BYTE userID, BYTE numOver) :
		userID(userID), numOver(numOver)
	{
		// Do Nothing
	}

	ModifyManaStructure::ModifyManaStructure(BYTE userID, BYTE mana) :
		userID(userID), mana(mana)
	{
		// Do Nothing
	}

	ModifyHealthStructure::ModifyHealthStructure(BYTE userID, Card* card) :
		userID(userID), card(card)
	{
		// Do Nothing
	}

	ExhaustMinionStructure::ExhaustMinionStructure(BYTE userID, Card* card) :
		userID(userID), card(card)
	{
		// Do Nothing
	}

	BeginFirstStructure::BeginFirstStructure(std::string& firstUserID, std::string& lastUserID) :
		firstUserID(firstUserID), lastUserID(lastUserID)
	{
		// Do Nothing
	}

	BeginShuffleStructure::BeginShuffleStructure(BYTE userID) : userID(userID)
	{
		// Do Nothing
	}

	BeginMulliganStructure::BeginMulliganStructure(BYTE userID) : userID(userID)
	{
		// Do Nothing
	}

	MainReadyStructure::MainReadyStructure(BYTE userID) : userID(userID)
	{
		// Do Nothing
	}

	MainMenuStructure::MainMenuStructure(BYTE userID) : userID(userID)
	{
		// Do Nothing
	}

	MainUseCardStructure::MainUseCardStructure(
		BYTE userID, BYTE existMana, BYTE numFields, BYTE numHands, Card** hands) : 
		userID(userID), existMana(existMana), numFields(numFields), numHands(numHands), hands(hands)
	{
		// Do Nothing
	}

	MainUseMinionStructure::MainUseMinionStructure(BYTE cardIndex, BYTE position) :
		cardIndex(cardIndex), position(position)
	{
		// Do Nothing
	}

	MainCombatStructure::MainCombatStructure(
		BYTE userID, BYTE numCurrentField, BYTE numOppositeField, BYTE numAttacked,
		Card** currentField, Card** oppositeField, Card** attacked) : 
		userID(userID), numCurrentField(numCurrentField), numOppositeField(numOppositeField), numAttacked(numAttacked),
		currentField(currentField), oppositeField(oppositeField), attacked(attacked)
	{
		// Do Nothing
	}

	MainEndStructure::MainEndStructure(BYTE userID) : userID(userID)
	{
		// Do Nothing
	}

	FinalGameOverStructure::FinalGameOverStructure(BYTE winnerUserID) : winnerUserID(winnerUserID)
	{
		// Do Nothing
	}
}