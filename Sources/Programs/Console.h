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
#include <Models/Deck.h>
#include <Models/Player.h>

#include <array>
#include <functional>

namespace Hearthstonepp
{
	class Console
	{
	public:
		template<std::size_t SIZE>
		void ShowMenu(std::array<std::string, SIZE>& menus);

		size_t InputMenuNum(std::string questionStr, size_t menuSize);
		bool InputYesNo(std::string sentence) const;

		void SignIn();
		void SignUp();

		void SearchCard();
		int ManageDeck();
		void SimulateGame();
		void Leave();

		void CreateDeck();
		void ModifyDeck();
		void DeleteDeck();

		void OperateDeck(size_t selectedDeck);

		void AddCardInDeck(Deck* deck, std::string& selectedCardID);
		void DeleteCardInDeck(Deck* deck, std::string& selectedCardID);

		int Login();
		int Main();

	private:
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
		std::array<std::function<void(Console&, Deck*, std::string&)>, CREATE_DECK_MENU_SIZE - 1> m_deckOperationFuncs =
		{
			&Console::AddCardInDeck,
			&Console::DeleteCardInDeck
		};

		Player* m_player;
	};
}

#endif