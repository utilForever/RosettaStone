#include "TestUtils.h"
#include "gtest/gtest.h"

#include <Cards/Cards.h>
#include <Cards/Minion.h>
#include <Cards/Weapon.h>
#include <Enchants/Enchant.h>
#include <Syncs/Player.h>
#include <Tasks/TaskSerializer.h>
#include <Tasks/Tasks.h>

#include <random>

using namespace Hearthstonepp;

TEST(TaskSerializer, CreateAndConvertCard)
{
    std::random_device rd;
    std::default_random_engine engine(rd());

    Cards* cards = Cards::GetInstance();
    const std::vector<Card*> allCards = cards->GetAllCards();

    auto cardTest = [](Card* card) {
        flatbuffers::FlatBufferBuilder builder(1024);

        auto serialized = Serializer::CreateCard(builder, card);
        builder.Finish(serialized);

        auto buffer = builder.GetBufferPointer();
        auto deserialized = flatbuffers::GetRoot<FlatData::Card>(buffer);

        std::unique_ptr<Card> converted =
            Serializer::ConvertCardFrom(deserialized);
        TestUtils::ExpectCardEqual(card, converted.get());
    };

    constexpr size_t zero = 0;

    // Rogue Minion : Nerubian
    const Card* nerubian = cards->FindCardByID("AT_036t");
    EXPECT_EQ(nerubian->name, "Nerubian");

    const auto* minionNerubian = dynamic_cast<const Minion*>(nerubian);
    EXPECT_NE(minionNerubian, nullptr);

    Minion copiedNerubian = *minionNerubian;
    cardTest(&copiedNerubian);

    // Rogue Weapon : Poisoned Blade
    const Card* poisonedBlade = cards->FindCardByID("AT_034");
    EXPECT_EQ(poisonedBlade->name, "Poisoned Blade");

    const Weapon* weaponPoisonedBlade =
        dynamic_cast<const Weapon*>(poisonedBlade);
    EXPECT_NE(weaponPoisonedBlade, nullptr);

    Weapon copiedPoisonedBlade = *weaponPoisonedBlade;
    cardTest(&copiedPoisonedBlade);

    const Card* dreadsteed = cards->FindCardByID("AT_019e");
    EXPECT_EQ(dreadsteed->name, "Dreadsteed");

    const auto* enchantmentDreadsteed =
        dynamic_cast<const Enchantment*>(dreadsteed);
    EXPECT_NE(enchantmentDreadsteed, nullptr);

    Enchantment copiedDreadsteed = *enchantmentDreadsteed;
    cardTest(&copiedDreadsteed);

    Card* randomCard = allCards[engine() % allCards.size()];
    cardTest(randomCard);
}

TEST(TaskSerializer, CreateTaskMetaVector)
{
    constexpr size_t testSize = 10;

    std::vector<TaskMeta> metas;
    metas.reserve(testSize);

    for (size_t i = 0; i < testSize; ++i)
    {
        metas.emplace_back(TestUtils::GenerateRandomTrait());
    }

    TaskMetaTrait random = TestUtils::GenerateRandomTrait();
    TaskMeta generated = Serializer::CreateTaskMetaVector(metas, random.status, random.userID);

    EXPECT_EQ(generated.id, +TaskID::TASK_TUPLE);
    EXPECT_EQ(generated.status, random.status);
    EXPECT_EQ(generated.userID, random.userID);

    const auto& buffer = generated.GetConstBuffer();
    auto taskTuple = flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());

    auto vector = taskTuple->vector();
    EXPECT_EQ(vector->Length(), testSize);

    for (size_t i = 0; i < testSize; ++i)
    {
        auto idx = static_cast<flatbuffers::uoffset_t>(i);
        TaskMeta converted = TaskMeta::ConvertFrom(vector->Get(idx));

        EXPECT_EQ(metas[i], converted);
    }
}

TEST(TaskSerializer, CreateRequireTaskMeta)
{
    TaskMetaTrait random = TestUtils::GenerateRandomTrait();

    TaskMeta required = Serializer::CreateRequireTaskMeta(random.id, random.userID);

    EXPECT_EQ(required.id, +TaskID::REQUIRE);
    EXPECT_EQ(required.status, MetaData::INVALID);
    EXPECT_EQ(required.userID, random.userID);

    const auto& buffer = required.GetConstBuffer();
    auto meta = flatbuffers::GetRoot<FlatData::RequireTaskMeta>(buffer.get());

    TaskID requiredID = TaskID::_from_integral(meta->required());
    EXPECT_EQ(requiredID, random.id);
}