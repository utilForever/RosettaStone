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

	InteractBuffer::InteractBuffer(int capacity)
	{
		this->capacity = capacity;
		this->head = 0;
		this->tail = 0;
		this->usage = 0;
		this->readable = false;
		this->buffer = new BYTE[capacity];
	}

	int InteractBuffer::ReadBuffer(BYTE *data, int maxSize)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [this]() { return readable; });

		for (int i = 0; (i < usage) && maxSize; ++i)
		{
			data[i] = buffer[head];

			head = (head + 1) % capacity;
			maxSize -= 1;
		}

		int read = usage;
		usage = 0;

		readable = false;
		cv.notify_one();

		return read;
	}

	int InteractBuffer::WriteBuffer(BYTE *data, int size)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [this]() { return !readable; });

		for (int i = 0; (i < size) && (usage < capacity); ++i)
		{
			buffer[tail] = data[i];

			tail = (tail + 1) % capacity;
			usage += 1;
		}

		readable = true;
		cv.notify_one();

		return usage;
	}
}