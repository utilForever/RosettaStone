// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_MACROS_H
#define HEARTHSTONEPP_MACROS_H

#if defined(_WIN32) || defined(_WIN64)
#define HEARTHSTONEPP_WINDOWS
#elif defined(__APPLE__)
#define HEARTHSTONEPP_APPLE
#ifndef HEARTHSTONEPP_IOS
#define HEARTHSTONEPP_MACOSX
#endif
#elif defined(linux) || defined(__linux__)
#define HEARTHSTONEPP_LINUX
#endif

#endif