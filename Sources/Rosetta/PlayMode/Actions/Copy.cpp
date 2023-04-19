// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Actions/Copy.hpp>
#include <Rosetta/PlayMode/Actions/Generic.hpp>
#include <Rosetta/PlayMode/Actions/Summon.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Models/Enchantment.hpp>
#include <Rosetta/PlayMode/Zones/FieldZone.hpp>
#include <Rosetta/PlayMode/Zones/SetasideZone.hpp>

namespace RosettaStone::PlayMode::Generic
{
Playable* Copy(Player* player, Playable* source, ZoneType targetZone,
               bool deathrattle)
{
    //! \note Determine whether enchantments should be also copied.
    //! Whenever a card moves forward in that flow (Deck -> Hand, Hand -> Play,
    //! Deck -> Play), it retains enchantments. If a card moves backwards in
    //! zones (Play -> Hand, Hand -> Deck, Play -> Deck, Play/Hand/Deck ->
    //! Graveyard and Graveyard -> Play/Hand/Deck), it loses enchantments.
    //! References: https://playhearthstone.com/en-gb/blog/21965466
    bool copyEnchantments = false;
    const ZoneType sourceZone =
        (source->zone) ? source->zone->GetType() : ZoneType::PLAY;

    if ((sourceZone == ZoneType::DECK && targetZone == ZoneType::DECK) ||
        (sourceZone == ZoneType::HAND && targetZone == ZoneType::HAND) ||
        (sourceZone == ZoneType::PLAY && targetZone == ZoneType::PLAY) ||
        (sourceZone == ZoneType::DECK && targetZone == ZoneType::HAND) ||
        (sourceZone == ZoneType::HAND && targetZone == ZoneType::PLAY) ||
        (sourceZone == ZoneType::DECK && targetZone == ZoneType::PLAY))
    {
        copyEnchantments = true;
    }
    else if ((sourceZone == ZoneType::PLAY && targetZone == ZoneType::HAND) ||
             (sourceZone == ZoneType::HAND && targetZone == ZoneType::DECK) ||
             (sourceZone == ZoneType::PLAY && targetZone == ZoneType::DECK) ||
             (sourceZone == ZoneType::PLAY &&
              targetZone == ZoneType::GRAVEYARD) ||
             (sourceZone == ZoneType::HAND &&
              targetZone == ZoneType::GRAVEYARD) ||
             (sourceZone == ZoneType::DECK &&
              targetZone == ZoneType::GRAVEYARD) ||
             (sourceZone == ZoneType::GRAVEYARD &&
              targetZone == ZoneType::PLAY) ||
             (sourceZone == ZoneType::GRAVEYARD &&
              targetZone == ZoneType::HAND) ||
             (sourceZone == ZoneType::GRAVEYARD &&
              targetZone == ZoneType::DECK))
    {
        copyEnchantments = false;
    }

    Playable* copiedEntity = Entity::GetFromCard(player, source->card);

    if (copyEnchantments)
    {
        if (const auto character = dynamic_cast<Character*>(copiedEntity);
            character)
        {
            dynamic_cast<Character*>(source)->CopyInternalAttributes(character);
        }

        for (const auto& enchantment : source->appliedEnchantments)
        {
            const auto instance = Enchantment::GetInstance(
                source, enchantment->card, copiedEntity);
            const int scriptNum1 =
                enchantment->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1);
            const int scriptNum2 =
                enchantment->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2);

            if (scriptNum1 > 0)
            {
                instance->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1,
                                     scriptNum1);
            }

            if (scriptNum2 > 0)
            {
                instance->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2,
                                     scriptNum2);
            }
        }

        auto& oneTurnEffects = player->game->oneTurnEffects;
        for (int i = static_cast<int>(oneTurnEffects.size()) - 1; i >= 0; --i)
        {
            if (oneTurnEffects[i].first->GetGameTag(GameTag::ENTITY_ID) ==
                source->GetGameTag(GameTag::ENTITY_ID))
            {
                oneTurnEffects.emplace_back(
                    std::make_pair(copiedEntity, oneTurnEffects[i].second));
            }
        }
    }

    switch (targetZone)
    {
        case ZoneType::HAND:
        {
            AddCardToHand(player, copiedEntity);
            break;
        }
        case ZoneType::DECK:
        {
            ShuffleIntoDeck(player, source, copiedEntity);
            break;
        }
        case ZoneType::PLAY:
        {
            if (const auto weapon = dynamic_cast<Weapon*>(copiedEntity); weapon)
            {
                if (player->GetHero()->HasWeapon())
                {
                    player->GetWeapon().Destroy();
                }

                player->GetHero()->AddWeapon(*weapon);
            }
            else
            {
                int position = -1;

                if (deathrattle)
                {
                    position = dynamic_cast<Minion*>(source)->GetLastBoardPos();

                    if (position > player->GetFieldZone()->GetCount())
                    {
                        position = player->GetFieldZone()->GetCount();
                    }
                }

                Summon(dynamic_cast<Minion*>(copiedEntity), position, source);
            }
            break;
        }
        case ZoneType::SETASIDE:
        {
            player->GetSetasideZone()->Add(copiedEntity);
            break;
        }
        case ZoneType::INVALID:
        case ZoneType::GRAVEYARD:
        case ZoneType::REMOVEDFROMGAME:
        case ZoneType::SECRET:
            break;
    }

    if (copyEnchantments && source->ongoingEffect && copiedEntity &&
        !copiedEntity->ongoingEffect)
    {
        source->ongoingEffect->Clone(copiedEntity);
    }

    return copiedEntity;
}
}  // namespace RosettaStone::PlayMode::Generic