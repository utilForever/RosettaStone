/*************************************************************************
> File Name: Cards.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Cards class that stores a list of cards.
> Created Time: 2017/10/10
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_CARDS_H
#define HEARTHSTONEPP_CARDS_H

#include <Models/Card.h>

#include <vector>

namespace Hearthstonepp
{
	class Cards
	{
	public:
		static Cards* GetInstance();

		const Card* FindCardByID(const std::string id);
		std::vector<Card*> FindCardByRarity(Rarity rarity);
		std::vector<Card*> FindCardByClass(CardClass cardClass);
		std::vector<Card*> FindCardByType(CardType cardType);
		std::vector<Card*> FindCardByName(const std::string name);
		std::vector<Card*> FindCardByCost(int minVal, int maxVal);
		std::vector<Card*> FindCardByAttack(int minVal, int maxVal);
		std::vector<Card*> FindCardByHealth(int minVal, int maxVal);

	private:
		Cards();
		~Cards();
		Cards(const Cards&) = delete;
		Cards(Cards&&) = delete;
		Cards& operator=(const Cards&) = delete;
		Cards& operator=(Cards&&) = delete;

		static Cards* m_instance;

		std::vector<Card*> m_cards;
	};
}

#endif