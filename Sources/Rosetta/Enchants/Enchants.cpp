// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enchants/Effects.hpp>
#include <Rosetta/Enchants/Enchants.hpp>

#include <regex>

namespace RosettaStone
{
Enchant Enchants::GetEnchantFromText(std::string cardID)
{
    std::vector<Effect> effects;

    static std::regex attackRegex("\\+([[:digit:]]+) Attack");

    std::string text = Cards::FindCardByID(cardID).text;
    std::smatch values;

    if (std::regex_search(text, values, attackRegex))
    {
        effects.emplace_back(Effects::AttackN(std::stoi(values[1].str())));
    }

    return Enchant(effects);
}
}  // namespace RosettaStone
