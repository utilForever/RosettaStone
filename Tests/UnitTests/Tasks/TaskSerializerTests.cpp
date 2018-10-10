// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include "gtest/gtest.h"
#include <Utils/TestUtils.h>

#include <hspp/Accounts/Player.h>
#include <hspp/Cards/Cards.h>
#include <hspp/Cards/Minion.h>
#include <hspp/Cards/Weapon.h>
#include <hspp/Enchants/Enchant.h>
#include <hspp/Tasks/TaskSerializer.h>
#include <hspp/Tasks/Tasks.h>

#include <random>

using namespace Hearthstonepp;

TEST(TaskSerializer, CreateCard)
{
    std::random_device rd;
    std::default_random_engine engine(rd());

    Cards* cards = Cards::GetInstance();
    const std::vector<Card*>& allCards = cards->GetAllCards();

    auto cardTest = [](const Card* card) {
        flatbuffers::FlatBufferBuilder builder(1024);

        auto serialized = Serializer::CreateCard(builder, card);
        builder.Finish(serialized);

        auto buffer = builder.GetBufferPointer();
        auto deserialized = flatbuffers::GetRoot<FlatData::Card>(buffer);
        auto converted = TestUtils::ConvertCardFrom(card, deserialized);
        TestUtils::ExpectCardEqual(card, converted.get());
    };

    constexpr size_t zero = 0;

    // Rogue Minion : Nerubian
    const Card* nerubian = cards->FindCardByID("AT_036t");
    EXPECT_NE(nerubian, static_cast<const Card*>(nullptr));
    EXPECT_EQ(nerubian->name, "Nerubian");
    cardTest(nerubian);

    // Rogue Weapon : Poisoned Blade
    const Card* poisonedBlade = cards->FindCardByID("AT_034");
    EXPECT_NE(poisonedBlade, static_cast<const Card*>(nullptr));
    EXPECT_EQ(poisonedBlade->name, "Poisoned Blade");
    cardTest(poisonedBlade);

    // Enchantment
    const Card* dreadsteed = cards->FindCardByID("AT_019e");
    EXPECT_NE(dreadsteed, static_cast<const Card*>(nullptr));
    EXPECT_EQ(dreadsteed->name, "Dreadsteed");
    cardTest(dreadsteed);

    const Card* randomCard = allCards[engine() % allCards.size()];
    cardTest(randomCard);
}

TEST(TaskSerializer, CreateEntity)
{
    auto autoEncode = [](const Entity* entity) {
        flatbuffers::FlatBufferBuilder builder(1024);

        auto serialized = Serializer::CreateEntity(builder, entity);
        builder.Finish(serialized);

        auto ptr = builder.GetBufferPointer();
        auto buffer = std::make_unique<BYTE[]>(builder.GetSize());
        std::copy(ptr, ptr + builder.GetSize(), buffer.get());

        return buffer;
    };

    Cards* cards = Cards::GetInstance();

    // Rogue Minion : Nerubian
    const Card* nerubian = cards->FindCardByID("AT_036t");
    EXPECT_NE(nerubian, static_cast<const Card*>(nullptr));
    EXPECT_EQ(nerubian->name, "Nerubian");

    Minion mNerubian(nerubian);
    mNerubian.health = 100;
    mNerubian.attack = 1000;

    auto buffer = autoEncode(&mNerubian);
    auto minion = flatbuffers::GetRoot<FlatData::Entity>(buffer.get());
    EXPECT_EQ(minion->card()->id()->str(), nerubian->id);
    EXPECT_EQ(minion->card()->health(), static_cast<size_t>(100));
    EXPECT_EQ(minion->card()->attack(), static_cast<size_t>(1000));
    EXPECT_EQ(minion->card()->durability(), static_cast<size_t>(0));

    // Rogue Weapon : Poisoned Blade
    const Card* poisonedBlade = cards->FindCardByID("AT_034");
    EXPECT_NE(poisonedBlade, static_cast<const Card*>(nullptr));
    EXPECT_EQ(poisonedBlade->name, "Poisoned Blade");

    Weapon wPoisonedBlade(poisonedBlade);
    wPoisonedBlade.durability = 500;

    buffer = autoEncode(&wPoisonedBlade);
    auto weapon = flatbuffers::GetRoot<FlatData::Entity>(buffer.get());
    EXPECT_EQ(weapon->card()->id()->str(), poisonedBlade->id);
    EXPECT_EQ(weapon->card()->health(), static_cast<size_t>(0));
    EXPECT_EQ(weapon->card()->attack(), static_cast<size_t>(1));
    EXPECT_EQ(weapon->card()->durability(), static_cast<size_t>(500));
}

TEST(TaskSerializer, CreateEntityVector)
{
    Cards* cards = Cards::GetInstance();
    TaskMetaTrait randTrait = TestUtils::GenerateRandomTrait();

    const Card* nerubian = cards->FindCardByID("AT_036t");
    Minion mNerubian(nerubian);

    const Card* poisonedBlade = cards->FindCardByID("AT_034");
    Weapon wPoisonedBlade(poisonedBlade);

    std::vector<Entity*> entities = {&mNerubian, &wPoisonedBlade};
    TaskMeta entityVector = Serializer::CreateEntityVector(randTrait, entities);

    EXPECT_EQ(entityVector.id, randTrait.id);
    EXPECT_EQ(entityVector.userID, randTrait.userID);
    EXPECT_EQ(entityVector.status, randTrait.status);

    auto vector =
        TaskMeta::ConvertTo<FlatData::EntityVector>(entityVector)->vector();
    EXPECT_EQ(vector->size(), static_cast<size_t>(2));

    auto deNerubian =
        TestUtils::ConvertCardFrom(nerubian, vector->Get(0)->card());
    TestUtils::ExpectCardEqual(nerubian, deNerubian.get());

    auto dePoisonedBlade =
        TestUtils::ConvertCardFrom(poisonedBlade, vector->Get(1)->card());
    TestUtils::ExpectCardEqual(poisonedBlade, dePoisonedBlade.get());
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
    TaskMeta generated =
        Serializer::CreateTaskMetaVector(metas, random.status, random.userID);

    EXPECT_EQ(generated.id, +TaskID::TASK_VECTOR);
    EXPECT_EQ(generated.status, random.status);
    EXPECT_EQ(generated.userID, random.userID);

    auto taskVector = TaskMeta::ConvertTo<FlatData::TaskMetaVector>(generated);
    auto vector = taskVector->vector();
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
    TaskMeta required = Serializer::CreateRequire(random.id, random.userID);

    EXPECT_EQ(required.id, +TaskID::REQUIRE);
    EXPECT_EQ(required.status, MetaData::INVALID);
    EXPECT_EQ(required.userID, random.userID);

    auto meta = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(required);
    TaskID requiredID = TaskID::_from_integral(meta->required());
    EXPECT_EQ(requiredID, random.id);
}

TEST(TaskSerializer, CreateResponseMulligan)
{
    BYTE mulligan[] = {1, 2, 3};
    TaskMeta resp = Serializer::CreateResponseMulligan(mulligan, 3);

    auto data = TaskMeta::ConvertTo<FlatData::ResponseMulligan>(resp);
    EXPECT_EQ(resp.id, +TaskID::MULLIGAN);
    EXPECT_EQ(data->mulligan()->size(), static_cast<size_t>(3));

    size_t i = 0;
    for (auto choice : *data->mulligan())
    {
        EXPECT_EQ(mulligan[i++], choice);
    }
}

TEST(TaskSerializer, CreateResponsePlayCard)
{
    TaskMeta resp = Serializer::CreateResponsePlayCard(10);

    auto data = TaskMeta::ConvertTo<FlatData::ResponsePlayCard>(resp);
    EXPECT_EQ(resp.id, +TaskID::SELECT_CARD);
    EXPECT_EQ(data->cardIndex(), static_cast<size_t>(10));
}

TEST(TaskSerializer, CreateResponsePlayMinion)
{
    TaskMeta resp = Serializer::CreateResponsePlayMinion(10);
    auto data = TaskMeta::ConvertTo<FlatData::ResponsePlayMinion>(resp);
    EXPECT_EQ(resp.id, +TaskID::SELECT_POSITION);
    EXPECT_EQ(data->position(), static_cast<size_t>(10));
}

TEST(TaskSerializer, CreateResponsePlaySpell)
{
    TaskMeta resp =
        Serializer::CreateResponsePlaySpell(TargetType::OPPONENT_FIELD, 10);
    auto data = TaskMeta::ConvertTo<FlatData::ResponsePlaySpell>(resp);
    EXPECT_EQ(resp.id, +TaskID::SELECT_TARGET);
    EXPECT_EQ(data->position(), 10);
    EXPECT_EQ(TargetType::_from_integral(data->targetType()),
              +TargetType::OPPONENT_FIELD);
}

TEST(TaskSerializer, CreateResponseTarget)
{
    TaskMeta resp = Serializer::CreateResponseTarget(10, 50);
    auto data = TaskMeta::ConvertTo<FlatData::ResponseTarget>(resp);
    EXPECT_EQ(resp.id, +TaskID::SELECT_TARGET);
    EXPECT_EQ(data->src(), static_cast<size_t>(10));
    EXPECT_EQ(data->dst(), static_cast<size_t>(50));
}

TEST(TaskSerializer, CreatePlayerSetting)
{
    std::string player1 = "player1";
    std::string player2 = "player2";

    TaskMeta resp = Serializer::CreatePlayerSetting(player1, player2);
    auto data = TaskMeta::ConvertTo<FlatData::PlayerSetting>(resp);

    EXPECT_EQ(resp.id, +TaskID::PLAYER_SETTING);
    EXPECT_EQ(data->player1()->str(), player1);
    EXPECT_EQ(data->player2()->str(), player2);
}

TEST(TaskSerializer, CreateGameStatus)
{
    TaskMetaTrait randTrait = TestUtils::GenerateRandomTrait();

    Account account1("email1", "name1");
    Account account2("email2", "name2");
    Deck deck1("deck1", CardClass::DRUID);
    Deck deck2("deck2", CardClass::PALADIN);

    Player player1(&account1, &deck1);
    Player player2(&account2, &deck2);

    player1.id = 100;
    player2.id = 200;

    player1.existMana = 10;
    player2.existMana = 20;

    Cards* cards = Cards::GetInstance();

    // Summons 'Nerubian' card to field (minion)
    player1.field.emplace_back(new Minion(cards->FindCardByID("AT_036t")));
    player2.field.emplace_back(new Minion(cards->FindCardByID("AT_036t")));

    // Draws 'Poisoned Blade' card (weapon)
    player1.hand.emplace_back(new Weapon(cards->FindCardByID("AT_034")));
    player2.hand.emplace_back(new Weapon(cards->FindCardByID("AT_034")));

    TaskMeta meta = Serializer::CreateGameStatus(randTrait.id, randTrait.status,
                                                 player1, player2);
    EXPECT_EQ(meta.id, randTrait.id);
    EXPECT_EQ(meta.status, randTrait.status);
    EXPECT_EQ(meta.userID, player1.id);

    auto status = TaskMeta::ConvertTo<FlatData::GameStatus>(meta);
    EXPECT_EQ(status->currentPlayer(), player1.id);
    EXPECT_EQ(status->opponentPlayer(), player2.id);
    EXPECT_EQ(status->currentMana(), player1.existMana);
    EXPECT_EQ(status->opponentMana(), player2.existMana);
    EXPECT_EQ(status->currentHero()->card()->id()->str(), "HERO_06");
    EXPECT_EQ(status->opponentHero()->card()->id()->str(), "HERO_04");
    EXPECT_EQ(status->currentField()->size(), static_cast<size_t>(1));
    EXPECT_EQ(status->currentField()->Get(0)->card()->id()->str(), "AT_036t");
    EXPECT_EQ(status->opponentField()->size(), static_cast<size_t>(1));
    EXPECT_EQ(status->opponentField()->Get(0)->card()->id()->str(), "AT_036t");
    EXPECT_EQ(status->currentHand()->size(), static_cast<size_t>(1));
    EXPECT_EQ(status->currentHand()->Get(0)->card()->id()->str(), "AT_034");
    EXPECT_EQ(status->numOpponentHand(), static_cast<size_t>(1));
    EXPECT_EQ(status->numCurrentDeck(), static_cast<size_t>(0));
    EXPECT_EQ(status->numOpponentDeck(), static_cast<size_t>(0));
}
