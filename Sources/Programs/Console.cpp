/*************************************************************************
> File Name: Console.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Console version of Hearthstone++ game.
> Created Time: 2017/10/08
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Commons/Constants.h>
#include <Programs/Console.h>

#include <iostream>

namespace Hearthstonepp
{
	void Console::ShowMenu()
	{
		std::cout << "    Welcome to Hearthstone++ Ver " << VERSION << '\n';
		std::cout << "========================================\n";
		for (auto& menu : m_menuStr)
		{
			std::cout << menu.c_str() << '\n';
		}
		std::cout << "========================================\n";
		std::cout << "Select: ";
	}

	size_t Console::InputMenuNum()
	{
		size_t num;
		std::cin >> num;
		return num;
	}

	void Console::SearchCard()
	{

	}

	void Console::ShowCardInfo()
	{

	}

	void Console::MakeDeck()
	{

	}

	void Console::LoadDeck()
	{

	}

	void Console::StoreDeck()
	{
		
	}

	void Console::SimulateGame()
	{
		
	}

	int Console::Play()
	{
		ShowMenu();

		const size_t selectedNum = InputMenuNum();
		bool isFinish = false;

		if (selectedNum < 0 || selectedNum > MENU_SIZE)
		{
			std::cout << "\nInvalid number! Try again.\n\n";
		}
		else if (selectedNum != MENU_SIZE)
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