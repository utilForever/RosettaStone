// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_CHOOSE_HPP
#define ROSETTASTONE_PLAYMODE_CHOOSE_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/PlayMode/Models/Choice.hpp>
#include <Rosetta/PlayMode/Models/Player.hpp>

namespace RosettaStone::PlayMode::Generic
{
//! Choices cards in mulligan state.
//! \param player The player to create choice cards.
//! \param choices A container of card to choose.
void ChoiceMulligan(Player* player, const std::vector<int>& choices);

//! Choices a card in choose task state.
//! \param player The player to create a choice card.
//! \param choice A card to choose.
//! \return true if a card is successfully choose, false otherwise.
bool ChoicePick(Player* player, int choice);

//! Creates a choice for player.
//! \param player The player to create a choice.
//! \param source The source entity.
//! \param type A choice type.
//! \param action A choice action.
//! \param choices A container of card to choose.
void CreateChoice(Player* player, Entity* source, ChoiceType type,
                  ChoiceAction action, const std::vector<int>& choices);

//! Creates choice cards for player.
//! \param player The player to create choice cards.
//! \param source The source entity.
//! \param type A choice type.
//! \param action A choice action.
//! \param choices A container of card to choose.
void CreateChoiceCards(Player* player, Entity* source, ChoiceType type,
                       ChoiceAction action, const std::vector<Card*>& choices);
}  // namespace RosettaStone::PlayMode::Generic

#endif  // ROSETTASTONE_PLAYMODE_CHOOSE_HPP
