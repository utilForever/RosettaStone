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
		// wait until the buffer can be read
		m_cv.wait(lock, [this]() { return m_readable; });

		int read = 0;
		// read data from buffer
		for (int i = 0; (i < m_usage) && maxSize; ++i)
		{
			data[i] = m_buffer[m_head];

			m_head = (m_head + 1) % m_capacity;
			maxSize -= 1;
			read += 1;
		}

		// calculate remaining capacity to read
		m_usage -= read;

		m_readable = false;
		// inform buffer is writable
		m_cv.notify_one();

		return read;
	}

	int InteractBuffer::WriteBuffer(BYTE* data, int size)
	{
		std::unique_lock<std::mutex> lock(m_mtx);
		// wait until the buffer can be write
		m_cv.wait(lock, [this]() { return !m_readable; });

		// write data to buffer
		for (size_t i = 0; (i < size) && (m_usage < m_capacity); ++i)
		{
			m_buffer[m_tail] = data[i];

			m_tail = (m_tail + 1) % m_capacity;
			m_usage += 1;
		}

		m_readable = true;
		// inform buffer is readable
		m_cv.notify_one();

		return m_usage;
	}
}