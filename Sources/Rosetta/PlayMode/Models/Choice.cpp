// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

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
        auto playable = player->game->entityList[lastChoice];
        bool isTargetingCard = false;

        for (auto& playReq : playable->card->playRequirements)
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
                for (auto& playReq : card->playRequirements)
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

    auto cards = SimpleTasks::DiscoverTask::GetChoices(cardSets, 3);

    std::vector<int> choiceCards;
    choiceCards.reserve(3);

    for (auto& card : cards)
    {
        const auto playable = Entity::GetFromCard(player, card, std::nullopt,
                                                  player->GetSetasideZone());
        choiceCards.emplace_back(playable->GetGameTag(GameTag::ENTITY_ID));
    }

    choices = choiceCards;
}

Choice* Choice::TryPopNextChoice(int lastChoice)
{
    if (nextChoice == nullptr)
    {
        return nullptr;
    }

    nextChoice->lastChoice = lastChoice;
    nextChoice->TryPrepare();
    nextChoice->entityStack = entityStack;

    return nextChoice;
}
}  // namespace RosettaStone::PlayMode