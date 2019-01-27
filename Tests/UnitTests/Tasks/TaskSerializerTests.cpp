// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Utils/TestUtils.hpp>
#include "gtest/gtest.h"

#include <hspp/Accounts/Player.hpp>
#include <hspp/Cards/Cards.hpp>
#include <hspp/Cards/Minion.hpp>
#include <hspp/Cards/Weapon.hpp>
#include <hspp/Managers/GameAgent.hpp>
#include <hspp/Tasks/TaskSerializer.hpp>
#include <hspp/Tasks/Tasks.hpp>

#include <random>

using namespace Hearthstonepp;
using namespace TestUtils;

TEST(TaskSerializer, CreateCard)
{
    std::random_device rd;
    std::default_random_engine engine(rd());

    Cards& instance = Cards::GetInstance();
    const std::vector<Card>& allCards = instance.GetAllCards();

    const auto cardTest = [](const Card& card) {
        flatbuffers::FlatBufferBuilder builder(1024);

        const auto serialized = Serializer::CreateCard(builder, card);
        builder.Finish(serialized);

        const auto buffer = builder.GetBufferPointer();
        const auto deserialized = flatbuffers::GetRoot<FlatData::Card>(buffer);
        const auto converted = ConvertCardFrom(card, deserialized);
        ExpectCardEqual(card, converted);
    };

    // Rogue minion: Nerubian
    const auto nerubian = instance.FindCardByID("AT_036t");
    EXPECT_NE(nerubian.id, "");
    EXPECT_EQ(nerubian.name, "Nerubian");
    cardTest(nerubian);

    // Rogue weapon: Poisoned Blade
    const auto poisonedBlade = instance.FindCardByID("AT_034");
    EXPECT_NE(poisonedBlade.id, "");
    EXPECT_EQ(poisonedBlade.name, "Poisoned Blade");
    cardTest(poisonedBlade);

    // Warlock minion: Dreadsteed
    const auto dreadsteed = instance.FindCardByID("AT_019e");
    EXPECT_NE(dreadsteed.id, "");
    EXPECT_EQ(dreadsteed.name, "Dreadsteed");
    cardTest(dreadsteed);

    const Card randomCard = allCards[engine() % allCards.size()];
    cardTest(randomCard);
}

TEST(TaskSerializer, CreateEntity)
{
    const auto autoEncode = [](const Entity* entity) {
        flatbuffers::FlatBufferBuilder builder(1024);

        const auto serialized = Serializer::CreateEntity(builder, entity);
        builder.Finish(serialized);

        const auto ptr = builder.GetBufferPointer();
        auto buffer = std::make_unique<BYTE[]>(builder.GetSize());
        std::copy(ptr, ptr + builder.GetSize(), buffer.get());

        return buffer;
    };

    Cards& instance = Cards::GetInstance();

    // Rogue Minion : Nerubian
    auto nerubian = instance.FindCardByID("AT_036t");
    EXPECT_NE(nerubian.id, "");
    EXPECT_EQ(nerubian.name, "Nerubian");

    auto minionNerubian = new Minion(nullptr, nerubian);
    minionNerubian->health = 100;
    minionNerubian->SetAttack(1000);

    auto buffer = autoEncode(minionNerubian);
    auto minion = flatbuffers::GetRoot<FlatData::Entity>(buffer.get());
    EXPECT_EQ(minion->card()->id()->str(), nerubian.id);
    EXPECT_EQ(minion->card()->health(), static_cast<size_t>(100));
    EXPECT_EQ(minion->card()->attack(), static_cast<size_t>(1000));
    EXPECT_EQ(minion->card()->durability(), static_cast<size_t>(0));

    // Rogue Weapon : Poisoned Blade
    Card poisonedBlade = instance.FindCardByID("AT_034");
    EXPECT_NE(poisonedBlade.id, "");
    EXPECT_EQ(poisonedBlade.name, "Poisoned Blade");

    auto weaponPoisonBlade = new Weapon(nullptr, poisonedBlade);
    weaponPoisonBlade->SetDurability(500);

    buffer = autoEncode(weaponPoisonBlade);
    auto weapon = flatbuffers::GetRoot<FlatData::Entity>(buffer.get());
    EXPECT_EQ(weapon->card()->id()->str(), poisonedBlade.id);
    EXPECT_EQ(weapon->card()->health(), static_cast<size_t>(0));
    EXPECT_EQ(weapon->card()->attack(), static_cast<size_t>(1));
    EXPECT_EQ(weapon->card()->durability(), static_cast<size_t>(500));

    delete minionNerubian;
    delete weaponPoisonBlade;
}

TEST(TaskSerializer, CreateEntityVector)
{
    Cards& instance = Cards::GetInstance();
    const TaskMetaTrait randTrait = GenerateRandomTrait();

    auto nerubian = instance.FindCardByID("AT_036t");
    const auto minionNerubian = new Minion(nullptr, nerubian);

    auto poisonedBlade = instance.FindCardByID("AT_034");
    const auto weaponPoisonedBlade = new Weapon(nullptr, poisonedBlade);

    const std::vector<Entity*> entities = { minionNerubian,
                                            weaponPoisonedBlade };
    TaskMeta entityVector = Serializer::CreateEntityVector(randTrait, entities);

    EXPECT_EQ(entityVector.GetID(), randTrait.GetID());
    EXPECT_EQ(entityVector.GetUserID(), randTrait.GetUserID());
    EXPECT_EQ(entityVector.GetStatus(), randTrait.GetStatus());

    auto vector =
        TaskMeta::ConvertTo<FlatData::EntityVector>(entityVector)->vector();
    EXPECT_EQ(vector->size(), static_cast<size_t>(2));

    const auto deserializedNerubian =
        ConvertCardFrom(nerubian, vector->Get(0)->card());
    ExpectCardEqual(nerubian, deserializedNerubian);

    const auto deserializedPoisonedBlade =
        ConvertCardFrom(poisonedBlade, vector->Get(1)->card());
    ExpectCardEqual(poisonedBlade, deserializedPoisonedBlade);

    delete minionNerubian;
    delete weaponPoisonedBlade;
}

TEST(TaskSerializer, CreateTaskMetaVector)
{
    constexpr size_t testSize = 10;

    std::vector<TaskMeta> metas;
    metas.reserve(testSize);

    for (size_t i = 0; i < testSize; ++i)
    {
        metas.emplace_back(GenerateRandomTrait());
    }

    const TaskMetaTrait random = GenerateRandomTrait();
    TaskMeta generated = Serializer::CreateTaskMetaVector(
        metas, random.GetStatus(), random.GetUserID());

    EXPECT_EQ(generated.GetID(), +TaskID::TASK_VECTOR);
    EXPECT_EQ(generated.GetStatus(), random.GetStatus());
    EXPECT_EQ(generated.GetUserID(), random.GetUserID());

    const auto taskVector =
        TaskMeta::ConvertTo<FlatData::TaskMetaVector>(generated);
    auto vector = taskVector->vector();
    EXPECT_EQ(vector->Length(), testSize);

    for (size_t i = 0; i < testSize; ++i)
    {
        const auto idx = static_cast<flatbuffers::uoffset_t>(i);
        TaskMeta converted = TaskMeta::ConvertFrom(vector->Get(idx));

        EXPECT_EQ(metas[i], converted);
    }
}

TEST(TaskSerializer, CreateRequireTaskMeta)
{
    const TaskMetaTrait random = GenerateRandomTrait();
    TaskMeta required =
        Serializer::CreateRequire(random.GetID(), random.GetUserID());

    EXPECT_EQ(required.GetID(), +TaskID::REQUIRE);
    EXPECT_EQ(required.GetStatus(), MetaData::INVALID);
    EXPECT_EQ(required.GetUserID(), random.GetUserID());

    const auto meta = TaskMeta::ConvertTo<FlatData::RequireTaskMeta>(required);
    TaskID requiredID = TaskID::_from_integral(meta->required());
    EXPECT_EQ(requiredID, random.GetID());
}

TEST(TaskSerializer, CreateResponseMulligan)
{
    BYTE mulligan[] = { 1, 2, 3 };
    TaskMeta resp = Serializer::CreateResponseMulligan(mulligan, 3);

    auto data = TaskMeta::ConvertTo<FlatData::ResponseMulligan>(resp);
    EXPECT_EQ(resp.GetID(), +TaskID::MULLIGAN);
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
    EXPECT_EQ(resp.GetID(), +TaskID::SELECT_CARD);
    EXPECT_EQ(data->cardIndex(), static_cast<size_t>(10));
}

TEST(TaskSerializer, CreateResponsePlayMinion)
{
    TaskMeta resp = Serializer::CreateResponsePlayMinion(10);
    auto data = TaskMeta::ConvertTo<FlatData::ResponsePlayMinion>(resp);
    EXPECT_EQ(resp.GetID(), +TaskID::SELECT_POSITION);
    EXPECT_EQ(data->position(), static_cast<size_t>(10));
}

TEST(TaskSerializer, CreateResponsePlaySpell)
{
    TaskMeta resp =
        Serializer::CreateResponsePlaySpell(EntityType::ENEMY_FIELD, 10);
    auto data = TaskMeta::ConvertTo<FlatData::ResponsePlaySpell>(resp);
    EXPECT_EQ(resp.GetID(), +TaskID::SELECT_TARGET);
    EXPECT_EQ(data->position(), 10);
    EXPECT_EQ(EntityType::_from_integral(data->targetType()),
              +EntityType::ENEMY_FIELD);
}

TEST(TaskSerializer, CreateResponseTarget)
{
    TaskMeta resp = Serializer::CreateResponseTarget(10, 50);
    auto data = TaskMeta::ConvertTo<FlatData::ResponseTarget>(resp);
    EXPECT_EQ(resp.GetID(), +TaskID::SELECT_TARGET);
    EXPECT_EQ(data->src(), static_cast<size_t>(10));
    EXPECT_EQ(data->dst(), static_cast<size_t>(50));
}

TEST(TaskSerializer, CreatePlayerSetting)
{
    const std::string player1 = "player1";
    const std::string player2 = "player2";

    TaskMeta resp = Serializer::CreatePlayerSetting(player1, player2);
    auto data = TaskMeta::ConvertTo<FlatData::PlayerSetting>(resp);

    EXPECT_EQ(resp.GetID(), +TaskID::PLAYER_SETTING);
    EXPECT_EQ(data->player1()->str(), player1);
    EXPECT_EQ(data->player2()->str(), player2);
}

TEST(TaskSerializer, CreateGameStatus)
{
    GameAgent agent(CardClass::DRUID, CardClass::ROGUE, PlayerType::PLAYER1);
    const TaskMetaTrait randTrait = GenerateRandomTrait();

    agent.GetPlayer1().SetID(100);
    agent.GetPlayer2().SetID(200);

    agent.GetPlayer1().SetAvailableMana(10);
    agent.GetPlayer2().SetAvailableMana(20);

    Cards& instance = Cards::GetInstance();

    // Summon 'Nerubian' card to field (minion)
    Card nerubian = instance.FindCardByID("AT_036t");
    
    Minion minion1(&agent, nerubian);
    Minion minion2(&agent, nerubian);
    
    agent.GetPlayer1().GetField().AddMinion(minion1, 0);
    agent.GetPlayer2().GetField().AddMinion(minion2, 0);

    // Draw 'Poisoned Blade' card (weapon)
    Card poisonedBlade = instance.FindCardByID("AT_034");

    Weapon weapon1(&agent, poisonedBlade);
    Weapon weapon2(&agent, poisonedBlade);

    agent.GetPlayer1().GetHand().AddCard(weapon1);
    agent.GetPlayer2().GetHand().AddCard(weapon2);

    TaskMeta meta = Serializer::CreateGameStatus(
        agent.GetPlayer1(), randTrait.GetID(), randTrait.GetStatus());
    EXPECT_EQ(meta.GetID(), randTrait.GetID());
    EXPECT_EQ(meta.GetStatus(), randTrait.GetStatus());
    EXPECT_EQ(meta.GetUserID(), agent.GetPlayer1().GetID());

    auto status = TaskMeta::ConvertTo<FlatData::GameStatus>(meta);
    EXPECT_EQ(status->currentPlayer(), agent.GetPlayer1().GetID());
    EXPECT_EQ(status->opponentPlayer(), agent.GetPlayer2().GetID());
    EXPECT_EQ(status->currentMana(), agent.GetPlayer1().GetAvailableMana());
    EXPECT_EQ(status->opponentMana(), agent.GetPlayer2().GetAvailableMana());
    EXPECT_EQ(status->currentHero()->card()->id()->str(), "HERO_06");
    EXPECT_EQ(status->opponentHero()->card()->id()->str(), "HERO_03");
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
