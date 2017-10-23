/*************************************************************************
> File Name: Interface.h
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/04
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_INTERFACE_H
#define HEARTHSTONEPP_INTERFACE_H

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
		std::mutex m_mtx;
		std::condition_variable m_cv;

		int m_capacity;
		bool m_readable = false;

		BYTE *m_buffer;
		int m_head = 0;
		int m_tail = 0;
		int m_usage = 0;
	};
}

#endif