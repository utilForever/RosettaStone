// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <hspp/Actions/Choose.hpp>

namespace Hearthstonepp::Generic
{
void CreateChoice(Player& player, ChoiceType type, ChoiceAction action,
                  std::vector<std::size_t> choices)
{
    // Block it if choice is exist
    if (player.choice.has_value())
    {
        return;
    }

    // Create a choice for player
    Choice& choice = player.choice.value();
    choice.choiceType = type;
    choice.choiceAction = action;
    choice.choices = choices;
}
}  // namespace Hearthstonepp::Generic