// Copyright (c) 2017-2023 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Enchants/Effects.hpp>
#include <Rosetta/PlayMode/Enchants/Enchants.hpp>

#include <regex>

namespace RosettaStone::PlayMode
{
std::shared_ptr<Enchant> Enchants::GetEnchantFromText(const std::string& cardID)
{
    std::vector<std::shared_ptr<IEffect>> effects;
    bool isOneTurn = false;

    static std::regex attackHealthRegex(
        R"(([\+\-][[:digit:]]+)/([\+\-][[:digit:]]+))");
    static std::regex setAttackHealthRegex("([[:digit:]]+)/([[:digit:]]+)");
    static std::regex attackRegex("([\\+\\-][[:digit:]]+) Attack");
    static std::regex healthRegex("([\\+\\-][[:digit:]]+) Health");

    const auto card = Cards::FindCardByID(cardID);
    const std::string text = card->text;
    std::smatch values;

    if (std::regex_search(text, values, attackHealthRegex))
    {
        effects.emplace_back(Effects::AttackN(std::stoi(values[1].str())));
        effects.emplace_back(Effects::HealthN(std::stoi(values[2].str())));
    }
    else if (std::regex_search(text, values, setAttackHealthRegex))
    {
        effects.emplace_back(Effects::SetAttack(std::stoi(values[1].str())));
        effects.emplace_back(
            Effects::SetBaseHealth(std::stoi(values[2].str())));
    }
    else if (std::regex_search(text, values, attackRegex))
    {
        effects.emplace_back(Effects::AttackN(std::stoi(values[1].str())));
    }
    else if (std::regex_search(text, values, healthRegex))
    {
        effects.emplace_back(Effects::HealthN(std::stoi(values[1].str())));
    }

    if (text.find("<b>Taunt</b>") != std::string::npos)
    {
        effects.emplace_back(Effects::Taunt);
    }

    if (text.find("<b>Poisonous</b>") != std::string::npos)
    {
        effects.emplace_back(Effects::Poisonous);
    }

    if (text.find("<b>Charge</b>") != std::string::npos)
    {
        effects.emplace_back(Effects::Charge);
    }

    if (text.find("<b>Windfury</b>") != std::string::npos)
    {
        effects.emplace_back(Effects::Windfury);
    }

    if (text.find("<b>Lifesteal</b>") != std::string::npos)
    {
        effects.emplace_back(Effects::Lifesteal);
    }

    if (text.find("<b>Immune</b>") != std::string::npos)
    {
        effects.emplace_back(Effects::Immune);
    }

    if (text.find("<b>Rush</b>") != std::string::npos)
    {
        effects.emplace_back(Effects::Rush);
    }

    if (text.find("<b>Divine Shield</b>") != std::string::npos)
    {
        effects.emplace_back(Effects::DivineShield);
    }

    if (text.find("this turn") != std::string::npos ||
        text.find("until end of turn") != std::string::npos ||
        card->gameTags[GameTag::TAG_ONE_TURN_EFFECT] > 0)
    {
        isOneTurn = true;
    }

    return std::make_shared<Enchant>(effects, false, isOneTurn);
}
}  // namespace RosettaStone::PlayMode
