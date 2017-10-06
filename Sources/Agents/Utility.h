/*************************************************************************
> File Name: Utility.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Utility for Hearthstone Game Agent
> Created Time: 2017/10/04
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_UTILITY_H
#define HEARTHSTONEPP_UTILITY_H

#include <Windows.h>

#include <condition_variable>
#include <mutex>
#include <random>

namespace Hearthstonepp
{
	class RandomInt
	{
	public:
		RandomInt(int num);
		int get();

	private:
		std::default_random_engine gen;
		std::uniform_int_distribution<int> dist;
	};

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
		bool readable;

		BYTE *buffer;
		int usage;
		int head, tail;
	};
}

#endif HEARTHSTONEPP_UTILITY_H