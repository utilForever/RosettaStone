/*************************************************************************
> File Name: Utility.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Utility for Hearthstone Game Agent
> Created Time: 2017/10/04
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/Utility.h>

namespace Hearthstonepp
{
	RandomInt::RandomInt(int num)
	{
		std::random_device rd;
		this->gen = std::default_random_engine(rd());
		this->dist = std::uniform_int_distribution<int>(0, num - 1);
	}

	int RandomInt::get()
	{
		return dist(gen);
	}

	InteractBuffer::InteractBuffer()
	{
		CreatePipe(&hRead, &hWrite, NULL, 1024);
	}

	int InteractBuffer::ReadBuffer(BYTE *arr, int maxLength)
	{
		DWORD written = 0;
		ReadFile(&hRead, arr, maxLength, &written, NULL);
		return written;
	}

	int InteractBuffer::WriteBuffer(BYTE *arr, int size)
	{
		DWORD written = 0;
		WriteFile(&hWrite, arr, size, &written, NULL);
		return written;
	}
}