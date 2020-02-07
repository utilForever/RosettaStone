// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"

#include <Rosetta/Actions/Copy.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Enums/CardEnums.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Models/Enchantment.hpp>
#include <Rosetta/Zones/DeckZone.hpp>
#include <Rosetta/Zones/FieldZone.hpp>
#include <Rosetta/Zones/GraveyardZone.hpp>
#include <Rosetta/Zones/HandZone.hpp>

using namespace RosettaStone;

TEST(Copy, Copy)
{
    GameConfig config;
    config.player1Class = CardClass::ROGUE;
    config.player2Class = CardClass::PALADIN;
    config.startPlayer = PlayerType::PLAYER1;
    config.doFillDecks = false;
    config.autoRun = false;

    Game game(config);
    game.Start();
    game.ProcessUntil(Step::MAIN_START);

    Player* curPlayer = game.GetCurrentPlayer();

    Card card;
    const std::map<GameTag, int> tags;

    // Case 1-1: Deck -> Hand
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetDeckZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, playable, ZoneType::HAND);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::HAND);

        delete playable;
    }

    // Case 1-2: Hand -> Play
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetHandZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, playable, ZoneType::PLAY);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::PLAY);

        delete playable;
    }

    // Case 1-3: Deck -> Play
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetDeckZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, playable, ZoneType::PLAY);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::PLAY);

        delete playable;
    }

    // Case 2-1: Play -> Hand
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetFieldZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, playable, ZoneType::HAND);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::HAND);

        delete playable;
    }

    // Case 2-2: Hand -> Deck
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetHandZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, playable, ZoneType::DECK);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::DECK);

        delete playable;
    }

    // Case 2-3: Play -> Deck
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetFieldZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, playable, ZoneType::DECK);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::DECK);

        delete playable;
    }

    // Case 2-4: Play -> Graveyard
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetFieldZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity =
            Generic::Copy(curPlayer, playable, ZoneType::GRAVEYARD);
        EXPECT_NE(copiedEntity->GetZoneType(), ZoneType::GRAVEYARD);

        delete playable;
    }

    // Case 2-5: Hand -> Graveyard
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetHandZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity =
            Generic::Copy(curPlayer, playable, ZoneType::GRAVEYARD);
        EXPECT_NE(copiedEntity->GetZoneType(), ZoneType::GRAVEYARD);

        delete playable;
    }

    // Case 2-6: Deck -> Graveyard
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetDeckZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity =
            Generic::Copy(curPlayer, playable, ZoneType::GRAVEYARD);
        EXPECT_NE(copiedEntity->GetZoneType(), ZoneType::GRAVEYARD);

        delete playable;
    }

    // Case 2-7: Graveyard -> Play
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetGraveyardZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, playable, ZoneType::PLAY);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::PLAY);

        delete playable;
    }

    // Case 2-8: Graveyard -> Hand
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetGraveyardZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, playable, ZoneType::HAND);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::HAND);

        delete playable;
    }

    // Case 2-9: Graveyard -> Deck
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetGraveyardZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, playable, ZoneType::DECK);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::DECK);

        delete playable;
    }

    // Case 3-1: sourceZone equals targetZone
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetHandZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, playable, ZoneType::HAND);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::HAND);

        delete playable;
    }

    // Case 3-2: targetZone is setaside
    {
        Playable* playable =
            Entity::GetFromCard(curPlayer, Cards::FindCardByName("Ysera"),
                                std::nullopt, curPlayer->GetHandZone());

        auto enchantment =
            std::make_shared<Enchantment>(curPlayer, &card, tags, playable, -1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        playable->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity =
            Generic::Copy(curPlayer, playable, ZoneType::SETASIDE);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::SETASIDE);

        delete playable;
    }
}