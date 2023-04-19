// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/CastSpell.hpp>
#include <Rosetta/PlayMode/Actions/Choose.hpp>
#include <Rosetta/PlayMode/Actions/Copy.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Cards/Cards.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/ITask.hpp>
#include <Rosetta/PlayMode/Zones/DeckZone.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

#include <effolkronium/random.hpp>

#include <algorithm>

using Random = effolkronium::random_static;

namespace RosettaStone::PlayMode::Generic
{
void ChoiceMulligan(Player* player, const std::vector<int>& choices)
{
    Choice* choice = player->choice;
    if (!choice)
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
    if (choice->choiceAction == ChoiceAction::HAND)
    {
        // Process mulligan state
        player->mulliganState = Mulligan::DEALING;

        const auto hand = player->GetHandZone();
        const auto deck = player->GetDeckZone();

        // Process redraw
        for (const auto& entityID : choices)
        {
            Playable* entity = player->game->entityList[entityID];
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
    }
}

bool ChoicePick(Player* player, int choice)
{
    Choice* choiceVal = player->choice;
    if (!choiceVal)
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
    if (!playable)
    {
        return false;
    }

    // Process pick by choice action
    switch (choiceVal->choiceAction)
    {
        case ChoiceAction::INVALID:
            throw std::invalid_argument(
                "ChoicePick() - Invalid choice action!");
        case ChoiceAction::CHANGE_HERO_POWER:
        {
            delete player->GetHero()->heroPower;
            player->GetSetasideZone()->Remove(playable);
            playable->SetGameTag(GameTag::ZONE,
                                 static_cast<int>(ZoneType::PLAY));
            player->GetHero()->heroPower = dynamic_cast<HeroPower*>(playable);
            break;
        }
        case ChoiceAction::HAND:
        {
            player->GetSetasideZone()->Remove(playable);
            AddCardToHand(player, playable);
            break;
        }
        case ChoiceAction::HAND_COPY:
        {
            Copy(player, playable, ZoneType::HAND);
            break;
        }
        case ChoiceAction::HAND_AND_STACK:
        {
            player->GetSetasideZone()->Remove(playable);
            AddCardToHand(player, playable);
            player->choice->AddToStack(choice);
            break;
        }
        case ChoiceAction::DECK:
        {
            player->GetSetasideZone()->Remove(playable);
            ShuffleIntoDeck(player, choiceVal->source, playable);
            break;
        }
        case ChoiceAction::ENCHANTMENT:
        {
            player->game->taskStack.num[0] = choice;
            break;
        }
        case ChoiceAction::DRAW_FROM_DECK:
        {
            player->GetDeckZone()->Remove(playable);
            AddCardToHand(player, playable);
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
        case ChoiceAction::DREDGE:
        {
            const auto deckZone = player->GetDeckZone();
            deckZone->Add(deckZone->Remove(playable));
            break;
        }
        case ChoiceAction::STACK:
        {
            player->choice->AddToStack(choice);
            break;
        }
        case ChoiceAction::ENVOY_OF_LAZUL:
        {
            for (const auto& handCard :
                 player->opponent->GetHandZone()->GetAll())
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
        case ChoiceAction::MADAME_LAZUL:
        {
            Copy(player, playable, ZoneType::HAND);
            break;
        }
        case ChoiceAction::SWAMPQUEEN_HAGATHA:
        {
            if (choiceVal->depth == 1)
            {
                choiceVal->source->SetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1,
                                              playable->card->dbfID);
            }
            else
            {
                choiceVal->source->SetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2,
                                              playable->card->dbfID);
            }
            break;
        }
        case ChoiceAction::TORTOLLAN_PILGRIM:
        {
            player->GetDeckZone()->Remove(playable);

            const auto spellToCast = dynamic_cast<Spell*>(playable);
            if (!spellToCast)
            {
                throw std::logic_error(
                    "Tortollan Pilgram casts non-spell card!");
            }

            const auto randTarget = spellToCast->GetRandomValidTarget();
            const int randChooseOne = Random::get<int>(1, 2);

            const auto choiceTemp = player->choice;
            player->choice = nullptr;

            player->game->taskQueue.StartEvent();
            CastSpell(player, spellToCast, randTarget, randChooseOne);
            player->game->ProcessDestroyAndUpdateAura();
            player->game->taskQueue.EndEvent();

            while (player->choice)
            {
                const auto idx = Random::get<std::size_t>(
                    0, player->choice->choices.size() - 1);

                player->game->taskQueue.StartEvent();
                ChoicePick(player, player->choice->choices[idx]);
                player->game->ProcessTasks();
                player->game->taskQueue.EndEvent();
                player->game->ProcessDestroyAndUpdateAura();
            }

            player->choice = choiceTemp;

            break;
        }
        case ChoiceAction::SIAMAT:
        {
            if (choiceVal->depth == 1)
            {
                choiceVal->source->SetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_1,
                                              playable->card->dbfID);
            }
            else
            {
                choiceVal->source->SetGameTag(GameTag::TAG_SCRIPT_DATA_ENT_2,
                                              playable->card->dbfID);
            }
            break;
        }
        case ChoiceAction::VULPERA_SCOUNDREL:
        {
            if (playable->card->id == "ULD_209t")
            {
                std::vector<Card*> allCards = Cards::GetDiscoverCards(
                    player->baseClass, player->game->GetFormatType());

                std::vector<Card*> spellCards;
                for (auto& card : allCards)
                {
                    if (card->GetCardType() == CardType::SPELL)
                    {
                        spellCards.emplace_back(card);
                    }
                }

                const auto idx =
                    Random::get<std::size_t>(0, spellCards.size() - 1);

                Playable* spell = Entity::GetFromCard(player, spellCards[idx]);
                AddCardToHand(player, spell);
                playable = spell;
            }
            else
            {
                player->GetSetasideZone()->Remove(playable);
                AddCardToHand(player, playable);
            }
            break;
        }
    }

    Choice* nextChoice = choiceVal->TryPopNextChoice(choice);
    if (!nextChoice)
    {
        // Process after choose tasks
        if (choiceVal->source)
        {
            const auto card = choiceVal->source->card;
            const auto tasks =
                player->IsComboActive() && card->HasGameTag(GameTag::COMBO)
                    ? card->power.GetAfterChooseForComboTask()
                    : card->power.GetAfterChooseTask();

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
                const std::unique_ptr<ITask> clonedTask = task->Clone();

                clonedTask->SetPlayer(player);
                clonedTask->SetSource(choiceVal->source);
                clonedTask->SetTarget(playable);

                clonedTask->Run();
            }

            // Set combo active to true
            if (!player->IsComboActive())
            {
                player->SetComboActive(true);
            }
        }

        // NOTE: Temporary code for 'Dwarven Archaeologist' (ULD_309)
        // TODO: We'll refactor it later using Coroutines in C++20
        if (const Entity* source = choiceVal->source;
            source && source->GetGameTag(GameTag::DISCOVER) == 1)
        {
            player->game->taskStack.num[0] =
                playable->GetGameTag(GameTag::ENTITY_ID);

            // Validate play card trigger
            Trigger::ValidateTriggers(player->game, choiceVal->source,
                                      SequenceType::PLAY_CARD);

            // Process after play card trigger
            player->game->taskQueue.StartEvent();
            player->game->triggerManager.OnAfterPlayCardTrigger(
                choiceVal->source);
            player->game->ProcessTasks();
            player->game->taskQueue.EndEvent();
            player->game->ProcessDestroyAndUpdateAura();
        }

        // It's done! - Reset choice
        delete player->choice;
        player->choice = nullptr;
    }
    else
    {
        player->choice = nextChoice;
    }

    return true;
}

void CreateChoice(Player* player, Entity* source, ChoiceType type,
                  ChoiceAction action, const std::vector<int>& choices)
{
    // Block it if choice is exist
    if (player->choice)
    {
        return;
    }

    // Create a choice for player
    player->choice = new Choice(player);
    player->choice->choiceType = type;
    player->choice->choiceAction = action;
    player->choice->source = source;
    player->choice->choices = choices;
    player->choice->depth = 1;
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

    if (!player->choice)
    {
        player->choice = new Choice(player);
        player->choice->choiceType = type;
        player->choice->choiceAction = action;
        player->choice->source = source;
        player->choice->choices = choiceIDs;
        player->choice->depth = 1;
    }
}
}  // namespace RosettaStone::PlayMode::Generic
