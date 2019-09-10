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

    Player& curPlayer = game.GetCurrentPlayer();

    Card card;
    const std::map<GameTag, int> tags;

    // Case 1-1: Deck -> Hand
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetDeckZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, entity, ZoneType::HAND);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::HAND);

        delete enchantment;
        delete entity;
    }

    // Case 1-2: Hand -> Play
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetHandZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, entity, ZoneType::PLAY);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::PLAY);

        delete entity;
        delete enchantment;
    }

    // Case 1-3: Deck -> Play
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetDeckZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, entity, ZoneType::PLAY);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::PLAY);

        delete entity;
        delete enchantment;
    }

    // Case 2-1: Play -> Hand
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetFieldZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, entity, ZoneType::HAND);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::HAND);

        delete entity;
        delete enchantment;
    }

    // Case 2-2: Hand -> Deck
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetHandZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, entity, ZoneType::DECK);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::DECK);

        delete entity;
        delete enchantment;
    }

    // Case 2-3: Play -> Deck
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetFieldZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, entity, ZoneType::DECK);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::DECK);

        delete entity;
        delete enchantment;
    }

    // Case 2-4: Play -> Graveyard
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetFieldZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity =
            Generic::Copy(curPlayer, entity, ZoneType::GRAVEYARD);
        EXPECT_NE(copiedEntity->GetZoneType(), ZoneType::GRAVEYARD);

        delete entity;
        delete enchantment;
    }

    // Case 2-5: Hand -> Graveyard
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetHandZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity =
            Generic::Copy(curPlayer, entity, ZoneType::GRAVEYARD);
        EXPECT_NE(copiedEntity->GetZoneType(), ZoneType::GRAVEYARD);

        delete entity;
        delete enchantment;
    }

    // Case 2-6: Deck -> Graveyard
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetDeckZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity =
            Generic::Copy(curPlayer, entity, ZoneType::GRAVEYARD);
        EXPECT_NE(copiedEntity->GetZoneType(), ZoneType::GRAVEYARD);

        delete entity;
        delete enchantment;
    }

    // Case 2-7: Graveyard -> Play
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetGraveyardZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, entity, ZoneType::PLAY);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::PLAY);

        delete entity;
        delete enchantment;
    }

    // Case 2-8: Graveyard -> Hand
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetGraveyardZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, entity, ZoneType::HAND);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::HAND);

        delete entity;
        delete enchantment;
    }

    // Case 2-9: Graveyard -> Deck
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetGraveyardZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, entity, ZoneType::DECK);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::DECK);

        delete entity;
        delete enchantment;
    }

    // Case 3-1: sourceZone equals targetZone
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetHandZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity = Generic::Copy(curPlayer, entity, ZoneType::HAND);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::HAND);

        delete entity;
        delete enchantment;
    }

    // Case 3-2: targetZone is setaside
    {
        Entity* entity = Entity::GetFromCard(
            curPlayer, Cards::GetInstance().FindCardByName("Ysera"),
            std::nullopt, &curPlayer.GetHandZone());

        Enchantment* enchantment =
            new Enchantment(curPlayer, &card, tags, entity);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_1, 1);
        enchantment->SetGameTag(GameTag::TAG_SCRIPT_DATA_NUM_2, 2);

        entity->appliedEnchantments.emplace_back(enchantment);

        auto copiedEntity =
            Generic::Copy(curPlayer, entity, ZoneType::SETASIDE);
        EXPECT_EQ(copiedEntity->GetZoneType(), ZoneType::SETASIDE);

        delete entity;
        delete enchantment;
    }
}