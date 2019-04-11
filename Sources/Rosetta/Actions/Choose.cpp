// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Actions/Generic.hpp>

#include <algorithm>

namespace RosettaStone::Generic
{
void ChoiceMulligan(Player& player, const std::vector<std::size_t>& choices)
{
    // Block it if player tries to mulligan in a non-mulligan choice
    if (player.choice.value().choiceType != ChoiceType::MULLIGAN)
    {
        return;
    }

    // Block it if player tries to mulligan a card that doesn't exist
    Choice& choice = player.choice.value();
    for (const auto choosedID : choices)
    {
        if (std::find(choice.choices.begin(), choice.choices.end(),
                      choosedID) == choice.choices.end())
        {
            return;
        }
    }

    // Process mulligan by choice action
    switch (player.choice.value().choiceAction)
    {
        case ChoiceAction::HAND:
        {
            // Process mulligan state
            player.mulliganState = Mulligan::DEALING;

            auto& hand = player.GetHand();
            auto& deck = player.GetDeck();

            // Collect cards to redraw
            std::vector<Entity*> mulliganList;
            for (const auto entity : hand.GetAllCards())
            {
                const bool isExist = std::find(choices.begin(), choices.end(),
                                               entity->id) == choices.end();
                if (isExist && entity->card.id != "GAME_005")
                {
                    mulliganList.push_back(entity);
                }
            }

            // Process redraw
            for (const auto& entity : mulliganList)
            {
                Entity& newCard = deck.RemoveCard(*deck.GetTopCard());
                Generic::AddCardToHand(player, &newCard);
                hand.SwapCard(*entity, newCard);

                Generic::RemoveCardFromHand(player, entity);
                deck.AddCard(*entity);
                deck.Shuffle();
            }

            // It's done! - Reset choice
            player.choice = std::nullopt;

            break;
        }
        default:
            throw std::invalid_argument(
                "ChoiceMulligan() - Invalid choice action!");
    }
}

void CreateChoice(Player& player, ChoiceType type, ChoiceAction action,
                  const std::vector<std::size_t>& choices)
{
    // Block it if choice is exist
    if (player.choice != std::nullopt)
    {
        return;
    }

    // Create a choice for player
    Choice choice;
    choice.choiceType = type;
    choice.choiceAction = action;
    choice.choices = choices;
    player.choice = choice;
}
}  // namespace RosettaStone::Generic
