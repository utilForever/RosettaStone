// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_UTILS_HPP
#define ROSETTASTONE_UTILS_HPP

#include <effolkronium/random.hpp>

#include <algorithm>
#include <cstddef>
#include <functional>
#include <span>
#include <string>
#include <type_traits>
#include <vector>

using Random = effolkronium::random_static;

//! Checks all conditions are true.
//! \param t A value to check that it is true.
//! \return true if all conditions are true, false otherwise.
template <typename T>
constexpr bool AllCondIsTrue(const T& t)
{
    return static_cast<bool>(t);
}

//! Checks all conditions are true.
//! \param t A value to check that it is true.
//! \param args Rest values to check that they are true.
//! \return true if all conditions are true, false otherwise.
template <typename T, typename... Others>
constexpr bool AllCondIsTrue(const T& t, const Others&... args)
{
    return (static_cast<bool>(t)) && AllCondIsTrue(args...);
}

//! Erases item if it is matched predicate.
//! \param items A container consists of item.
//! \param predicate The condition to erase item.
template <typename ContainerT, typename PredicateT>
void EraseIf(ContainerT& items, const PredicateT& predicate)
{
    for (auto it = items.begin(); it != items.end();)
    {
        if (predicate(*it))
        {
            it = items.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

//! Gets N elements from a list of distinct elements by using the default
//! equality comparer. The source list must not have any repeated elements.
//! \param list A list of distinct elements to choose.
//! \param amount The number of elements to choose.
//! \return A list of N distinct elements.
template <typename T, std::size_t N>
std::vector<std::remove_cv_t<T>> ChooseNElements(std::span<T, N> list,
                                                std::size_t amount)
{
    std::vector<std::remove_cv_t<T>> results(list.begin(), list.end());

    Random::shuffle(results);
    results.erase(results.begin() + std::min(amount, results.size()),
                  results.end());

    return results;
}

//! Splits a string \p str using \p delim.
//! \param str An original string.
//! \param delim A string delimiter to split.
//! \return A splitted string.
inline std::vector<std::string> SplitString(const std::string& str,
                                            const std::string& delim)
{
    std::vector<std::string> tokens;
    std::size_t prev = 0, pos;

    do
    {
        pos = str.find(delim, prev);

        if (pos == std::string::npos)
        {
            pos = str.length();
        }

        std::string token = str.substr(prev, pos - prev);

        if (!token.empty())
        {
            tokens.push_back(token);
        }

        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());

    return tokens;
}

//! Removes all substrings \p pattern from a string \p str.
//! \param str An original string.
//! \param pattern A substring to remove.
template <typename T>
void RemoveSubstrs(std::basic_string<T>& str,
                   const std::basic_string<T>& pattern)
{
    typename std::basic_string<T>::size_type n = pattern.length();

    for (decltype(n) i = str.find(pattern); i != std::basic_string<T>::npos;
         i = str.find(pattern))
    {
        str.erase(i, n);

        // Insert whitespace instead of new line
        if (pattern == "\n" && str.substr(i - 1, 1) != " " &&
            str.substr(i, 1) != " ")
        {
            str.insert(i, " ");
        }
    }
}

//! Finds out if \p value starts with \p starting.
//! \param value The original string.
//! \param starting The suffix string to check.
//! \return true if \p value starts with \p starting, false otherwise.
inline bool StartsWith(const std::string& value, const std::string& starting)
{
    if (starting.size() > value.size())
    {
        return false;
    }

    return std::equal(starting.rbegin(), starting.rend(), value.rbegin());
}

//! Finds out if \p value ends with \p ending.
//! \param value The original string.
//! \param ending The suffix string to check.
//! \return true if \p value ends with \p ending, false otherwise.
inline bool EndsWith(const std::string& value, const std::string& ending)
{
    if (ending.size() > value.size())
    {
        return false;
    }

    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

//! Decodes Base64 based string.
//! \param src Base64 based string.
//! \return A unsigned char type container consists of decoded string.
std::vector<unsigned char> DecodeBase64(std::string_view src);

#endif  // ROSETTASTONE_UTILS_HPP
