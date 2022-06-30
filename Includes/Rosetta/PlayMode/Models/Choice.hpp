// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_CHOICE_HPP
#define ROSETTASTONE_PLAYMODE_CHOICE_HPP

#include <Rosetta/Common/Enums/CardEnums.hpp>
#include <Rosetta/Common/Enums/ChoiceEnums.hpp>
#include <Rosetta/PlayMode/Models/Entity.hpp>

#include <vector>

namespace RosettaStone::PlayMode
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
    explicit Choice(Player* _player);

    //! Constructs task with given \p _player and \p _cardSets.
    //! \param _player The player context.
    //! \param _cardSets A list of cards to discover.
    explicit Choice(Player* _player, std::vector<Card*> _cardSets);

    // Adds entity ID to stack.
    //! \param entityID The entity ID to add to stack.
    void AddToStack(int entityID);

    //! Tries to prepare next choice.
    void TryPrepare();

    //! Tries to pop next choice.
    //! \param _lastChoice The chosen entity ID of last choice.
    //! \return The popped next choice.
    Choice* TryPopNextChoice(const int _lastChoice) const;

    ChoiceType choiceType = ChoiceType::INVALID;
    ChoiceAction choiceAction = ChoiceAction::INVALID;

    Player* player = nullptr;
    Entity* source = nullptr;
    std::vector<Card*> cardSets;
    std::vector<int> choices;
    std::vector<int> entityStack;

    int depth = 1;
    int lastChoice = 0;
    Choice* nextChoice = nullptr;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_CHOICE_HPP
