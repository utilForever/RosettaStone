/*************************************************************************
> File Name: InteractBuffer.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: InteractBuffer for Hearthstone Game Agent
> Created Time: 2017/10/04
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Interface/InteractBuffer.h>

namespace Hearthstonepp
{
	InteractBuffer::InteractBuffer(int capacity)
		: m_capacity(capacity)
	{
		m_buffer = new BYTE[capacity]; // buffer, circular queue
	}

	int InteractBuffer::GetCapacity() const
	{
		return m_capacity;
	}

	int InteractBuffer::ReadBuffer(BYTE* data, int maxSize)
	{
		std::unique_lock<std::mutex> lock(m_mtx);
		m_cv.wait(lock, [this]() { return m_readable; }); // wait until the buffer can be read

		int read = 0;
		for (int i = 0; (i < m_usage) && maxSize; ++i) // read data from buffer
		{
			data[i] = m_buffer[m_head];

			m_head = (m_head + 1) % m_capacity;
			maxSize -= 1;
			read += 1;
		}

		m_usage -= read; // calculate remaining capacity to read

		m_readable = false;
		m_cv.notify_one(); // inform buffer is writable

		return read;
	}

	int InteractBuffer::WriteBuffer(BYTE* data, int size)
	{
		std::unique_lock<std::mutex> lock(m_mtx);
		m_cv.wait(lock, [this]() { return !m_readable; }); // wait until the buffer can be write

		for (size_t i = 0; (i < size) && (m_usage < m_capacity); ++i) // write data to buffer
		{
			m_buffer[m_tail] = data[i];

			m_tail = (m_tail + 1) % m_capacity;
			m_usage += 1;
		}

		m_readable = true;
		m_cv.notify_one(); // inform buffer is readable

		return m_usage;
	}
}