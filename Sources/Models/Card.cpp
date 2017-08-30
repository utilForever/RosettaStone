/*************************************************************************
> File Name: Card.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Card class that stores card information.
> Created Time: 2017/08/30
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Models/Card.h>

#include <iterator>
#include <sstream>

namespace Hearthstonepp
{
	std::string Card::AbbreviatedName(int size) const
	{
		if (m_name.length() < size)
		{
			return m_name;
		}
		
		if (m_name.find(" ") != std::string::npos)
		{
			return m_name.substr(0, size);
		}

		std::istringstream iss(m_name);
		std::vector<std::string> token{ std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{} };

		std::string ret = "";

		return ret;
	}
}