#include "TestUtils.h"
#include "gtest/gtest.h"

#include <Cards/Cards.h>
#include <Cards/Minion.h>
#include <Enchants/Enchant.h>
#include <Tasks/TaskSerializer.h>
#include <cards/Weapon.h>

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