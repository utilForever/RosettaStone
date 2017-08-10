/*************************************************************************
> File Name: main.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Main entry of Hearthstone++ simulator.
> Created Time: 2017/08/10
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <json/json.hpp>

#include <fstream>

using json = nlohmann::json;

int main()
{
	// Read card data from JSON file
	std::ifstream cardFile("cards.json");
	json j;

	if (cardFile.is_open())
	{
		cardFile >> j;
		std::cout << j << std::endl;
	}

	cardFile.close();

	return 0;
}