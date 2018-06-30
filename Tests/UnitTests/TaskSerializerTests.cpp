#include "TestUtils.h"
#include "gtest/gtest.h"

#include <Cards/Cards.h>
#include <Tasks/TaskSerializer.h>

#include <random>

using namespace Hearthstonepp;

TEST(TaskSerializer, CreateAndConvertCard)
{
    std::random_device rd;
    std::default_random_engine engine(rd());
    const std::vector<Card*> cards = Cards::GetInstance()->GetAllCards();

    Card* card = cards[engine() % cards.size()];
    flatbuffers::FlatBufferBuilder builder(1024);

    auto serialized = Serializer::CreateCard(builder, card);
    builder.Finish(serialized);

    auto buffer = builder.GetBufferPointer();
    auto deserialized = flatbuffers::GetRoot<FlatData::Card>(buffer);

    std::unique_ptr<Card> converted = Serializer::ConvertCardFrom(deserialized);
    TestUtils::ExpectCardEqual(card, converted.get());
}