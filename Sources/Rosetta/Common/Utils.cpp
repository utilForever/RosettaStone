// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Utils.hpp>

std::vector<unsigned char> DecodeBase64(std::string_view src)
{
    static constexpr int decodeTable[256] = {
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, 52, 53, 54, 55, 56, 57,
        58, 59, 60, 61, -1, -1, -1, -1, -1, -1, -1, 0,  1,  2,  3,  4,  5,  6,
        7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
        25, -1, -1, -1, -1, -1, -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
        37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
        -1, -1, -1, -1
    };

    union
    {
        struct
        {
            unsigned char c1, c2, c3;
        } chCode;

        struct
        {
            unsigned int e1 : 6, e2 : 6, e3 : 6, e4 : 6;
        } intCode;
    } temp;

    std::vector<unsigned char> ret;
    std::vector<unsigned char> srcTmp(begin(src), end(src));

    int blank = 0;
    for (std::size_t i = 0; i < src.size(); i += 4)
    {
        temp.intCode.e4 = decodeTable[srcTmp[i]];
        temp.intCode.e3 = decodeTable[srcTmp[i + 1]];

        if (src[i + 2] == '=')
        {
            temp.intCode.e2 = 0;
            ++blank;
        }
        else
        {
            temp.intCode.e2 = decodeTable[srcTmp[i + 2]];
        }

        if (src[i + 3] == '=')
        {
            temp.intCode.e1 = 0;
            ++blank;
        }
        else
        {
            temp.intCode.e1 = decodeTable[srcTmp[i + 3]];
        }

        ret.emplace_back(temp.chCode.c3);
        ret.emplace_back(temp.chCode.c2);
        ret.emplace_back(temp.chCode.c1);
    }

    for (int i = 0; i < blank; ++i)
    {
        ret.pop_back();
    }

    return ret;
}
