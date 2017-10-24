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
#include <Enums/EnumsToString.h>
#include <Interface/Interface.h>
#include <Loaders/CardLoader.h>
#include <Loaders/PlayerLoader.h>
#include <Models/Card.h>
#include <Models/Cards.h>
#include <Programs/Console.h>

#include <filesystem>
#include <fstream>
#include <iostream>

namespace filesystem = std::experimental::filesystem;

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

	size_t Console::InputMenuNum(std::string questionStr, size_t menuSize)
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

	void Console::SignIn()
	{
		std::cout << "Input Player ID to load data.\n";
		std::cout << "If you do not want to load, please input \"STOP\"\n";

		while (true)
		{
			std::cout << "Player ID: ";
			std::string playerID;
			std::cin >> playerID;

			if (playerID == "STOP")
			{
				break;
			}

			if (!filesystem::exists("Datas/" + playerID + ".json"))
			{
				std::cout << playerID << ".json doesn't exist. Try again.\n";
				continue;
			}

			PlayerLoader loader;
			m_player = loader.Load(playerID);

			if (m_player == nullptr)
			{
				std::cout << "An error occurred while loading player data.\n";
				continue;
			}

			std::cout << "You are signed in. Hello, " << playerID << "!\n";

			Main();

			break;
		}
	}

	void Console::SignUp()
	{
		std::cout << "Input Player ID to create data.\n";

		while (true)
		{
			std::cout << "Player ID: ";
			std::string playerID;
			std::cin >> playerID;

			if (filesystem::exists("Datas/" + playerID + ".json"))
			{
				std::cout << playerID << ".json already exists. Try again.\n";
				continue;
			}

			std::cout << "Name: ";
			std::string name;
			std::cin >> name;

			m_player = new Player(std::move(playerID), std::move(name));

			PlayerLoader loader;
			loader.Save(m_player);

			std::cout << "Your account has been created. Please sign in.\n";
			break;
		}
	}

	void Console::SearchCard()
	{

	}

	int Console::ManageDeck()
	{
		std::cout << "========================================\n";
		std::cout << "              Manage Deck!              \n";
		std::cout << "========================================\n";

		ShowMenu(m_manageDeckStr);
		const size_t selectedNum = InputMenuNum("Select: ", MANAGE_DECK_MENU_SIZE);
		bool isFinish = false;

		if (selectedNum != MANAGE_DECK_MENU_SIZE)
		{
			m_manageDeckFuncs[selectedNum - 1](*this);
		}
		else
		{
			isFinish = true;
		}

		return isFinish ? 0 : ManageDeck();
	}

	void Console::SimulateGame()
	{
		int deck1, deck2;
		std::string user1, user2;

		std::cout << "[*] input first id, deck index : ";
		std::cin >> user1 >> deck1;

		std::cout << "[*] input second id, deck index : ";
		std::cin >> user2 >> deck2;

		PlayerLoader loader;
		Player* p1 = loader.Load(user1);
		Player* p2 = loader.Load(user2);

		GameAgent agent(User(p1, deck1), User(p2, deck2));
		GameInterface game(agent);

		GameResult result = game.StartGame();
	}

	void Console::Leave()
	{
		PlayerLoader loader;
		loader.Save(m_player);

		if (m_player != nullptr)
		{
			delete m_player;
			m_player = nullptr;
		}

		std::cout << "You have been successfully signed out. Have a nice day!\n";
	}

	void Console::CreateDeck()
	{
		std::cout << "========================================\n";
		std::cout << "              Create Deck!              \n";
		std::cout << "========================================\n";

		std::cout << "What's your deck name? ";
		std::string name;
		std::cin >> name;

		ShowMenu(m_playerClassStr);
		const size_t selectedClassNum = InputMenuNum("What's your player class? ", PLAYER_CLASS_SIZE);
		const CardClass deckClass = static_cast<CardClass>(selectedClassNum + 1);

		m_player->CreateDeck(name, deckClass);

		OperateDeck(m_player->GetNumOfDeck());
	}

	void Console::ModifyDeck()
	{
		if (m_player->GetNumOfDeck() == 0)
		{
			std::cout << "Deck does not exist. Create a new deck!\n";
			return;
		}

		std::cout << "========================================\n";
		std::cout << "              Modify Deck!              \n";
		std::cout << "========================================\n";

		std::cout << "Input the number to modify your deck.\n";

		m_player->ShowDeckList();
		const size_t selectedDeck = InputMenuNum("Select: ", m_player->GetNumOfDeck());

		OperateDeck(selectedDeck);
	}

	void Console::DeleteDeck()
	{
		if (m_player->GetNumOfDeck() == 0)
		{
			std::cout << "Deck does not exist. Create a new deck!\n";
			return;
		}

		std::cout << "========================================\n";
		std::cout << "              Delete Deck!              \n";
		std::cout << "========================================\n";

		std::cout << "Input the number to delete your deck.\n";

		m_player->ShowDeckList();
		const size_t selectedDeck = InputMenuNum("Select: ", m_player->GetNumOfDeck());

		m_player->DeleteDeck(selectedDeck);
	}

	void Console::OperateDeck(size_t selectedDeck)
	{
		Deck* deck = m_player->GetDeck(selectedDeck - 1);
		const CardClass deckClass = deck->GetClass();

		std::cout << "Input Card ID to add or delete to your deck.\n";
		std::cout << "If you do not want to add or delete more, please input \"STOP\"\n";

		while (true)
		{
			std::cout << "The number of cards in the current deck = " << deck->GetNumOfCards() << " / " << MAXIMUM_NUM_CARDS_IN_DECK << "\n";
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
			if (card->GetCardClass() != CardClass::NEUTRAL && card->GetCardClass() != deckClass)
			{
				std::cout << "The class of " << selectedCardID << " is " << ConverterFromCardClassToString.at(card->GetCardClass()).c_str() << '\n';
				std::cout << "It is neither a NETURAL nor a " << ConverterFromCardClassToString.at(deckClass).c_str() << '\n';
				continue;
			}

			card->ShowInfo();

			const bool isYes = InputYesNo("Is it correct? ");
			if (isYes == false)
			{
				continue;
			}

			ShowMenu(m_deckOperationStr);
			const size_t selectedOperation = InputMenuNum("What do you want to do? ", CREATE_DECK_MENU_SIZE);

			if (selectedOperation != CREATE_DECK_MENU_SIZE)
			{
				m_deckOperationFuncs[selectedOperation - 1](*this, deck, selectedCardID);
			}
			else
			{
				break;
			}
		}
	}

	void Console::AddCardInDeck(Deck* deck, std::string& selectedCardID)
	{
		if (deck->GetNumOfCards() >= MAXIMUM_NUM_CARDS_IN_DECK)
		{
			std::cout << "The deck " << deck->GetName() << " is full of cards.\n";
			return;
		}

		while (true)
		{
			unsigned int numCardToAddAvailable = Cards::GetInstance()->FindCardByID(selectedCardID)->GetMaxAllowedInDeck() - deck->GetNumCardInDeck(selectedCardID);
			if (deck->GetNumOfCards() + numCardToAddAvailable > MAXIMUM_NUM_CARDS_IN_DECK)
			{
				numCardToAddAvailable = deck->GetNumOfCards() + numCardToAddAvailable - MAXIMUM_NUM_CARDS_IN_DECK;
			}

			std::cout << "How many cards to add (0 - " << numCardToAddAvailable << ") ? ";
			unsigned int numCardToAdd;
			std::cin >> numCardToAdd;

			if (numCardToAdd < 0 || numCardToAdd > numCardToAddAvailable)
			{
				std::cout << "Invalid number! Try again.\n";
			}
			else
			{
				deck->AddCard(selectedCardID, numCardToAdd);
				break;
			}
		}
	}

	void Console::DeleteCardInDeck(Deck* deck, std::string& selectedCardID)
	{
		if (deck->GetNumCardInDeck(selectedCardID) == 0)
		{
			std::cout << selectedCardID << " doesn't exist.\n";
			return;
		}

		while (true)
		{
			std::cout << "How many cards to delete (0 - " << deck->GetNumCardInDeck(selectedCardID) << ") ? ";
			unsigned int numCardToDelete;
			std::cin >> numCardToDelete;

			if (numCardToDelete < 0 || numCardToDelete > deck->GetNumCardInDeck(selectedCardID))
			{
				std::cout << "Invalid number! Try again.\n";
			}
			else
			{
				deck->DeleteCard(selectedCardID, numCardToDelete);
				break;
			}
		}
	}

	int Console::Login()
	{
		std::cout << "    Welcome to Hearthstone++ Ver " << VERSION << '\n';

		ShowMenu(m_loginMenuStr);
		const size_t selectedNum = InputMenuNum("Select: ", LOGIN_MENU_SIZE);
		bool isFinish = false;

		if (selectedNum != LOGIN_MENU_SIZE)
		{
			m_loginMenuFuncs[selectedNum - 1](*this);
		}
		else
		{
			isFinish = true;
		}

		return isFinish ? 0 : Login();
	}

	int Console::Main()
	{
		ShowMenu(m_mainMenuStr);
		const size_t selectedNum = InputMenuNum("Select: ", MAIN_MENU_SIZE);
		bool isFinish = false;

		m_mainMenuFuncs[selectedNum - 1](*this);

		if (selectedNum == MAIN_MENU_SIZE)
		{
			isFinish = true;
		}

		return isFinish ? 0 : Main();
	}
}
