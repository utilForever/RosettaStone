// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/CastSpell.hpp>
#include <Rosetta/Actions/Choose.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Actions/Summon.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Tasks/ITask.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>
#include <Rosetta/Zones/SetasideZone.hpp>

#include <algorithm>

namespace RosettaStone::Generic
{
void ChoiceMulligan(Player* player, const std::vector<int>& choices)
{
    Choice* choice = player->choice;
    if (choice == nullptr)
    {
        return;
    }

    // Block it if player tries to mulligan in a non-mulligan choice
    if (choice->choiceType != ChoiceType::MULLIGAN)
    {
        return;
    }

    // Block it if player tries to mulligan a card that doesn't exist
    for (const auto chooseID : choices)
    {
        if (std::find(choice->choices.begin(), choice->choices.end(),
                      chooseID) == choice->choices.end())
        {
            return;
        }
    }

    // Process mulligan by choice action
    switch (choice->choiceAction)
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
                const bool isExist =
                    std::find(choices.begin(), choices.end(),
                              entity->GetGameTag(GameTag::ENTITY_ID)) ==
                    choices.end();
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
            delete player->choice;
            player->choice = nullptr;

            break;
        }
        default:
            throw std::invalid_argument(
                "ChoiceMulligan() - Invalid choice action!");
    }
}

bool ChoicePick(Player* player, int choice)
{
    Choice* choiceVal = player->choice;
    if (choiceVal == nullptr)
    {
        return false;
    }

    // Block it if player tries to pick in a non-general choice
    if (choiceVal->choiceType != ChoiceType::GENERAL)
    {
        return false;
    }

    // Block it if player tries to pick a card that doesn't exist
    if (std::find(choiceVal->choices.begin(), choiceVal->choices.end(),
                  choice) == choiceVal->choices.end())
    {
        return false;
    }

    // Get picked card using entity ID
    Playable* playable = player->game->entityList[choice];
    // Block it if player tries to pick a card that doesn't exist
    if (playable == nullptr)
    {
        return false;
    }

    // Process pick by choice action
    switch (choiceVal->choiceAction)
    {
        case ChoiceAction::HAND:
        {
            player->GetSetasideZone()->Remove(playable);
            AddCardToHand(player, playable);
            break;
        }
        case ChoiceAction::ENCHANTMENT:
        {
            player->game->taskStack.num[0] = static_cast<int>(choice);
            break;
        }
        case ChoiceAction::CAST_SPELL:
        {
            player->game->currentEventData = std::make_unique<EventMetaData>(
                dynamic_cast<Playable*>(choiceVal->source), nullptr);
            player->GetSetasideZone()->Remove(playable);
            CastSpell(player, dynamic_cast<Spell*>(playable), nullptr, 0);
            player->game->currentEventData.reset();
            break;
        }
        case ChoiceAction::SUMMON:
        {
            if (!player->GetFieldZone()->IsFull())
            {
                player->GetSetasideZone()->Remove(playable);

                const int sourceID =
                    player->choice->source->GetGameTag(GameTag::ENTITY_ID);
                Summon(dynamic_cast<Minion*>(playable), -1,
                       player->game->entityList[sourceID]);
            }
            break;
        }
        case ChoiceAction::STACK:
        {
            player->choice->AddToStack(choice);
            break;
        }
        case ChoiceAction::ENVOY_OF_LAZUL:
        {
            for (auto& handCard : player->opponent->GetHandZone()->GetAll())
            {
                if (handCard->card->id == playable->card->id)
                {
                    player->GetSetasideZone()->Remove(playable);
                    AddCardToHand(player, playable);
                    break;
                }
            }
            break;
        }
        case ChoiceAction::SIGHTLESS_WATCHER:
        {
            const auto deckZone = player->GetDeckZone();
            deckZone->Swap(playable, deckZone->GetTopCard());

            break;
        }
        default:
            throw std::invalid_argument(
                "ChoicePick() - Invalid choice action!");
    }

    // Process after choose tasks
    if (choiceVal->source != nullptr)
    {
        auto tasks = choiceVal->source->card->power.GetAfterChooseTask();

        if (!choiceVal->entityStack.empty())
        {
            std::vector<Playable*> playables;

            for (auto& entityID : choiceVal->entityStack)
            {
                playables.emplace_back(player->game->entityList[entityID]);
            }

            player->game->taskStack.playables = playables;
        }

        for (auto& task : tasks)
        {
            std::unique_ptr<ITask> clonedTask = task->Clone();

            clonedTask->SetPlayer(player);
            clonedTask->SetSource(choiceVal->source);
            clonedTask->SetTarget(playable);

            clonedTask->Run();
        }
    }

    // It's done! - Reset choice
    delete player->choice;
    player->choice = nullptr;

    return true;
}

void CreateChoice(Player* player, ChoiceType type, ChoiceAction action,
                  const std::vector<int>& choices)
{
    // Block it if choice is exist
    if (player->choice != nullptr)
    {
        return;
    }

    // Create a choice for player
    player->choice = new Choice(player);
    player->choice->choiceType = type;
    player->choice->choiceAction = action;
    player->choice->choices = choices;
}

void CreateChoiceCards(Player* player, Entity* source, ChoiceType type,
                       ChoiceAction action, const std::vector<Card*>& choices)
{
    std::vector<int> choiceIDs;

    for (auto& card : choices)
    {
        std::map<GameTag, int> cardTags;
        cardTags.emplace(GameTag::CREATOR,
                         source->GetGameTag(GameTag::ENTITY_ID));
        cardTags.emplace(GameTag::DISPLAYED_CREATOR,
                         source->GetGameTag(GameTag::ENTITY_ID));

        Playable* choiceEntity = Entity::GetFromCard(player, card, cardTags,
                                                     player->GetSetasideZone());
        player->GetSetasideZone()->Add(choiceEntity);
        choiceIDs.emplace_back(choiceEntity->GetGameTag(GameTag::ENTITY_ID));
    }

    if (player->choice == nullptr)
    {
        player->choice = new Choice(player);
        player->choice->choiceType = type;
        player->choice->choiceAction = action;
        player->choice->source = source;
        player->choice->choices = choiceIDs;
    }
}
}  // namespace RosettaStone::Generic
