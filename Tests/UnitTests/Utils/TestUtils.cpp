// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <random>

namespace TestUtils
{
PlayerGenerator::PlayerGenerator(CardClass class1, CardClass class2)
    : account1("test1@test.com", "test1"),
      account2("test2@test.com", "test2"),
      deck1("deck1", class1),
      deck2("deck2", class2),
      player1(&account1, &deck1),
      player2(&account2, &deck2)
{
    // Do nothing
}

std::size_t GenerateRandomBuffer(std::unique_ptr<BYTE[]>& ptr,
                                 size_t maximumSize)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    // ReSharper disable once CppLocalVariableMayBeConst
    // NOTE: 'const' occurs compile error on Linux and macOS
    std::uniform_int_distribution<int> data(0, 255);

    const size_t size = gen() % maximumSize;
    ptr = std::make_unique<BYTE[]>(size);

    for (size_t i = 0; i < size; ++i)
    {
        ptr[i] = static_cast<BYTE>(data(gen));
    }

    return size;
}

TaskMetaTrait GenerateRandomTrait()
{
    std::random_device rd;
    std::default_random_engine gen(rd());

    const auto sizeTaskID = static_cast<int>(TaskID::_size());
    const auto sizeMetaData = static_cast<int>(MetaData::GAME_END);

    const TaskID taskID = TaskID::_from_integral(gen() % sizeTaskID);
    const auto metaData = static_cast<MetaData>(gen() % sizeMetaData);
    const BYTE userID = gen() % 2;

    const TaskMetaTrait randomTrait(taskID, metaData, userID);
    return randomTrait;
}

TaskMeta GenerateRandomTaskMeta()
{
    const TaskMetaTrait trait = GenerateRandomTrait();

    std::unique_ptr<BYTE[]> ptr;
    const size_t size = GenerateRandomBuffer(ptr);

    TaskMeta randomTaskMeta(trait, size, std::move(ptr));
    return randomTaskMeta;
}

Card GenerateMinionCard(std::string&& id, size_t attack, size_t health)
{
    Card card;
    card.cardType = CardType::MINION;

    card.id = std::move(id);
    card.attack = attack;
    card.health = health;

    return card;
}

Card ConvertCardFrom(const Card& card, const FlatData::Card* deserialized)
{
    Card convertedCard;

    convertedCard.id = deserialized->id()->str();
    convertedCard.rarity = Rarity::_from_integral(deserialized->rarity());
    convertedCard.faction = Faction::_from_integral(deserialized->faction());
    convertedCard.cardSet = CardSet::_from_integral(deserialized->cardSet());
    convertedCard.cardClass =
        CardClass::_from_integral(deserialized->cardClass());
    convertedCard.cardType = CardType::_from_integral(deserialized->cardType());
    convertedCard.race = Race::_from_integral(deserialized->race());
    convertedCard.name = deserialized->name()->str();
    convertedCard.text = deserialized->text()->str();
    convertedCard.isCollectible = deserialized->collectible();
    convertedCard.cost = deserialized->cost();
#ifndef HEARTHSTONEPP_MACOSX
    convertedCard.attack = card.attack
                               ? std::optional<size_t>(deserialized->attack())
                               : std::nullopt;
    convertedCard.health = card.health
                               ? std::optional<size_t>(deserialized->health())
                               : std::nullopt;
    convertedCard.durability =
        card.durability ? std::optional<size_t>(deserialized->durability())
                        : std::nullopt;
#else
    convertedCard.attack =
        card.attack
            ? std::experimental::optional<size_t>(deserialized->attack())
            : std::experimental::nullopt;
    convertedCard.health =
        card.health
            ? std::experimental::optional<size_t>(deserialized->health())
            : std::experimental::nullopt;
    convertedCard.durability =
        card.durability
            ? std::experimental::optional<size_t>(deserialized->durability())
            : std::experimental::nullopt;
#endif

    for (auto mechanic : *deserialized->mechanics())
    {
        convertedCard.mechanics.emplace_back(GameTag::_from_integral(mechanic));
    }
    for (auto req : *deserialized->playRequirements())
    {
        convertedCard.playRequirements.emplace(
            PlayReq::_from_integral(req->key_()), req->value());
    }
    for (auto entourage : *deserialized->entourages())
    {
        convertedCard.entourages.emplace_back(entourage->str());
    }
    convertedCard.maxAllowedInDeck = deserialized->maxAllowedInDeck();

    convertedCard.Initialize();

    return convertedCard;
}

void ExpectBufferEqual(const std::unique_ptr<BYTE[]>& buffer1,
                       const std::unique_ptr<BYTE[]>& buffer2, std::size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_EQ(buffer1[i], buffer2[i]);
    }
}

void ExpectCardEqual(const Card& card1, const Card& card2)
{
    EXPECT_EQ(card1.id, card2.id);
    EXPECT_EQ(card1.rarity, card2.rarity);
    EXPECT_EQ(card1.faction, card2.faction);
    EXPECT_EQ(card1.cardSet, card2.cardSet);
    EXPECT_EQ(card1.cardClass, card2.cardClass);
    EXPECT_EQ(card1.cardType, card2.cardType);
    EXPECT_EQ(card1.race, card2.race);
    EXPECT_EQ(card1.name, card2.name);
    EXPECT_EQ(card1.text, card2.text);
    EXPECT_EQ(card1.isCollectible, card2.isCollectible);
    EXPECT_EQ(card1.cost, card2.cost);
    EXPECT_EQ(card1.mechanics, card2.mechanics);
    EXPECT_EQ(card1.playRequirements, card2.playRequirements);
    EXPECT_EQ(card1.entourages, card2.entourages);
    EXPECT_EQ(card1.maxAllowedInDeck, card2.maxAllowedInDeck);

    EXPECT_EQ(card1.attack, card2.attack);
    EXPECT_EQ(card1.health, card2.health);

    EXPECT_EQ(card1.durability, card2.durability);
}
}  // namespace TestUtils
