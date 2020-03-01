// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SetasideZone.hpp>

#include <algorithm>

namespace RosettaStone::Generic
{
void ChoiceMulligan(Player* player, const std::vector<std::size_t>& choices)
{
    // Block it if player tries to mulligan in a non-mulligan choice
    if (player->choice.value().choiceType != ChoiceType::MULLIGAN)
    {
        return;
    }

    // Block it if player tries to mulligan a card that doesn't exist
    Choice& choice = player->choice.value();
    for (const auto chooseID : choices)
    {
        if (std::find(choice.choices.begin(), choice.choices.end(), chooseID) ==
            choice.choices.end())
        {
            return;
        }
    }

    // Process mulligan by choice action
    switch (choice.choiceAction)
    {
        case ChoiceAction::HAND:
        {
            // Process mulligan state
            player->mulliganState = Mulligan::DEALING;

            auto hand = player->GetHandZone();
            auto deck = player->GetDeckZone();

            // Collect cards to redraw
            std::vector<Playable*> mulliganList;
            for (const auto entity : hand->GetAll())
            {
                const bool isExist = std::find(choices.begin(), choices.end(),
                                               entity->id) == choices.end();
                if (isExist && entity->card->id != "GAME_005")
                {
                    mulliganList.push_back(entity);
                }
            }

            // Process redraw
            for (const auto& entity : mulliganList)
            {
                Playable* playable = deck->Remove(deck->GetTopCard());
                AddCardToHand(player, playable);
                hand->Swap(entity, playable);

                hand->Remove(entity);
                deck->Add(entity);
                deck->Shuffle();
            }

            // It's done! - Reset choice
            player->choice = std::nullopt;

            break;
        }
        default:
            throw std::invalid_argument(
                "ChoiceMulligan() - Invalid choice action!");
    }
}

bool ChoicePick(Player* player, std::size_t choice)
{
    Choice choiceVal = player->choice.value();

    // Block it if player tries to pick in a non-general choice
    if (choiceVal.choiceType != ChoiceType::GENERAL)
    {
        return false;
    }

    // Block it if player tries to pick a card that doesn't exist
    if (std::find(choiceVal.choices.begin(), choiceVal.choices.end(), choice) ==
        choiceVal.choices.end())
    {
        return false;
    }

    // Get picked card using entity ID
    Playable* playable = player->GetSetasideZone()->GetEntity(choice);
    // Block it if player tries to pick a card that doesn't exist
    if (playable == nullptr)
    {
        return false;
    }

    // Process pick by choice action
    switch (choiceVal.choiceAction)
    {
        case ChoiceAction::HAND:
        {
            player->GetSetasideZone()->Remove(playable);
            AddCardToHand(player, playable);
            break;
        }
        default:
            throw std::invalid_argument(
                "ChoiceMulligan() - Invalid choice action!");
    }

    return true;
}

void CreateChoice(Player* player, ChoiceType type, ChoiceAction action,
                  const std::vector<std::size_t>& choices)
{
    // Block it if choice is exist
    if (player->choice != std::nullopt)
    {
        return;
    }

    // Create a choice for player
    Choice choice;
    choice.choiceType = type;
    choice.choiceAction = action;
    choice.choices = choices;

    player->choice = choice;
}

void CreateChoiceCards(Player* player, Entity* source, ChoiceType type,
                       ChoiceAction action, const std::vector<Card*>& choices)
{
    std::vector<std::size_t> choiceIDs;

    for (auto& card : choices)
    {
        std::map<GameTag, int> cardTags;
        cardTags.emplace(GameTag::CREATOR, source->id);
        cardTags.emplace(GameTag::DISPLAYED_CREATOR, source->id);

        Playable* choiceEntity = Entity::GetFromCard(player, card, cardTags,
                                                     player->GetSetasideZone());
        choiceIDs.emplace_back(choiceEntity->id);
    }

    Choice choice;
    choice.choiceType = type;
    choice.choiceAction = action;
    choice.choices = choiceIDs;

    if (!player->choice.has_value())
    {
        player->choice = choice;
    }
}
}  // namespace RosettaStone::Generic
