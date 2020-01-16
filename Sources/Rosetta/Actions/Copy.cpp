// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#include <Rosetta/Actions/Copy.hpp>
#include <Rosetta/Actions/Generic.hpp>
#include <Rosetta/Actions/Summon.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/SetasideZone.hpp>

namespace RosettaStone::Generic
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
    bool copyEnchantments;
    const ZoneType sourceZone =
        (source->zone) ? source->zone->GetType() : ZoneType::PLAY;

    if (sourceZone == ZoneType::GRAVEYARD)
    {
        copyEnchantments = false;
    }
    else if (sourceZone == targetZone)
    {
        copyEnchantments = true;
    }
    else if (targetZone == ZoneType::SETASIDE)
    {
        copyEnchantments = false;
    }
    else if (targetZone == ZoneType::PLAY)
    {
        copyEnchantments = true;
    }
    else if (sourceZone == ZoneType::DECK)
    {
        copyEnchantments = true;
    }
    else if (sourceZone == ZoneType::HAND && targetZone != ZoneType::DECK)
    {
        copyEnchantments = true;
    }
    else
    {
        copyEnchantments = false;
    }

    Playable* copiedEntity = Entity::GetFromCard(player, source->card);

    if (copyEnchantments)
    {
        if (!source->appliedEnchantments.empty())
        {
            for (auto& e : source->appliedEnchantments)
            {
                auto instance =
                    Enchantment::GetInstance(player, e->card, copiedEntity);
                if (e->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1) > 0)
                {
                    instance->SetGameTag(
                        GameTag::TAG_SCRIPT_DATA_NUM_1,
                        e->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1));

                    if (e->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2) > 0)
                    {
                        instance->SetGameTag(
                            GameTag::TAG_SCRIPT_DATA_NUM_2,
                            e->GetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2));
                    }
                }
            }
        }

        auto& oneTurnEffects = player->game->oneTurnEffects;
        for (int i = static_cast<int>(oneTurnEffects.size()) - 1; i >= 0; --i)
        {
            if (oneTurnEffects[i].first->id == source->id)
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
            ShuffleIntoDeck(player, copiedEntity);
            break;
        }
        case ZoneType::PLAY:
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
            break;
        }
        case ZoneType::SETASIDE:
        {
            player->GetSetasideZone()->Add(copiedEntity);
            break;
        }
        default:
            break;
    }

    if (copyEnchantments && source->ongoingEffect != nullptr &&
        copiedEntity->ongoingEffect == nullptr)
    {
        source->ongoingEffect->Clone(copiedEntity);
    }

    return copiedEntity;
}
}  // namespace RosettaStone::Generic