/*************************************************************************
> File Name: Interface.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/04
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_UTILITY_H
#define HEARTHSTONEPP_UTILITY_H

#include <condition_variable>
#include <mutex>

namespace Hearthstonepp
{
	using BYTE = unsigned char;

	class InteractBuffer
	{
	public:
		InteractBuffer(int capacity);

		int ReadBuffer(BYTE *data, int maxSize);
		int WriteBuffer(BYTE *data, int size);

	private:
		std::mutex mtx;
		std::condition_variable cv;

		int capacity;
		bool readable = false;

		BYTE *buffer;
		int head = 0;
		int tail = 0;
		int usage = 0;
	};
}

#endif HEARTHSTONEPP_UTILITY_H