// Copyright (c) 2017-2024 Chris Ohk

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Rosetta/Common/Utils.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Choice.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/DiscoverTask.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

namespace RosettaStone::PlayMode
{
Choice::Choice(Player* _player) : player(_player)
{
    // Do nothing
}

Choice::Choice(Player* _player, std::vector<Card*> _cardSets)
    : player(_player), cardSets(std::move(_cardSets))
{
    // Do nothing
}

void Choice::AddToStack(int entityID)
{
    entityStack.emplace_back(entityID);
}

void Choice::TryPrepare()
{
    if (cardSets.empty())
    {
        return;
    }

    if (choiceAction == ChoiceAction::SWAMPQUEEN_HAGATHA)
    {
        const Playable* playable = player->game->entityList[lastChoice];
        bool isTargetingCard = false;

        for (const auto& playReq : playable->card->playRequirements)
        {
            if (playReq.first == PlayReq::REQ_TARGET_TO_PLAY ||
                playReq.first == PlayReq::REQ_TARGET_IF_AVAILABLE)
            {
                isTargetingCard = true;
                break;
            }
        }

        if (isTargetingCard)
        {
            std::vector<Card*> cards;

            for (auto& card : cardSets)
            {
                if (card->GetCardType() != CardType::SPELL ||
                    card->GetCardClass() != CardClass::SHAMAN)
                {
                    continue;
                }

                bool isValid = true;

                for (const auto& playReq : card->playRequirements)
                {
                    if (playReq.first == PlayReq::REQ_TARGET_TO_PLAY ||
                        playReq.first == PlayReq::REQ_TARGET_IF_AVAILABLE)
                    {
                        isValid = false;
                        break;
                    }
                }

                if (isValid)
                {
                    cards.emplace_back(card);
                }
            }

            cardSets = cards;
        }
    }
    else if (choiceAction == ChoiceAction::SIAMAT)
    {
        const Playable* effect = player->game->entityList[lastChoice];

        EraseIf(cardSets,
                [=](const Card* card) { return effect->card->id == card->id; });
    }

    choices = SimpleTasks::DiscoverTask::GetChoices(source, cardSets,
                                                    std::vector<int>{}, 3);
}

Choice* Choice::TryPopNextChoice(const int _lastChoice) const
{
    if (nextChoice)
    {
        nextChoice->lastChoice = _lastChoice;
        nextChoice->TryPrepare();
        nextChoice->entityStack = entityStack;
    }

    return nextChoice;
}
}  // namespace RosettaStone::PlayMode