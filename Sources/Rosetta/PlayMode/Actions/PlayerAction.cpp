// Copyright (c) 2026 Chris Ohk

#include <Rosetta/PlayMode/Actions/PlayCard.hpp>
#include <Rosetta/PlayMode/Actions/PlayerAction.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/PlayerTasks/HeroPowerTask.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/HandZone.hpp>

#include <algorithm>

namespace RosettaStone::PlayMode
{
std::vector<PlayerAction> EnumerateActions(const Game& game)
{
    std::vector<PlayerAction> actions;

    if (game.state != State::RUNNING || game.step != Step::MAIN_ACTION ||
        !game.taskQueue.IsIdle() || !game.deadMinions.empty() ||
        !game.rebornMinions.empty() || !game.summonedMinions.empty())
    {
        return actions;
    }

    const auto* player = game.GetCurrentPlayer();

    if (player->opponent->choice)
    {
        return actions;
    }

    if (player->choice)
    {
        if (player->choice->choiceType == ChoiceType::GENERAL)
        {
            for (const int id : player->choice->choices)
            {
                actions.push_back(
                    { PlayerActionType::CHOOSE, -1, -1, -1, 0, id });
            }
        }
    }
    else
    {
        actions.push_back({ PlayerActionType::END_TURN });

        // Choose One options may target differently from their parent card.
        std::vector<Character*> targets{ nullptr, player->GetHero(),
                                         player->opponent->GetHero() };

        for (auto* owner :
             { player, static_cast<const Player*>(player->opponent) })
        {
            for (auto* character : owner->GetFieldZone()->GetAll())
            {
                targets.push_back(character);
            }
        }

        for (auto* source : player->GetHandZone()->GetAll())
        {
            const bool choose = source->HasChooseOne() && !player->ChooseBoth();
            const int lastChoice =
                choose ? static_cast<int>(source->card->chooseCardIDs.size())
                       : 0;
            const auto type = source->card->GetCardType();
            const bool onBoard =
                type == CardType::MINION || type == CardType::LOCATION;

            for (int choice = choose ? 1 : 0; choice <= lastChoice; ++choice)
            {
                for (auto* target : targets)
                {
                    if (!Generic::CanPlayCard(source, target, choice))
                    {
                        continue;
                    }

                    const int lastPosition =
                        onBoard ? player->GetFieldZone()->GetCount() : -1;

                    for (int position = onBoard ? 0 : -1;
                         position <= lastPosition; ++position)
                    {
                        actions.push_back(
                            { PlayerActionType::PLAY_CARD,
                              source->GetGameTag(GameTag::ENTITY_ID),
                              target ? target->GetGameTag(GameTag::ENTITY_ID)
                                     : -1,
                              position, choice });
                    }
                }
            }
        }

        for (auto* source : targets)
        {
            if (!source || source->player != player || !source->CanAttack())
            {
                continue;
            }

            for (auto* target : source->GetValidAttackTargets(player->opponent))
            {
                if (source->IsValidAttackTarget(player->opponent, target))
                {
                    actions.push_back(
                        { PlayerActionType::ATTACK,
                          source->GetGameTag(GameTag::ENTITY_ID),
                          target->GetGameTag(GameTag::ENTITY_ID) });
                }
            }
        }

        using PlayerTasks::HeroPowerTask;

        for (auto* target : targets)
        {
            if (HeroPowerTask::ResolveTarget(player, target) == target &&
                HeroPowerTask::CanPlay(player, target))
            {
                actions.push_back(
                    { PlayerActionType::HERO_POWER,
                      player->GetHeroPower().GetGameTag(GameTag::ENTITY_ID),
                      target ? target->GetGameTag(GameTag::ENTITY_ID) : -1 });
            }
        }
    }

    std::ranges::sort(actions);
    actions.erase(std::unique(actions.begin(), actions.end()), actions.end());

    return actions;
}
}  // namespace RosettaStone::PlayMode
