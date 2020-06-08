// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CONSOLE_HPP
#define ROSETTASTONE_CONSOLE_HPP

#include <Rosetta/Common/Constants.hpp>
#include <Rosetta/PlayMode/Accounts/AccountInfo.hpp>
#include <Rosetta/PlayMode/Accounts/DeckInfo.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>

#include <array>
#include <cctype>
#include <functional>
#include <optional>
#include <regex>

constexpr std::size_t LOGIN_MENU_SIZE = 3;
constexpr std::size_t MAIN_MENU_SIZE = 4;
constexpr std::size_t MANAGE_DECK_MENU_SIZE = 4;
constexpr std::size_t CREATE_DECK_MENU_SIZE = 3;

inline std::size_t GetInputNum(const std::string& inputStr)
{
    const auto isNumber = [](const std::string& str) {
        auto iter = str.begin();

        while (iter != str.end() &&
               std::isdigit(static_cast<unsigned char>(*iter)))
        {
            ++iter;
        }

        return !str.empty() && iter == str.end();
    };

    if (isNumber(inputStr))
    {
        const auto inputNum = static_cast<std::size_t>(std::stoi(inputStr));
        return inputNum;
    }

    return 0;
}

inline std::tuple<int, int> ParseValueRangeFromString(const std::string& str,
                                                      bool& isValid)
{
    const std::regex reValueRange("([[:digit:]]+)(-[[:digit:]]+)?");
    std::smatch values;

    int minValue = 0, maxValue = std::numeric_limits<int>::max();
    if (!str.empty())
    {
        if (std::regex_match(str, values, reValueRange))
        {
            minValue = std::atoi(values[1].str().c_str());
            if (values[2].matched)
            {
                std::string truncatedStr = values[2].str().substr(1);
                maxValue = std::atoi(truncatedStr.c_str());
            }
            else
            {
                maxValue = minValue;
            }

            if (minValue > maxValue)
            {
                std::swap(minValue, maxValue);
            }
        }
        else
        {
            isValid = false;
        }
    }

    return std::make_tuple(minValue, maxValue);
}

namespace RosettaStone::PlayMode
{
class Console
{
 public:
    void SignIn();
    void SignUp();
    std::optional<Card*> SearchCard() const;
    int ManageDeck();
    void SimulateGame() const;
    void Leave();

    void CreateDeck();
    void ModifyDeck();
    void DeleteDeck() const;

    int OperateDeck(std::size_t deckIndex);

    void AddCardInDeck(std::size_t deckIndex);
    void DeleteCardInDeck(std::size_t deckIndex) const;

    int Login();
    int Main();

 private:
    enum class SearchMode
    {
        JustSearch,
        AddCardInDeck,
    };

    template <std::size_t SIZE>
    void ShowMenu(std::array<std::string, SIZE>& menus);

    std::size_t InputMenuNum(const std::string& questionStr,
                             std::size_t menuSize) const;
    bool InputYesNo(std::string& sentence) const;

    std::tuple<SearchFilter, bool, bool> InputAndParseSearchCommand(
        const std::string& commandStr) const;
    std::vector<Card*> ProcessSearchCommand(SearchFilter& filter) const;

    std::vector<std::string> SplitString(std::string str,
                                         const std::string& delimiter) const;

    std::array<std::string, LOGIN_MENU_SIZE> m_loginMenuStr = { "1. Sign in",
                                                                "2. Sign up",
                                                                "3. Exit" };
    std::array<std::function<void(Console&)>, LOGIN_MENU_SIZE - 1>
        m_loginMenuFuncs = { &Console::SignIn, &Console::SignUp };
    std::array<std::string, MAIN_MENU_SIZE> m_mainMenuStr = {
        "1. Search Card", "2. Manage Deck", "3. Simulate Game", "4. Leave"
    };
    std::array<std::function<void(Console&)>, MAIN_MENU_SIZE>
        m_mainMenuFuncs = { &Console::SearchCard, &Console::ManageDeck,
                            &Console::SimulateGame, &Console::Leave };
    std::array<std::string, MANAGE_DECK_MENU_SIZE> m_manageDeckStr = {
        "1. Create deck", "2. Modify deck", "3. Delete deck", "4. Back"
    };
    std::array<std::function<void(Console&)>, MANAGE_DECK_MENU_SIZE - 1>
        m_manageDeckFuncs = { &Console::CreateDeck, &Console::ModifyDeck,
                              &Console::DeleteDeck };
    std::array<std::string, NUM_PLAYER_CLASS> m_playerClassStr = {
        "1. Druid", "2. Hunter", "3. Mage",    "4. Paladin", "5. Priest",
        "6. Rogue", "7. Shaman", "8. Warlock", "9. Warrior"
    };
    std::array<std::string, CREATE_DECK_MENU_SIZE> m_deckOperationStr = {
        "1. Add Card(s)", "2. Delete Card(s)", "3. Back"
    };
    std::array<std::function<void(Console&, std::size_t)>,
               CREATE_DECK_MENU_SIZE - 1>
        m_deckOperationFuncs = { &Console::AddCardInDeck,
                                 &Console::DeleteCardInDeck };

    SearchMode m_searchMode = SearchMode::JustSearch;
    CardClass m_deckClass = CardClass::INVALID;

    AccountInfo* m_account = nullptr;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_CONSOLE_HPP
