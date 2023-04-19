// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Battlegrounds/Cards/Cards.hpp>
#include <Rosetta/Battlegrounds/Enchants/Enchants.hpp>

#include <regex>

namespace RosettaStone::Battlegrounds
{
Enchant Enchants::GetEnchantFromText(const std::string& cardID)
{
    std::vector<Effect> effects;

    static std::regex attackHealthRegex(
        R"(([\+\-][[:digit:]]+)/([\+\-][[:digit:]]+))");

    const auto card = Cards::FindCardByID(cardID);
    const std::string text = card.text;
    std::smatch values;

    if (std::regex_search(text, values, attackHealthRegex))
    {
        effects.emplace_back(Effects::AttackN(std::stoi(values[1].str())));
        effects.emplace_back(Effects::HealthN(std::stoi(values[2].str())));
    }

    return Enchant{ effects, false };
}
}  // namespace RosettaStone::Battlegrounds
