/*************************************************************************
> File Name: InteractBuffer.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: InteractBuffer for Hearthstone Game Agent
> Created Time: 2017/10/04
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_INTERACT_BUFFER_H
#define HEARTHSTONEPP_INTERACT_BUFFER_H

#include <condition_variable>
#include <mutex>

namespace Hearthstonepp
{
	using BYTE = unsigned char;

	class InteractBuffer
	{
	public:
		InteractBuffer(int capacity);

		size_t GetCapacity() const;

		size_t ReadBuffer(BYTE* data, size_t maxSize);
		size_t WriteBuffer(BYTE* data, size_t size);

	private:
		std::mutex m_mtx;
		std::condition_variable m_cv;

		size_t m_capacity;
		bool m_readable = false;

		BYTE* m_buffer;
		int m_head = 0;
		int m_tail = 0;
		size_t m_usage = 0;
	};
}

#endif