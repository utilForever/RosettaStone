// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Loaders/QuestLoader.hpp>

namespace RosettaStone
{
int QuestLoader::GetQuestProgressTotal(const std::string_view& cardID)
{
    if (cardID == "ULD_431")
    {
        return 5;
    }
    else if (cardID == "DRG_255")
    {
        return 3;
    }

    return 0;
}
}  // namespace RosettaStone