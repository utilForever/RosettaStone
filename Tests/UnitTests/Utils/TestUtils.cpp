// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

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
    // Do Nothing
}

std::size_t GenerateRandomBuffer(std::unique_ptr<BYTE[]>& ptr,
                                 size_t maximumSize)
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> data(0, 255);

    size_t size = gen() % maximumSize;
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

    int sizeTaskID = static_cast<int>(TaskID::_size());
    int sizeMetaData = static_cast<int>(MetaData::GAME_END);

    TaskID taskID = TaskID::_from_integral(gen() % sizeTaskID);
    MetaData metaData = static_cast<MetaData>(gen() % sizeMetaData);
    BYTE userID = gen() % 2;

    TaskMetaTrait randomTrait(taskID, metaData, userID);
    return randomTrait;
}

TaskMeta GenerateRandomTaskMeta()
{
    TaskMetaTrait trait = GenerateRandomTrait();

    std::unique_ptr<BYTE[]> ptr;
    size_t size = GenerateRandomBuffer(ptr);

    TaskMeta randomTaskMeta(trait, size, std::move(ptr));
    return randomTaskMeta;
}

std::unique_ptr<Card> ConvertCardFrom(const Card& card,
                                      const FlatData::Card* deserialized)
{
    auto converted = std::make_unique<Card>();

    converted->id = deserialized->id()->str();
    converted->rarity = Rarity::_from_integral(deserialized->rarity());
    converted->faction = Faction::_from_integral(deserialized->faction());
    converted->cardSet = CardSet::_from_integral(deserialized->cardSet());
    converted->cardClass = CardClass::_from_integral(deserialized->cardClass());
    converted->cardType = CardType::_from_integral(deserialized->cardType());
    converted->race = Race::_from_integral(deserialized->race());
    converted->name = deserialized->name()->str();
    converted->text = deserialized->text()->str();
    converted->isCollectible = deserialized->collectible();
    converted->cost = deserialized->cost();
#ifndef HEARTHSTONEPP_MACOSX
    converted->attack = card.attack
                            ? std::optional<size_t>(deserialized->attack())
                            : std::nullopt;
    converted->health = card.health
                            ? std::optional<size_t>(deserialized->health())
                            : std::nullopt;
    converted->durability =
        card.durability ? std::optional<size_t>(deserialized->durability())
                         : std::nullopt;
#else
    converted->attack =
        card.attack
            ? std::experimental::optional<size_t>(deserialized->attack())
            : std::experimental::nullopt;
    converted->health =
        card.health
            ? std::experimental::optional<size_t>(deserialized->health())
            : std::experimental::nullopt;
    converted->durability =
        card.durability
            ? std::experimental::optional<size_t>(deserialized->durability())
            : std::experimental::nullopt;
#endif

    for (auto mechanic : *deserialized->mechanics())
    {
        converted->mechanics.emplace_back(GameTag::_from_integral(mechanic));
    }
    for (auto req : *deserialized->playRequirements())
    {
        converted->playRequirements.emplace(
            PlayReq::_from_integral(req->key_()), req->value());
    }
    for (auto entourage : *deserialized->entourages())
    {
        converted->entourages.emplace_back(entourage->str());
    }
    converted->maxAllowedInDeck = deserialized->maxAllowedInDeck();
    converted->Initialize();

    return converted;
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
