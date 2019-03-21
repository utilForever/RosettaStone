// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_MACROS_HPP
#define ROSETTASTONE_MACROS_HPP

#if defined(_WIN32) || defined(_WIN64)
#define ROSETTASTONE_WINDOWS
#elif defined(__APPLE__)
#define ROSETTASTONE_APPLE
#ifndef ROSETTASTONE_IOS
#define ROSETTASTONE_MACOSX
#endif
#elif defined(linux) || defined(__linux__)
#define ROSETTASTONE_LINUX
#endif

#endif  // ROSETTASTONE_MACROS_HPP
