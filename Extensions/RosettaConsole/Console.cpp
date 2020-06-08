// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "Console.hpp"

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/Common/Macros.hpp>
#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Cards/Card.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Loaders/AccountLoader.hpp>
#include <Rosetta/PlayMode/Loaders/CardLoader.hpp>

#include <lyra/cli_parser.hpp>
#include <lyra/help.hpp>
#include <lyra/opt.hpp>

#include <cctype>
#if defined(ROSETTASTONE_WINDOWS)
#include <filesystem>
#elif defined(ROSETTASTONE_LINUX)
#include <experimental/filesystem>
#elif defined(ROSETTASTONE_MACOSX)
#include <sys/stat.h>
#endif
#include <fstream>
#include <iomanip>
#include <iostream>

#if defined(ROSETTASTONE_WINDOWS)
namespace filesystem = std::filesystem;
#elif defined(ROSETTASTONE_LINUX)
namespace filesystem = std::experimental::filesystem;
#endif

namespace RosettaStone::PlayMode
{
void Console::SignIn()
{
    std::cout << "Input Account ID to load data.\n";
    std::cout << "If you do not want to load, please input \"STOP\"\n";

    while (true)
    {
        std::cout << "Account ID: ";
        std::string accountID;
        std::cin >> accountID;

        if (accountID == "STOP")
        {
            break;
        }

#ifndef ROSETTASTONE_MACOSX
        if (!filesystem::exists("Datas/" + accountID + ".json"))
#else
        struct stat buf;
        std::string path = "Datas/" + accountID + ".json";
        if (stat(path.c_str(), &buf) == -1)
#endif
        {
            std::cout << accountID << ".json doesn't exist. Try again.\n";
            continue;
        }

        AccountLoader loader;
        m_account = loader.Load(accountID);

        if (m_account == nullptr)
        {
            std::cout << "An error occurred while loading account data.\n";
            continue;
        }

        std::cout << "You are signed in. Hello, " << accountID << "!\n";

        Main();

        break;
    }
}

void Console::SignUp()
{
    std::cout << "Input Account ID to create data.\n";

    while (true)
    {
        std::cout << "Account ID: ";
        std::string accountID;
        std::cin >> accountID;

#if defined(ROSETTASTONE_WINDOWS) || defined(ROSETTASTONE_LINUX)
        if (filesystem::exists("Datas/" + accountID + ".json"))
#elif defined(ROSETTASTONE_MACOSX)
        struct stat buf;
        std::string path = "Datas/" + accountID + ".json";
        if (stat(path.c_str(), &buf) == 0)
#endif
        {
            std::cout << accountID << ".json already exists. Try again.\n";
            continue;
        }

        std::cout << "Name: ";
        std::string name;
        std::cin >> name;

        m_account = new AccountInfo(std::move(accountID), std::move(name));

        AccountLoader loader;
        loader.Save(m_account);

        std::cout << "Your account has been created. Please sign in.\n";
        break;
    }
}

std::optional<Card*> Console::SearchCard() const
{
    std::cout << "========================================\n";
    std::cout << "              Search Card!              \n";
    std::cout << "========================================\n";

    // Extracts and discards characters from the input stream.
    std::cin.ignore();

    std::cout << "If you want to get help, type -h or --help.\n";

    while (true)
    {
        auto [filter, isValid, isFinish] =
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

        std::vector<Card*> result = ProcessSearchCommand(filter);
        if (result.empty())
        {
            std::cout << "There are no cards matching your search condition.\n";
        }
        else
        {
            std::size_t cardIdx = 1;

            for (Card* card : result)
            {
                std::cout << cardIdx << ". ";
                card->ShowBriefInfo();
                std::cout << '\n';

                cardIdx++;
            }

            if (m_searchMode == SearchMode::AddCardInDeck)
            {
                const std::size_t selectedCardIndex =
                    InputMenuNum("Select: ", cardIdx);
                return result.at(selectedCardIndex - 1);
            }
        }
    }

    return std::nullopt;
}

int Console::ManageDeck()
{
    std::cout << "========================================\n";
    std::cout << "              Manage Deck!              \n";
    std::cout << "========================================\n";

    ShowMenu(m_manageDeckStr);
    const std::size_t selectedNum =
        InputMenuNum("Select: ", MANAGE_DECK_MENU_SIZE);
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

void Console::SimulateGame() const
{
    int deckIndex1, deckIndex2;
    std::string user1, user2;

    std::cout << "[*] input first id, deck index : ";
    std::cin >> user1 >> deckIndex1;

    std::cout << "[*] input second id, deck index : ";
    std::cin >> user2 >> deckIndex2;

    AccountLoader loader;
    AccountInfo* p1 = loader.Load(user1);
    AccountInfo* p2 = loader.Load(user2);

    DeckInfo* deck1 = p1->GetDeck(deckIndex1);
    DeckInfo* deck2 = p2->GetDeck(deckIndex2);

    GameConfig config;
    config.player1Class = deck1->GetClass();
    config.player2Class = deck2->GetClass();

    Game game(config);
    game.GetPlayer1()->nickname = p1->GetNickname();
    game.GetPlayer2()->nickname = p2->GetNickname();

    game.Start();
}

void Console::Leave()
{
    AccountLoader loader;
    loader.Save(m_account);

    if (m_account != nullptr)
    {
        delete m_account;
        m_account = nullptr;
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
    const std::size_t selectedClassNum =
        InputMenuNum("What's your player class? ", NUM_PLAYER_CLASS);
    const CardClass deckClass = static_cast<CardClass>(selectedClassNum + 1);

    m_account->CreateDeck(name, deckClass);

    OperateDeck(m_account->GetNumOfDeck());
}

void Console::ModifyDeck()
{
    if (m_account->GetNumOfDeck() == 0)
    {
        std::cout << "Deck does not exist. Create a new deck!\n";
        return;
    }

    std::cout << "========================================\n";
    std::cout << "              Modify Deck!              \n";
    std::cout << "========================================\n";

    std::cout << "Input the number to modify your deck.\n";

    m_account->ShowDeckList();
    const std::size_t selectedDeck =
        InputMenuNum("Select: ", m_account->GetNumOfDeck());

    OperateDeck(selectedDeck);
}

void Console::DeleteDeck() const
{
    if (m_account->GetNumOfDeck() == 0)
    {
        std::cout << "Deck does not exist. Create a new deck!\n";
        return;
    }

    std::cout << "========================================\n";
    std::cout << "              Delete Deck!              \n";
    std::cout << "========================================\n";

    std::cout << "Input the number to delete your deck.\n";

    m_account->ShowDeckList();
    const std::size_t selectedDeck =
        InputMenuNum("Select: ", m_account->GetNumOfDeck());

    m_account->DeleteDeck(selectedDeck);
}

int Console::OperateDeck(std::size_t deckIndex)
{
    ShowMenu(m_deckOperationStr);
    const std::size_t selectedOperation =
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

void Console::AddCardInDeck(std::size_t deckIndex)
{
    DeckInfo* deck = m_account->GetDeck(deckIndex - 1);

    if (deck->GetNumOfCards() >= START_DECK_SIZE)
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
        std::cout << "Card is NULL value. Try again.\n";
        return;
    }

    if (card->id.empty())
    {
        std::cout << "The ID of card doesn't exist. Try again.\n";
        return;
    }

    while (true)
    {
        std::size_t numCardToAddAvailable =
            card->GetMaxAllowedInDeck() - deck->GetNumCardInDeck(card->id);
        if (deck->GetNumOfCards() + numCardToAddAvailable > START_DECK_SIZE)
        {
            numCardToAddAvailable =
                deck->GetNumOfCards() + numCardToAddAvailable - START_DECK_SIZE;
        }

        std::cout << "How many cards to add (0 - " << numCardToAddAvailable
                  << ") ? ";
        std::size_t numCardToAdd;
        std::cin >> numCardToAdd;

        if (numCardToAdd > numCardToAddAvailable)
        {
            std::cout << "Invalid number! Try again.\n";
        }
        else
        {
            deck->AddCard(card->id, numCardToAdd);
            break;
        }
    }
}

void Console::DeleteCardInDeck(std::size_t deckIndex) const
{
    DeckInfo* deck = m_account->GetDeck(deckIndex - 1);

    if (deck->GetNumOfCards() == 0)
    {
        std::cout << "The deck " << deck->GetName() << " is empty.\n";
        return;
    }

    deck->ShowCardList();
    const std::size_t selectedCardIndex =
        InputMenuNum("Select: ", deck->GetUniqueNumOfCards());
    const std::string selectedCardID =
        deck->GetCard(selectedCardIndex - 1).first;

    while (true)
    {
        std::cout << "How many cards to delete (0 - "
                  << deck->GetNumCardInDeck(selectedCardID) << ") ? ";
        std::size_t numCardToDelete;
        std::cin >> numCardToDelete;

        const std::size_t numCardinDeck =
            deck->GetNumCardInDeck(selectedCardID);
        if (numCardToDelete > numCardinDeck)
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
    std::cout << "    Welcome to RosettaStone Ver " << VERSION << '\n';

    ShowMenu(m_loginMenuStr);
    const std::size_t selectedNum = InputMenuNum("Select: ", LOGIN_MENU_SIZE);
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
    const std::size_t selectedNum = InputMenuNum("Select: ", MAIN_MENU_SIZE);
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

std::size_t Console::InputMenuNum(const std::string& questionStr,
                                  std::size_t menuSize) const
{
    while (true)
    {
        std::cout << questionStr;
        std::string inputStr;
        std::cin >> inputStr;

        const std::size_t num = GetInputNum(inputStr);
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

bool Console::InputYesNo(std::string& sentence) const
{
    std::cout << sentence;
    std::cout << "(Please input \"y/yes\" or \"n/no\" (insensitive))\n";
    std::cout << "Input: ";

    std::string str;
    std::cin >> str;
    std::transform(str.begin(), str.end(), str.begin(),
                   [](char c) { return static_cast<char>(std::toupper(c)); });

    return (str == "y" || str == "yes")
               ? true
               : (str == "n" || str == "no") ? false : InputYesNo(sentence);
}

std::tuple<SearchFilter, bool, bool> Console::InputAndParseSearchCommand(
    const std::string& commandStr) const
{
    // Output command string
    std::cout << commandStr;

    // Input commands
    std::string cmd;
    std::getline(std::cin, cmd);

    // Split commands by whitespace and quote
    std::istringstream iss(cmd);
    std::vector<std::string> cmdTokens{ "RosettaStone" };
    std::string cmdToken;

    while (iss >> std::quoted(cmdToken))
    {
        cmdTokens.push_back(cmdToken);
    }

    // Convert std::string to const char*
    std::vector<const char*> convertedSplitCmds{};
    convertedSplitCmds.reserve(cmdTokens.size());
    for (const auto& token : cmdTokens)
    {
        convertedSplitCmds.push_back(token.c_str());
    }

    // Parse command
    bool showHelp = false;
    std::string strName, strRarity, strPlayerClass, strCardType;
    std::string strRace, strGameTag, strCost, strAttack, strHealth;
    bool isValid = true, isFinish = false;

    // Parsing
    auto parser =
        lyra::cli_parser() | lyra::help(showHelp) |
        lyra::opt(strName, "name")["-n"]["--name"](
            "the name of a card"
            "(You can enclose the name with \"\", regardless of whether it "
            "contains spaces.)") |
        lyra::opt(strRarity, "rarity")["-r"]["--rarity"](
            "a rough measure of the quality and scarcity of a card") |
        lyra::opt(strPlayerClass, "playerClass")["-c"]["--class"](
            "the primary determinant of a hero's powers and abilities") |
        lyra::opt(strCardType, "cardType")["-t"]["--type"](
            "spell cards, weapon cards, minion cards and hero cards") |
        lyra::opt(strRace, "race")["-e"]["--race"](
            "does not directly affect the behavior of the minion, but allows "
            "it to be affected by certain type-specific effects") |
        lyra::opt(strCost, "cost")["-s"]["--cost"](
            "determines how much mana is required to play that card from the "
            "hand or to use that hero power"
            "(You can search for an exact value such as 3 or a range of values "
            "like 3-4.)") |
        lyra::opt(strAttack, "attack")["-a"]["--attack"](
            "the primary determinant of a hero's powers and abilities"
            "(You can search for an exact value such as 3 or a range of values "
            "like 3-4.)") |
        lyra::opt(strHealth, "health")["-l"]["--health"](
            "an attribute found on heroes and minions, reflecting the "
            "remaining survivability of the character"
            "(You can search for an exact value such as 3 or a range of values "
            "like 3-4.)") |
        lyra::opt(strGameTag, "mechanic")["-m"]["--mechanic"](
            "describes the total effect of playing that card or special "
            "effects or powers additional to the basic functions of the card") |
        lyra::opt(isFinish, "isFinish")["-f"]["--finish"]("finish the search");

    auto result =
        parser.parse(lyra::args(static_cast<int>(convertedSplitCmds.size()),
                                convertedSplitCmds.data()));
    if (!result)
    {
        std::cerr << "Error in command line: " << result.errorMessage() << '\n';
        isValid = false;
    }

    if (showHelp)
    {
        std::cout << parser << '\n';
        isValid = false;
    }

    const Rarity rarity = StrToEnum<Rarity>(strRarity);
    const CardClass playerClass = StrToEnum<CardClass>(strPlayerClass);
    const CardType cardType = StrToEnum<CardType>(strCardType);
    const Race race = StrToEnum<Race>(strRace);
    const GameTag gameTag = StrToEnum<GameTag>(strGameTag);

    auto [minCost, maxCost] = ParseValueRangeFromString(strCost, isValid);
    auto [minAttack, maxAttack] = ParseValueRangeFromString(strAttack, isValid);
    auto [minHealth, maxHealth] = ParseValueRangeFromString(strHealth, isValid);

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
    filter.gameTag = gameTag;

    return std::make_tuple(filter, isValid, isFinish);
}

std::vector<Card*> Console::ProcessSearchCommand(SearchFilter& filter) const
{
    std::vector<Card*> result;

    for (Card* card : Cards::GetInstance().GetAllCards())
    {
        if (card->gameTags.at(GameTag::COLLECTIBLE) == 0)
        {
            continue;
        }

        bool rarityCondition = (filter.rarity == Rarity::INVALID ||
                                filter.rarity == card->GetRarity());
        bool classCondition = false;

        // When search mode is adding a card to a deck, the class is fixed to
        // the deck class and the neutral class.
        if (m_searchMode == SearchMode::AddCardInDeck)
        {
            classCondition = (card->GetCardClass() == m_deckClass ||
                              card->GetCardClass() == CardClass::NEUTRAL);
        }
        else if (m_searchMode == SearchMode::JustSearch)
        {
            classCondition = (filter.playerClass == CardClass::INVALID ||
                              filter.playerClass == card->GetCardClass());
        }
        bool typeCondition = (filter.cardType == CardType::INVALID ||
                              filter.cardType == card->GetCardType());
        bool raceCondition =
            (filter.race == Race::INVALID || filter.race == card->GetRace());
        bool nameCondition =
            (filter.name.empty() ||
             card->name.find(filter.name) != std::string::npos);
        bool costCondition =
            filter.costMin <= card->gameTags.at(GameTag::COST) &&
            filter.costMax >= card->gameTags.at(GameTag::COST);
        bool attackCondition =
            filter.attackMin <= card->gameTags.at(GameTag::ATK) &&
            filter.attackMax >= card->gameTags.at(GameTag::ATK);
        bool healthCondition =
            filter.healthMin <= card->gameTags.at(GameTag::HEALTH) &&
            filter.healthMax >= card->gameTags.at(GameTag::HEALTH);
        bool mechanicsCondition = (filter.gameTag == GameTag::INVALID ||
                                   card->HasGameTag(filter.gameTag));
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

std::vector<std::string> Console::SplitString(
    std::string str, const std::string& delimiter) const
{
    std::size_t pos;
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
}  // namespace RosettaStone::PlayMode
