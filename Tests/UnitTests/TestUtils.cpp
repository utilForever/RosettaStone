//#include "TestUtils.h"
//#include "gtest/gtest.h"
//
//#include <Cards/Cards.h>
//#include <Cards/Character.h>
//#include <Cards/Weapon.h>
//
//using namespace Hearthstonepp;
//
//namespace TestUtils
//{
//size_t GenerateRandomBuffer(std::unique_ptr<BYTE[]>& ptr)
//{
//    std::random_device rd;
//    std::default_random_engine gen(rd());
//    std::uniform_int_distribution<int> data(0, 255);
//
//    size_t size = data(gen);
//    ptr = std::make_unique<BYTE[]>(size);
//    for (size_t i = 0; i < size; ++i)
//    {
//        ptr[i] = static_cast<BYTE>(data(gen));
//    }
//
//    return size;
//}
//
//TaskMetaTrait GenerateRandomTrait()
//{
//    std::random_device rd;
//    std::default_random_engine gen(rd());
//
//    int sizeTaskID = static_cast<int>(TaskID::_size());
//    int sizeMetaData = static_cast<int>(MetaData::GAME_END);
//
//    TaskID taskID = TaskID::_from_integral(gen() % sizeTaskID);
//    MetaData metaData = static_cast<MetaData>(gen() % sizeMetaData);
//    BYTE userID = gen() % 2;
//
//    TaskMetaTrait randomTrait(taskID, metaData, userID);
//    return randomTrait;
//}
//
//TaskMeta GenerateRandomTaskMeta()
//{
//    TaskMetaTrait trait = GenerateRandomTrait();
//
//    std::unique_ptr<BYTE[]> ptr;
//    size_t size = GenerateRandomBuffer(ptr);
//
//    TaskMeta randomTaskMeta(trait, size, std::move(ptr));
//    return randomTaskMeta;
//}
//
//void ExpectBufferEqual(const std::unique_ptr<BYTE[]>& buffer1,
//                       const std::unique_ptr<BYTE[]>& buffer2, size_t size)
//{
//    for (size_t i = 0; i < size; ++i)
//    {
//        EXPECT_EQ(buffer1[i], buffer2[i]);
//    }
//}
//
//void ExpectCardEqual(const Card* card1, const Card* card2)
//{
//    EXPECT_EQ(card1->id, card2->id);
//    EXPECT_EQ(card1->rarity, card2->rarity);
//    EXPECT_EQ(card1->faction, card2->faction);
//    EXPECT_EQ(card1->cardSet, card2->cardSet);
//    EXPECT_EQ(card1->cardClass, card2->cardClass);
//    EXPECT_EQ(card1->cardType, card2->cardType);
//    EXPECT_EQ(card1->race, card2->race);
//    EXPECT_EQ(card1->name, card2->name);
//    EXPECT_EQ(card1->text, card2->text);
//    EXPECT_EQ(card1->isCollectible, card2->isCollectible);
//    EXPECT_EQ(card1->cost, card2->cost);
//    EXPECT_EQ(card1->mechanics, card2->mechanics);
//    EXPECT_EQ(card1->maxAllowedInDeck, card2->maxAllowedInDeck);
//
//    auto character1 = dynamic_cast<const Character*>(card1);
//    auto character2 = dynamic_cast<const Character*>(card2);
//    if (character1 != nullptr || character2 != nullptr)
//    {
//        EXPECT_NE(character1, nullptr);
//        EXPECT_NE(character2, nullptr);
//
//        EXPECT_EQ(character1->attack, character2->attack);
//        EXPECT_EQ(character1->health, character2->health);
//    }
//
//    auto weapon1 = dynamic_cast<const Weapon*>(card1);
//    auto weapon2 = dynamic_cast<const Weapon*>(card2);
//    if (weapon1 != nullptr || weapon2 != nullptr)
//    {
//        EXPECT_NE(weapon1, nullptr);
//        EXPECT_NE(weapon2, nullptr);
//
//        EXPECT_EQ(weapon1->durability, weapon2->durability);
//    }
//}
//}  // namespace TestUtils