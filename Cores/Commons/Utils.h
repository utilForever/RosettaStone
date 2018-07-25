/*************************************************************************
> File Name: Utils.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Utility functions for Hearthstone++.
> Created Time: 2017/10/29
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_UTILS_H
#define HEARTHSTONEPP_UTILS_H

template <typename T>
constexpr bool AllCondIsTrue(const T& t)
{
	return t == true;
}

template <typename T, typename... Others>
constexpr bool AllCondIsTrue(const T& t, Others const&... args)
{
	return (t == true) && AllCondIsTrue(args...);
}

#endif