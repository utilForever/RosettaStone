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
#include <Interface/Interface.h>
#include <Loaders/CardLoader.h>
#include <Loaders/PlayerLoader.h>
#include <Models/Card.h>
#include <Models/Cards.h>

#include <cctype>
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
#include <regex>

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
        auto[filter, isValid, isFinish] =
            InputAndParseSearchCommand("Command > ");

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
    const size_t selectedClassNum =
        InputMenuNum("What's your player class? ", PLAYER_CLASS_SIZE);
    const CardClass deckClass = CardClass::_from_integral(static_cast<int>(selectedClassNum + 1));

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
    const size_t selectedDeck =
        InputMenuNum("Select: ", m_player->GetNumOfDeck());

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
    const size_t selectedDeck =
        InputMenuNum("Select: ", m_player->GetNumOfDeck());

    m_player->DeleteDeck(selectedDeck);
}

int Console::OperateDeck(size_t deckIndex)
{
    ShowMenu(m_deckOperationStr);
    const size_t selectedOperation =
        InputMenuNum("What do you want to do? ", CREATE_DECK_MENU_SIZE);
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
        int numCardToAddAvailable =
            card->GetMaxAllowedInDeck() - deck->GetNumCardInDeck(card->GetID());
        if (deck->GetNumOfCards() + numCardToAddAvailable >
            MAXIMUM_NUM_CARDS_IN_DECK)
        {
            numCardToAddAvailable = deck->GetNumOfCards() +
                                    numCardToAddAvailable -
                                    MAXIMUM_NUM_CARDS_IN_DECK;
        }

        std::cout << "How many cards to add (0 - " << numCardToAddAvailable
                  << ") ? ";
        int numCardToAdd;
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
    const size_t selectedCardIndex =
        InputMenuNum("Select: ", deck->GetUniqueNumOfCards());
    const std::string selectedCardID =
        deck->GetCard(selectedCardIndex - 1).first;

    while (true)
    {
        std::cout << "How many cards to delete (0 - "
                  << deck->GetNumCardInDeck(selectedCardID) << ") ? ";
        int numCardToDelete;
        std::cin >> numCardToDelete;

        int numCardinDeck =
            static_cast<int>(deck->GetNumCardInDeck(selectedCardID));
        if (numCardToDelete < 0 || numCardToDelete > numCardinDeck)
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

template <std::size_t SIZE>
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
    std::transform(str.begin(), str.end(), str.begin(), [](char c){return static_cast<char>(std::toupper(c));});

    return (str == "y" || str == "yes")
               ? true
               : (str == "n" || str == "no") ? false : InputYesNo(sentence);
}

std::tuple<SearchFilter, bool, bool> Console::InputAndParseSearchCommand(
    std::string commandStr) const
{
    // Output command string
    std::cout << commandStr;

    // Input commands
    std::string cmd;
    std::getline(std::cin, cmd);

    // Split commands by whitespace and quote
    std::istringstream iss(cmd);
    std::vector<std::string> cmdTokens{"Hearthstone++"};
    std::string cmdToken;

    while (iss >> std::quoted(cmdToken))
    {
        cmdTokens.push_back(cmdToken);
    }

    // Convert std::string to const char*
    std::vector<const char*> convertedSplitCmds{};
    for (const auto& token : cmdTokens)
    {
        convertedSplitCmds.push_back(token.c_str());
    }

    // Parse command
    bool showHelp = false;
    std::string strName, strRarity, strPlayerClass, strCardType;
    std::string strRace, strMechanics, strCost, strAttack, strHealth;
    bool isValid = true, isFinish = false;

    // Parsing
    auto parser =
        clara::Help(showHelp) |
        clara::Opt(strName, "name")["-n"]["--name"](
            "the name of a card"
            "(You can enclose the name with \"\", regardless of whether it "
            "contains spaces.)") |
        clara::Opt(strRarity, "rarity")["-r"]["--rarity"](
            "a rough measure of the quality and scarcity of a card") |
        clara::Opt(strPlayerClass, "playerClass")["-c"]["--class"](
            "the primary determinant of a hero's powers and abilities") |
        clara::Opt(strCardType, "cardType")["-t"]["--type"](
            "spell cards, weapon cards, minion cards and hero cards") |
        clara::Opt(strRace, "race")["-e"]["--race"](
            "does not directly affect the behavior of the minion, but allows "
            "it to be affected by certain type-specific effects") |
        clara::Opt(strCost, "cost")["-s"]["--cost"](
            "determines how much mana is required to play that card from the "
            "hand or to use that hero power"
            "(You can search for an exact value such as 3 or a range of values "
            "like 3-4.)") |
        clara::Opt(strAttack, "attack")["-a"]["--attack"](
            "the primary determinant of a hero's powers and abilities"
            "(You can search for an exact value such as 3 or a range of values "
            "like 3-4.)") |
        clara::Opt(strHealth, "health")["-l"]["--health"](
            "an attribute found on heroes and minions, reflecting the "
            "remaining survivability of the character"
            "(You can search for an exact value such as 3 or a range of values "
            "like 3-4.)") |
        clara::Opt(strMechanics, "mechanic")["-m"]["--mechanic"](
            "describes the total effect of playing that card or special "
            "effects or powers additional to the basic functions of the card") |
        clara::Opt(isFinish, "isFinish")["-f"]["--finish"]("finish the search");

    auto result = parser.parse(
        clara::Args(static_cast<int>(convertedSplitCmds.size()), convertedSplitCmds.data()));
    if (!result)
    {
        std::cerr << "Error in command line: " << result.errorMessage() << '\n';
        isValid = false;
    }

    if (showHelp)
    {
        std::cout << ToString(parser) << '\n';
        isValid = false;
    }

    Rarity rarity = Rarity::_from_string_nothrow(strRarity.c_str())
                        ? Rarity::_from_string(strRarity.c_str())
                        : Rarity::_from_string("INVALID");
    CardClass playerClass =
        CardClass::_from_string_nothrow(strPlayerClass.c_str())
            ? CardClass::_from_string(strPlayerClass.c_str())
            : CardClass::_from_string("INVALID");
    CardType cardType = CardType::_from_string_nothrow(strCardType.c_str())
                            ? CardType::_from_string(strCardType.c_str())
                            : CardType::_from_string("INVALID");
    Race race = Race::_from_string_nothrow(strRace.c_str())
                    ? Race::_from_string(strRace.c_str())
                    : Race::_from_string("INVALID");
    GameTag mechanic = GameTag::_from_string_nothrow(strMechanics.c_str())
                            ? GameTag::_from_string(strMechanics.c_str())
                            : GameTag::_from_string("INVALID");

    auto[minCost, maxCost] = ParseValueRangeFromString(strCost, isValid);
    auto[minAttack, maxAttack] = ParseValueRangeFromString(strAttack, isValid);
    auto[minHealth, maxHealth] = ParseValueRangeFromString(strHealth, isValid);

    SearchFilter filter;
    filter.rarity = rarity;
    filter.playerClass = playerClass;
    filter.cardType = cardType;
    filter.race = race;
    filter.name = strName;
    filter.costMin = minCost;
    filter.costMax = maxCost;
    filter.attackMin = minAttack;
    filter.attackMax = maxAttack;
    filter.healthMin = minHealth;
    filter.healthMax = maxHealth;
    filter.mechanic = mechanic;

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

        bool rarityCondition = (filter.rarity == +Rarity::INVALID ||
                                filter.rarity == card->GetRarity());
        bool classCondition = false;

        // When search mode is adding a card to a deck, the class is fixed to
        // the deck class and the neutral class.
        if (m_searchMode == SearchMode::AddCardInDeck)
        {
            classCondition = (card->GetCardClass() == m_deckClass ||
                card->GetCardClass() == +CardClass::NEUTRAL);
        }
        else if (m_searchMode == SearchMode::JustSearch)
        {
            classCondition = (filter.playerClass == +CardClass::INVALID ||
                              filter.playerClass == card->GetCardClass());
        }
        bool typeCondition = (filter.cardType == +CardType::INVALID ||
                              filter.cardType == card->GetCardType());
        bool raceCondition =
            (filter.race == +Race::INVALID || filter.race == card->GetRace());
        bool nameCondition =
            (filter.name.empty() ||
             card->GetName().find(filter.name) != std::string::npos);
        bool costCondition =  filter.costMin <= card->GetCost() &&
            filter.costMax >= card->GetCost();
        bool attackCondition =
            filter.attackMin <= card->GetAttack() &&
            filter.attackMax >= card->GetAttack();
        bool healthCondition =
            filter.healthMin <= card->GetHealth() &&
            filter.healthMax >= card->GetHealth();
        bool mechanicsCondition = (filter.mechanic == +GameTag::INVALID ||
                                   card->HasMechanic(filter.mechanic));
        const bool isMatched =
            AllCondIsTrue(rarityCondition, classCondition, typeCondition,
                          raceCondition, nameCondition, costCondition,
                          attackCondition, healthCondition, mechanicsCondition);

        if (isMatched)
        {
            result.emplace_back(card);
        }
    }

    return result;
}

std::vector<std::string> Console::SplitString(std::string str,
                                              std::string delimiter) const
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
        tokens.emplace_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }

    return tokens;
}
}