/*************************************************************************
> File Name: Console.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Console version of Hearthstone++ game.
> Created Time: 2017/10/08
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Agents/GameAgent.h>
#include <Commons/Constants.h>
#include <Loaders/CardLoader.h>
#include <Models/Card.h>
#include <Models/Cards.h>
#include <Programs/Console.h>

#include <iostream>

namespace Hearthstonepp
{
	template<std::size_t SIZE>
	void Console::ShowMenu(std::array<std::string, SIZE>& menus)
	{
		std::cout << "========================================\n";
		for (auto& menu : menus)
		{
			std::cout << menu.c_str() << '\n';
		}
		std::cout << "========================================\n";
	}

	size_t Console::InputMenuNum(std::string questionStr, const int menuSize)
	{
		while (true)
		{
			std::cout << questionStr;
			size_t num;
			std::cin >> num;

			if (num < 1 || num > menuSize)
			{
				std::cout << "Invalid number! Try again.\n";
			}
			else
			{
				return num;
			}
		}
	}

	bool Console::InputYesNo(std::string sentence) const
	{
		std::cout << sentence;
		std::cout << "(Please input \"y/yes\" or \"n/no\" (insensitive))\n";
		std::cout << "Input: ";

		std::string str;
		std::cin >> str;
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);

		return (str == "y" || str == "yes") ? true : (str == "n" || str == "no") ? false : InputYesNo(sentence);
	}

	void Console::SearchCard()
	{

	}

	void Console::MakeDeck()
	{
		std::cout << "========================================\n";
		std::cout << "               Make Deck!               \n";
		std::cout << "========================================\n";

		ShowMenu(m_playerClassStr);
		const size_t selectedClassNum = InputMenuNum("What's your player class? ", PLAYER_CLASS_SIZE);
		const PlayerClass playerClass = static_cast<PlayerClass>(selectedClassNum);

		std::cout << "What's your deck name? ";
		std::string name;
		std::cin >> name;

		Deck deck(playerClass, name);

		std::cout << "Input Card ID to add or delete to your deck.\n";
		std::cout << "If you do not want to add or delete more, please input \"STOP\"\n";

		while (true)
		{
			std::cout << "The number of cards in the current deck = " << deck.GetNumOfCards() << " / " << MAXIMUM_NUM_CARDS_IN_DECK << "\n";
			std::cout << "Card ID: ";
			std::string selectedCardID;
			std::cin >> selectedCardID;

			if (selectedCardID == "STOP")
			{
				break;
			}

			const Card* card = Cards::GetInstance()->FindCardByID(selectedCardID);
			if (card == nullptr)
			{
				std::cout << selectedCardID << " doesn't exist. Try again.\n";
				continue;
			}

			card->ShowInfo();

			const bool isYes = InputYesNo("Is it correct? ");
			if (isYes == false)
			{
				continue;
			}

			ShowMenu(m_makeDeckOperationStr);
			const size_t selectedOperation = InputMenuNum("What do you want to do? ", 2);
			m_makeDeckOperationFuncs[selectedOperation - 1](*this, deck, card, selectedCardID);
		} 
	}

	void Console::AddCardInDeck(Deck& deck, const Card* card, std::string& selectedCardID)
	{
		while (true)
		{
			std::cout << "How many cards to add (0 - " << card->GetMaxAllowedInDeck() - deck.GetNumCardInDeck(selectedCardID) << ") ? ";
			unsigned int numCardToAdd;
			std::cin >> numCardToAdd;

			if (numCardToAdd < 0 || numCardToAdd > card->GetMaxAllowedInDeck() - deck.GetNumCardInDeck(selectedCardID))
			{
				std::cout << "Invalid number! Try again.\n";
			}
			else
			{
				deck.AddCard(card, numCardToAdd);
				break;
			}
		}
	}

	void Console::DeleteCardInDeck(Deck& deck, const Card* card, std::string& selectedCardID)
	{
		if (deck.GetNumCardInDeck(selectedCardID) == 0)
		{
			std::cout << selectedCardID << " doesn't exist.\n";
			return;
		}

		while (true)
		{
			std::cout << "How many cards to delete (0 - " << deck.GetNumCardInDeck(selectedCardID) << ") ? ";
			unsigned int numCardToDelete;
			std::cin >> numCardToDelete;

			if (numCardToDelete < 0 || numCardToDelete > deck.GetNumCardInDeck(selectedCardID))
			{
				std::cout << "Invalid number! Try again.\n";
			}
			else
			{
				deck.DeleteCard(card, numCardToDelete);
				break;
			}
		}
	}

	void Console::LoadDeck()
	{

	}

	void Console::StoreDeck()
	{
		
	}

	void Console::SimulateGame()
	{
		//CardLoader loader;
		//std::vector<Card*> cards;

		//loader.Load(cards);

		//Deck deck1; // temporal deck
		//Deck deck2;

		//deck1.reserve(30);
		//deck2.reserve(30);

		//deck1.assign(cards.begin(), cards.begin() + 30); 
		//deck2.assign(cards.begin() + 30, cards.begin() + 60);

		//User user1(0, new Hero(), new HeroPower(), deck1); // define new user
		//User user2(1, new Hero(), new HeroPower(), deck2);

		//GameAgent agent(&user1, &user2);
		//GameResult result;

		//std::thread *at = agent.StartAgent(result);

		//for (int i = 0; i < 2; ++i)
		//{
		//	Card *list[3] = { 0, };
		//	int result = agent.ReadBuffer((BYTE*)list, sizeof(Card*) * 3); // get card data

		//	for (auto card : list)
		//	{
		//		std::cout << "[" << card->name << "] ";
		//	}
		//	std::cout << std::endl;

		//	BYTE mulligan[] = { 0, 2 }; // index of the card to be mulligan
		//	result = agent.WriteBuffer(mulligan, 2); // send index to agent

		//	result = agent.ReadBuffer((BYTE*)list, sizeof(Card*) * 3); // get new card data

		//	for (auto card : list)
		//	{
		//		std::cout << "[" << card->name << "] ";
		//	}
		//	std::cout << std::endl;
		//}

		//at->join(); // join agent thread
	}

	int Console::Play()
	{
		std::cout << "    Welcome to Hearthstone++ Ver " << VERSION << '\n';

		ShowMenu(m_menuStr);
		const size_t selectedNum = InputMenuNum("Select: ", MENU_SIZE);
		bool isFinish = false;

		if (selectedNum != MENU_SIZE)
		{
			m_menuFuncs[selectedNum - 1](*this);
		}
		else
		{
			isFinish = true;
		}

		return isFinish ? 0 : Play();
	}
}
