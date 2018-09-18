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