/*************************************************************************
> File Name: Console.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Console version of Hearthstone++ game.
> Created Time: 2017/10/08
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_CONSOLE_H
#define HEARTHSTONEPP_CONSOLE_H

#include <Commons/Constants.h>
#include <Commons/Macros.h>
#include <Models/Cards.h>
#include <Models/Deck.h>
#include <Models/Player.h>

#include <array>
#include <functional>
#ifndef HEARTHSTONEPP_MACOSX
#include <optional>
#else
#include <experimental/optional>
#endif

namespace Hearthstonepp
{
	class Console
	{
	public:
		void SignIn();
		void SignUp();
#ifndef HEARTHSTONEPP_MACOSX
		std::optional<Card*> SearchCard();
#else
		std::experimental::optional<Card*> SearchCard();
#endif
		int ManageDeck();
		void SimulateGame();
		void Leave();

		void CreateDeck();
		void ModifyDeck();
		void DeleteDeck();

		int OperateDeck(size_t deckIndex);

		void AddCardInDeck(size_t deckIndex);
		void DeleteCardInDeck(size_t deckIndex);

		int Login();
		int Main();

	private:
		enum class SearchMode
		{
			JustSearch,
			AddCardInDeck,
		};

		template<std::size_t SIZE>
		void ShowMenu(std::array<std::string, SIZE>& menus);
		void ShowSearchCardUsage() const;

		size_t InputMenuNum(std::string questionStr, size_t menuSize);
		bool InputYesNo(std::string sentence) const;

		std::tuple<SearchFilter, bool, bool> InputAndParseSearchCommand(std::string commandStr) const;
		std::vector<Card*> ProcessSearchCommand(SearchFilter filter) const;

		std::vector<std::string> SplitString(std::string str, std::string delimiter) const;

		std::array<std::string, LOGIN_MENU_SIZE> m_loginMenuStr =
		{
			"1. Sign in",
			"2. Sign up",
			"3. Exit"
		};
		std::array<std::function<void(Console&)>, LOGIN_MENU_SIZE - 1> m_loginMenuFuncs =
		{
			&Console::SignIn,
			&Console::SignUp
		};
		std::array<std::string, MAIN_MENU_SIZE> m_mainMenuStr =
		{
			"1. Search Card",
			"2. Manage Deck",
			"3. Simulate Game",
			"4. Leave"
		};
		std::array<std::function<void(Console&)>, MAIN_MENU_SIZE> m_mainMenuFuncs =
		{
			&Console::SearchCard,
			&Console::ManageDeck,
			&Console::SimulateGame,
			&Console::Leave
		};
		std::array<std::string, MANAGE_DECK_MENU_SIZE> m_manageDeckStr = 
		{
			"1. Create deck",
			"2. Modify deck",
			"3. Delete deck",
			"4. Back"
		};
		std::array<std::function<void(Console&)>, MANAGE_DECK_MENU_SIZE - 1> m_manageDeckFuncs =
		{
			&Console::CreateDeck,
			&Console::ModifyDeck,
			&Console::DeleteDeck
		};
		std::array<std::string, PLAYER_CLASS_SIZE> m_playerClassStr =
		{
			"1. Druid",
			"2. Hunter",
			"3. Mage",
			"4. Paladin",
			"5. Priest",
			"6. Rogue",
			"7. Shaman",
			"8. Warlock",
			"9. Warrior"
		};
		std::array<std::string, CREATE_DECK_MENU_SIZE> m_deckOperationStr =
		{
			"1. Add Card(s)",
			"2. Delete Card(s)",
			"3. Back"
		};
		std::array<std::function<void(Console&, size_t)>, CREATE_DECK_MENU_SIZE - 1> m_deckOperationFuncs =
		{
			&Console::AddCardInDeck,
			&Console::DeleteCardInDeck
		};

		SearchMode m_searchMode = SearchMode::JustSearch;
		CardClass m_deckClass = CardClass::INVALID;

		Player* m_player = nullptr;
	};
}

#endif