// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_CHOICE_HPP
#define ROSETTASTONE_CHOICE_HPP

#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Enums/ChoiceEnums.hpp>
#include <Rosetta/Models/Entity.hpp>

#include <vector>

namespace RosettaStone
{
//!
//! \brief Choice struct.
//!
//! This struct holds all configuration values to offer a choice of options.
//!
struct Choice
{
    //! Constructs task with given \p _player.
    //! \param _player The player context.
    Choice(Player* _player);

    //! Constructs task with given \p _player and \p _cardSets.
    //! \param _player The player context.
    //! \param _cardSets A list of cards to discover.
    Choice(Player* _player, std::vector<Card*> _cardSets);

    // Adds entity ID to stack.
    //! \param entityID The entity ID to add to stack.
    void AddToStack(int entityID);

    //! Tries to prepare next choice.
    void TryPrepare();

    //! Tries to pop next choice.
    //! \param lastChoice The chosen entity ID of last choice.
    //! \return The popped next choice.
    Choice* TryPopNextChoice(int lastChoice);

    ChoiceType choiceType = ChoiceType::INVALID;
    ChoiceAction choiceAction = ChoiceAction::INVALID;

    Player* player = nullptr;
    Entity* source = nullptr;
    std::vector<Card*> cardSets;
    std::vector<int> choices;
    std::vector<int> entityStack;

    int lastChoice = 0;
    Choice* nextChoice = nullptr;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_CHOICE_HPP
