#include "TestUtils.h"
#include "gtest/gtest.h"

#include <Cards/Cards.h>
#include <Cards/Minion.h>
#include <cards/Weapon.h>
#include <Tasks/TaskSerializer.h>

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

        std::unique_ptr<Card> converted = Serializer::ConvertCardFrom(deserialized);
        TestUtils::ExpectCardEqual(card, converted.get());
    };

    constexpr size_t zero = 0;

    // Rogue Minion : Nerubian
    const Card* nerubian = cards->FindCardByID("AT_036t");
    EXPECT_EQ(nerubian->name, "Nerubian");

    const auto * minionNerubian = dynamic_cast<const Minion*>(nerubian);
    EXPECT_NE(minionNerubian, nullptr);
    EXPECT_EQ(nerubian->name, "Nerubian");
    EXPECT_EQ(minionNerubian->cardType, +CardType::MINION);
    EXPECT_NE(minionNerubian->attack, zero);
    EXPECT_NE(minionNerubian->health, zero);

    Minion copiedNerubian = *minionNerubian;
    cardTest(&copiedNerubian);

    // Rogue Weapon : Poisoned Blade
    const Card* poisonedBlade = cards->FindCardByID("AT_034");
    const Weapon* weaponPoisonedBlade = dynamic_cast<const Weapon*>(poisonedBlade);
    EXPECT_NE(weaponPoisonedBlade, nullptr);
    EXPECT_EQ(weaponPoisonedBlade->cardType, +CardType::WEAPON);

    Weapon copiedPoisonedBlade = *weaponPoisonedBlade;
    cardTest(&copiedPoisonedBlade);

    Card* randomCard = allCards[engine() % allCards.size()];
    cardTest(randomCard);
}