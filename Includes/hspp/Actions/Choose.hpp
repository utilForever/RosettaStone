// This code is based on Sabberstone project.
// Copyright (c) 2017-2018 SabberStone Team, darkfriend77 & rnilva
// Hearthstone++ is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef HEARTHSTONEPP_CHOOSE_HPP
#define HEARTHSTONEPP_CHOOSE_HPP

#include <hspp/Enums/CardEnums.hpp>
#include <hspp/Models/Choice.hpp>
#include <hspp/Models/Player.hpp>

namespace Hearthstonepp::Generic
{
//! Choices cards in mulligan state.
//! \param player The player to create a choice cards.
//! \param choices A container of card to choose.
void ChoiceMulligan(Player& player, std::vector<std::size_t>& choices);

//! Creates a choice for player.
//! \param player The player to create a choice.
//! \param type A choice type.
//! \param action A choice action.
//! \param choices A container of card to choose.
void CreateChoice(Player& player, ChoiceType type, ChoiceAction action,
                  std::vector<std::size_t>& choices);
}  // namespace Hearthstonepp::Generic

#endif  // HEARTHSTONEPP_DRAW_HPP
