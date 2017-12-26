/*************************************************************************
> File Name: Console.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Console version of Hearthstone++ game.
> Created Time: 2017/10/08
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include "Console.h"

#include <Agents/GameAgent.h>
#include <Commons/Constants.h>
#include <Commons/Macros.h>
#include <Commons/Utils.h>
#include <Enums/EnumsToString.h>
#include <Interface/Interface.h>
#include <Loaders/CardLoader.h>
#include <Loaders/PlayerLoader.h>
#include <Models/Card.h>
#include <Models/Cards.h>

#ifdef HEARTHSTONEPP_WINDOWS
#include <filesystem>
#endif
#ifdef HEARTHSTONEPP_LINUX
#include <experimental/filesystem>
#endif
#ifdef HEARTHSTONEPP_MACOSX
#include <sys/stat.h>
#endif
#include <fstream>
#include <iostream>

#include <winix/getopt.h>

#ifndef HEARTHSTONEPP_MACOSX
namespace filesystem = std::experimental::filesystem;
#endif

namespace Hearthstonepp
{
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

#ifndef HEARTHSTONEPP_MACOSX
			if (!filesystem::exists("Datas/" + playerID + ".json"))
#else
			struct stat buf;
			std::string path = "Datas/" + playerID + ".json";
			if (stat(path.c_str(), &buf) == -1)
#endif
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

#ifndef HEARTHSTONEPP_MACOSX
			if (filesystem::exists("Datas/" + playerID + ".json"))
#else
			struct stat buf;
			std::string path = "Datas/" + playerID + ".json";
			if (stat(path.c_str(), &buf) == 0)
#endif
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
#ifndef HEARTHSTONEPP_MACOSX
	std::optional<Card*> Console::SearchCard()
#else
	std::experimental::optional<Card*> Console::SearchCard()
#endif
	{
		std::cout << "========================================\n";
		std::cout << "              Search Card!              \n";
		std::cout << "========================================\n";

		// Extracts and discards characters from the input stream.
		std::cin.ignore();

		std::cout << "If you want to get help, type -h or --help.\n";

		while (true)
		{
			auto[filter, isValid, isFinish] = InputAndParseSearchCommand("Command > ");

			if (!isValid)
			{
				continue;
			}
			
			if (isFinish)
			{
				break;
			}

			std::cout << "========================================\n";
			std::cout << "             Search Result!             \n";
			std::cout << "========================================\n";
			size_t idx = 1;
			std::vector<Card*> result = ProcessSearchCommand(filter);
			if (result.empty())
			{
				std::cout << "There are no cards matching your search condition.\n";
			}
			else
			{
				for (auto& card : result)
				{
					std::cout << idx << ". ";
					card->ShowBriefInfo();
					std::cout << '\n';

					idx++;
				}

				if (m_searchMode == SearchMode::AddCardInDeck)
				{
					const size_t selectedCardIndex = InputMenuNum("Select: ", idx);
					return result.at(selectedCardIndex);
				}
			}
		}

		return {};
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

	int Console::OperateDeck(size_t deckIndex)
	{
		ShowMenu(m_deckOperationStr);
		const size_t selectedOperation = InputMenuNum("What do you want to do? ", CREATE_DECK_MENU_SIZE);
		bool isFinish = false;

		if (selectedOperation != CREATE_DECK_MENU_SIZE)
		{
			m_deckOperationFuncs[selectedOperation - 1](*this, deckIndex);
		}
		else
		{
			isFinish = true;
		}

		return isFinish ? 0 : OperateDeck(deckIndex);
	}

	void Console::AddCardInDeck(size_t deckIndex)
	{
		Deck* deck = m_player->GetDeck(deckIndex - 1);

		if (deck->GetNumOfCards() >= MAXIMUM_NUM_CARDS_IN_DECK)
		{
			std::cout << "The deck " << deck->GetName() << " is full of cards.\n";
			return;
		}

		// Set flag that the card should be returned.
		m_searchMode = SearchMode::AddCardInDeck;
		m_deckClass = deck->GetClass();

		const Card* card = SearchCard().value_or(nullptr);
		if (card == nullptr)
		{
			std::cout << " doesn't exist. Try again.\n";
			return;
		}

		while (true)
		{
			unsigned int numCardToAddAvailable = card->GetMaxAllowedInDeck() - deck->GetNumCardInDeck(card->GetID());
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
				deck->AddCard(card->GetID(), numCardToAdd);
				break;
			}
		}
	}

	void Console::DeleteCardInDeck(size_t deckIndex)
	{
		Deck* deck = m_player->GetDeck(deckIndex - 1);

		if (deck->GetNumOfCards() == 0)
		{
			std::cout << "The deck " << deck->GetName() << " is empty.\n";
			return;
		}

		deck->ShowCardList();
		const size_t selectedCardIndex = InputMenuNum("Select: ", deck->GetUniqueNumOfCards());
		const std::string selectedCardID = deck->GetCard(selectedCardIndex - 1).first;

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

		// Set flag that you do not need to return the card.
		m_searchMode = SearchMode::JustSearch;
		m_deckClass = CardClass::INVALID;

		m_mainMenuFuncs[selectedNum - 1](*this);

		if (selectedNum == MAIN_MENU_SIZE)
		{
			isFinish = true;
		}

		return isFinish ? 0 : Main();
	}

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

	void Console::ShowSearchCardUsage() const
	{
		std::cout << "Usage: -r rarity -c class -t type -e race -n name -s cost -a attack -h health -m mechanics\n";
		std::cout << "-r, --rarity: a rough measure of the quality and scarcity of a card\n";
		std::cout << "(1 = Common, 2 = Free, 3 = Rare, 4 = Epic, 5 = Legendary)\n";
		std::cout << "-c, --class: the primary determinant of a hero's powers and abilities\n";
		std::cout << "(1 = Deathknight, 2 = Druid, 3 = Hunter, 4 = Mage, 5 = Paladin)\n";
		std::cout << "(6 = Priest, 7 = Rogue, 8 = Shaman, 9 = Warlock, 10 = Warrior)\n";
		std::cout << "-t, --type: spell cards, weapon cards, minion cards and hero cards\n";
		std::cout << "(3 = Hero, 4 = Minion, 5 = Spell, 7 = Weapon)\n";
		std::cout << "-e, --race: does not directly affect the behavior of the minion, but allows it to be affected by certain type-specific effects\n";
		std::cout << "(14 = Murloc, 15 = Demon, 17 = Mechanical, 18 = Elemental)\n";
		std::cout << "(20 = Beast, 21 = Totem, 23 = Pirate, 24 = Dragon)\n";
		std::cout << "-n, --name: the name of a card (must type \"_\" between words)\n";
		std::cout << "-s, --cost: determines how much mana is required to play that card from the hand or to use that hero power\n";
		std::cout << "-a, --attack: what occurs when a player commands one character to attack another, causing them to simultaneously deal damage to each other\n";
		std::cout << "-h, --health: an attribute found on heroes and minions, reflecting the remaining survivability of the character\n";
		std::cout << "(-s|-a|-h \"x\": exact value, -s|-a|-h \"x\",\"y\": range value)\n";
		std::cout << "-m, --mechanics: describes the total effect of playing that card or special effects or powers additional to the basic functions of the card\n";
		std::cout << "(546 = Adapt, 218 = Battlecry, 197 = Charge, 443 = Choose one, 220 = Combo)\n";
		std::cout << "(340 = Counter, 217 = Deathrattle, 415 = Discover, 194 = Divine Shield, 212 = Enraged)\n";
		std::cout << "(208 = Freeze, 240 = Immune, 403 = Inspire, 685 = Lifesteal, 215 = Overload)\n";
		std::cout << "(363 = Poisonous, 462 = Quest, 219 = Secret, 339 = Silence, 191 = Stealth)\n";
		std::cout << "(190 = Taunt, 189 = Windfury)\n";
		std::cout << "-p, --help: print this message\n";
		std::cout << "-x, --exit: exit the menu\n";
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

	std::tuple<SearchFilter, bool, bool> Console::InputAndParseSearchCommand(std::string commandStr) const
	{
		// Input commands
		std::cout << commandStr;

		char searchInput[256];
		std::cin.getline(searchInput, 256);

		int argc = 1;
		char** argv = new char*[32];
		char* context = nullptr;
		const char* delimiter = " ";

		for (int i = 0; i < 32; ++i)
		{
			argv[i] = new char[16];
		}

#ifdef HEARTHSTONEPP_WINDOWS
		argv[0] = _strdup("Hearthstone++");
#else
		argv[0] = strdup("Hearthstone++");
#endif

#ifdef HEARTHSTONEPP_WINDOWS
		char* nextToken = strtok_s(searchInput, delimiter, &context);
#else
		char* nextToken = strtok_r(searchInput, delimiter, &context);
#endif
		while (nextToken != nullptr)
		{
#ifdef HEARTHSTONEPP_WINDOWS
			argv[argc] = _strdup(nextToken);
			nextToken = strtok_s(context, delimiter, &context);
#else
			argv[argc] = strdup(nextToken);
			nextToken = strtok_r(context, delimiter, &context);
#endif
			argc++;
		}

		// Parse command
		std::vector<std::string> tokens;
		int opt, longIndex = 0;

		Rarity rarity = Rarity::INVALID;
		CardClass playerClass = CardClass::INVALID;
		CardType cardType = CardType::INVALID;
		Race race = Race::INVALID;
		std::string name = "";
		int costMin = -1, costMax = -1;
		int attackMin = -1, attackMax = -1;
		int healthMin = -1, healthMax = -1;
		std::vector<GameTag> mechanics;
		bool isValid = false, isFinish = false;

		// Parse options
		static struct option longOptions[] =
		{
			{ "rarity",		required_argument,	nullptr, 'r' },
			{ "class",		required_argument,	nullptr, 'c' },
			{ "type",		required_argument,	nullptr, 't' },
			{ "race",		required_argument,	nullptr, 'e' },
			{ "name",		required_argument,	nullptr, 'n' },
			{ "cost",		required_argument,	nullptr, 's' },
			{ "attack",		required_argument,	nullptr, 'a' },
			{ "health",		required_argument,	nullptr, 'h' },
			{ "mechanics",	required_argument,	nullptr, 'm' },
			{ "help",		no_argument,		nullptr, 'p' },
			{ "exit",		no_argument,		nullptr, 'x' },
			{ nullptr,		0,					nullptr,  0 }
		};

		// Initialize opt index
		optind = 1;

		while ((opt = getopt_long(argc, argv, "r:c:t:e:n:s:a:h:m:p:x", longOptions, &longIndex)) != -1)
		{
			isValid = true;

			switch (opt)
			{
			case 'r':
				rarity = static_cast<Rarity>(atoi(optarg));
				break;
			case 'c':
				playerClass = static_cast<CardClass>(atoi(optarg));
				break;
			case 't':
				cardType = static_cast<CardType>(atoi(optarg));
				break;
			case 'e':
				race = static_cast<Race>(atoi(optarg));
				break;
			case 'n':
				name = optarg;
				break;
			case 's':
				tokens.clear();
				tokens = SplitString(optarg, ",");

				if (tokens.size() == 1)
				{
					costMin = costMax = std::clamp(atoi(tokens[0].c_str()), 0, std::numeric_limits<int>::max());
				}
				else if (tokens.size() == 2)
				{
					costMin = std::clamp(atoi(tokens[0].c_str()), 0, std::numeric_limits<int>::max());
					costMax = std::clamp(atoi(tokens[1].c_str()), 0, std::numeric_limits<int>::max());
				}
				break;
			case 'a':
				tokens.clear();
				tokens = SplitString(optarg, ",");

				if (tokens.size() == 1)
				{
					attackMin = attackMax = std::clamp(atoi(tokens[0].c_str()), 0, std::numeric_limits<int>::max());
				}
				else if (tokens.size() == 2)
				{
					attackMin = std::clamp(atoi(tokens[0].c_str()), 0, std::numeric_limits<int>::max());
					attackMax = std::clamp(atoi(tokens[1].c_str()), 0, std::numeric_limits<int>::max());
				}
				break;
			case 'h':
				tokens.clear();
				tokens = SplitString(optarg, ",");

				if (tokens.size() == 1)
				{
					healthMin = healthMax = std::clamp(atoi(tokens[0].c_str()), 0, std::numeric_limits<int>::max());
				}
				else if (tokens.size() == 2)
				{
					healthMin = std::clamp(atoi(tokens[0].c_str()), 0, std::numeric_limits<int>::max());
					healthMax = std::clamp(atoi(tokens[1].c_str()), 0, std::numeric_limits<int>::max());
				}
				break;
			case 'm':
				tokens.clear();
				tokens = SplitString(optarg, ",");

				mechanics.clear();
				for (auto& token : tokens)
				{
					mechanics.emplace_back(std::move(static_cast<GameTag>(atoi(token.c_str()))));
				}
				break;
			case 'p':
				isValid = false;
				ShowSearchCardUsage();
				break;
			case 'x':
				isFinish = true;
				break;
			default:
				isValid = false;
				ShowSearchCardUsage();
				break;
			}
		}

		for (int i = 0; i < 32; ++i)
		{
			delete[] argv[i];
		}
		delete[] argv;

		SearchFilter filter;
		filter.rarity = rarity;
		filter.playerClass = playerClass;
		filter.cardType = cardType;
		filter.race = race;
		filter.name = name;
		filter.costMin = costMin;
		filter.costMax = costMax;
		filter.attackMin = attackMin;
		filter.attackMax = attackMax;
		filter.healthMin = healthMin;
		filter.healthMax = healthMax;
		filter.mechanics = mechanics;

		return std::make_tuple(filter, isValid, isFinish);
	}

	std::vector<Card*> Console::ProcessSearchCommand(SearchFilter filter) const
	{
		std::vector<Card*> result;

		for (auto& card : Cards::GetInstance()->GetAllCards())
		{
			if (card->GetCollectible() == false)
			{
				continue;
			}

			bool rarityCondition = (filter.rarity == Rarity::INVALID || filter.rarity == card->GetRarity());
			bool classCondition;
			// When search mode is adding a card to a deck, the class is fixed to the deck class and the neutral class.
			if (m_searchMode == SearchMode::AddCardInDeck)
			{
				if (filter.playerClass == CardClass::NEUTRAL || filter.playerClass == m_deckClass)
				{
					classCondition = filter.playerClass == card->GetCardClass();
				}
				else
				{
					classCondition = (card->GetCardClass() == CardClass::NEUTRAL || card->GetCardClass() == m_deckClass);
				}
			}
			else if (m_searchMode == SearchMode::JustSearch)
			{
				classCondition = (filter.playerClass == CardClass::INVALID || filter.playerClass == card->GetCardClass());
			}
			bool typeCondition = (filter.cardType == CardType::INVALID || filter.cardType == card->GetCardType());
			bool raceCondition = (filter.race == Race::INVALID || filter.race == card->GetRace());
			bool nameCondition = (filter.name.empty() || card->GetName().find(filter.name) != std::string::npos);
			bool costCondition = ((filter.costMin == -1 || filter.costMax == -1) || (filter.costMin <= card->GetCost() && filter.costMax >= card->GetCost()));
			bool attackCondition = ((filter.attackMin == -1 || filter.attackMax == -1) || (filter.attackMin <= card->GetAttack() && filter.attackMax >= card->GetAttack()));
			bool healthCondition = ((filter.healthMin == -1 || filter.healthMax == -1) || (filter.healthMin <= card->GetHealth() && filter.healthMax >= card->GetHealth()));
			bool mechanicsCondition = (filter.mechanics.size() == 0 || card->HasMechanics(filter.mechanics));
			const bool isMatched = AllCondIsTrue(rarityCondition, classCondition, typeCondition, raceCondition, nameCondition, costCondition, attackCondition, healthCondition, mechanicsCondition);

			if (isMatched)
			{
				result.emplace_back(card);
			}
		}

		return result;
	}

	std::vector<std::string> Console::SplitString(std::string str, std::string delimiter) const
	{
		size_t pos;
		std::vector<std::string> tokens;

		// If the number of tokens is 1
		if ((pos = str.find(delimiter)) == std::string::npos)
		{
			tokens.emplace_back(str);
			return tokens;
		}

		// If the number of tokens is greater than 1
		while ((pos = str.find(delimiter)) != std::string::npos)
		{
			tokens.emplace_back(std::move(str.substr(0, pos)));
			str.erase(0, pos + delimiter.length());
		}

		return tokens;
	}
}