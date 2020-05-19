// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_BATTLEGROUNDS_CARD_ENUMS_HPP
#define ROSETTASTONE_BATTLEGROUNDS_CARD_ENUMS_HPP

#include <string>
#include <string_view>

namespace RosettaStone::Battlegrounds
{
//! \brief An enumerator for identifying the game tag of the card.
enum class GameTag
{
#define X(a) a,
#include "Rosetta/Common/Enums/GameTag.def"
#undef X
};

const std::string GAME_TAG_STR[] = {
#define X(a) #a,
#include "Rosetta/Common/Enums/GameTag.def"
#undef X
};

template <class T>
T StrToEnum(const std::string_view&);
template <class T>
std::string_view EnumToStr(T);

#define STR2ENUM(TYPE, ARRAY)                                                \
    template <>                                                              \
    inline TYPE StrToEnum<TYPE>(const std::string_view& str)                 \
    {                                                                        \
        for (std::size_t i = 0; i < (sizeof(ARRAY) / sizeof(ARRAY[0])); ++i) \
        {                                                                    \
            if (ARRAY[i] == str)                                             \
            {                                                                \
                return TYPE(i);                                              \
            }                                                                \
        }                                                                    \
                                                                             \
        return TYPE(0);                                                      \
    }

#define ENUM2STR(TYPE, ARRAY)                       \
    template <>                                     \
    inline std::string_view EnumToStr<TYPE>(TYPE v) \
    {                                               \
        return ARRAY[static_cast<int>(v)];          \
    }

#define ENUM_AND_STR(TYPE, ARRAY) \
    STR2ENUM(TYPE, ARRAY)         \
    ENUM2STR(TYPE, ARRAY)

ENUM_AND_STR(GameTag, GAME_TAG_STR)
}  // namespace RosettaStone::Battlegrounds

#endif  // ROSETTASTONE_BATTLEGROUNDS_CARD_ENUMS_HPP
