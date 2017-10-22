/*************************************************************************
> File Name: Interface.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/04
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/Interface.h>

namespace Hearthstonepp
{
	InteractBuffer::InteractBuffer(int capacity)
		: capacity(capacity), head(0), tail(0), usage(0), readable(false)
	{
		buffer = new BYTE[capacity]; // buffer, circular queue
	}

	int InteractBuffer::ReadBuffer(BYTE *data, int maxSize)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [this]() { return readable; }); // wait until the buffer can be read

		int read = 0;
		for (int i = 0; (i < usage) && maxSize; ++i) // read data from buffer
		{
			data[i] = buffer[head];

			head = (head + 1) % capacity;
			maxSize -= 1;
			read += 1;
		}

		usage -= read; // calculate remaining capacity to read

		readable = false;
		cv.notify_one(); // inform buffer is writable

		return read;
	}

	int InteractBuffer::WriteBuffer(BYTE *data, int size)
	{
		std::unique_lock<std::mutex> lock(mtx);
		cv.wait(lock, [this]() { return !readable; }); // wait until the buffer can be write

		for (int i = 0; (i < size) && (usage < capacity); ++i) // write data to buffer
		{
			buffer[tail] = data[i];

			tail = (tail + 1) % capacity;
			usage += 1;
		}

		readable = true;
		cv.notify_one(); // inform buffer is readable

		return usage;
	}
}