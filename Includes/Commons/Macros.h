/*************************************************************************
> File Name: Macros.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Macro lists for Hearthstone++.
> Created Time: 2017/12/26
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_MACROS_H
#define HEARTHSTONEPP_MACROS_H

#if defined(_WIN32) || defined(_WIN64)
#   define HEARTHSTONEPP_WINDOWS
#elif defined(__APPLE__)
#   define HEARTHSTONEPP_APPLE
#   ifndef HEARTHSTONEPP_IOS
#       define HEARTHSTONEPP_MACOSX
#   endif
#elif defined(linux) || defined(__linux__)
#   define HEARTHSTONEPP_LINUX
#endif

#endif