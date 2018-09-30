// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Character.h>
#include <hspp/Cards/Weapon.h>
#include <hspp/Tasks/MetaData.h>
#include <hspp/Tasks/TaskSerializer.h>

#include <algorithm>

namespace Hearthstonepp::Serializer
{
flatbuffers::Offset<FlatData::Entity> CreateEntity(
    flatbuffers::FlatBufferBuilder& builder, const Entity* entity)
{
    if (entity == nullptr)
    {
        return FlatData::CreateEntity(builder);
    }
    return FlatData::CreateEntity(builder,
                                  CreateCard(builder, entity->card, entity), 0);
}

flatbuffers::Offset<FlatData::Card> CreateCard(
    flatbuffers::FlatBufferBuilder& builder, const Card* card,
    const Entity* entity)
{
    std::vector<int> mechanics;
    mechanics.reserve(card->mechanics.size());
    for (const auto& mechanic : card->mechanics)
    {
        mechanics.emplace_back(static_cast<int>(mechanic));
    }

    std::vector<flatbuffers::Offset<FlatData::PlayRequirements>> requirements;
    requirements.reserve(card->playRequirements.size());
    for (const auto& [req, num] : card->playRequirements)
    {
        auto playReq = FlatData::CreatePlayRequirements(
            builder, static_cast<int>(req), num);
        requirements.emplace_back(playReq);
    }

    std::vector<flatbuffers::Offset<flatbuffers::String>> entourages;
    entourages.reserve(card->entourages.size());
    for (const auto& entourage : card->entourages)
    {
        entourages.emplace_back(builder.CreateString(entourage));
    }

    size_t attack = card->attack ? *card->attack : 0;
    size_t health = card->health ? *card->health : 0;
    size_t durability = card->durability ? *card->durability : 0;

    if (entity != nullptr)
    {
        if (auto character = dynamic_cast<const Character*>(entity);
            character != nullptr)
        {
            attack = character->attack;
            health = character->health;
        }
        if (auto weapon = dynamic_cast<const Weapon*>(entity);
            weapon != nullptr)
        {
            durability = weapon->durability;
        }
    }
    return FlatData::CreateCard(
        builder, builder.CreateString(card->id), static_cast<int>(card->rarity),
        static_cast<int>(card->faction), static_cast<int>(card->cardSet),
        static_cast<int>(card->cardClass), static_cast<int>(card->cardType),
        static_cast<int>(card->race), builder.CreateString(card->name),
        builder.CreateString(card->text), card->isCollectible,
        static_cast<int>(card->cost), static_cast<uint32_t>(attack),
        static_cast<uint32_t>(health), static_cast<uint32_t>(durability),
        builder.CreateVector(mechanics), builder.CreateVector(requirements),
        builder.CreateVector(entourages), card->GetMaxAllowedInDeck());
}

TaskMeta CreateEntityVector(const TaskMetaTrait& trait,
                            const std::vector<Entity*>& vector)
{
    flatbuffers::FlatBufferBuilder builder(1024);
    std::vector<flatbuffers::Offset<FlatData::Entity>> flatten;

    for (const auto entity : vector)
    {
        flatten.emplace_back(CreateEntity(builder, entity));
    }

    auto entities =
        FlatData::CreateEntityVector(builder, builder.CreateVector(flatten));
    builder.Finish(entities);

    return TaskMeta(trait, builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateTaskMetaVector(const std::vector<TaskMeta>& vector,
                              MetaData status, BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(1024);
    std::vector<flatbuffers::Offset<FlatData::TaskMeta>> flatten;

    // Convert TaskMeta to FlatData::TaskMeta
    for (const auto& task : vector)
    {
        auto trait = FlatData::TaskMetaTrait(static_cast<int>(task.id),
                                             static_cast<status_t>(task.status),
                                             task.userID);
        const auto& unique = task.GetBuffer();
        auto buffer = builder.CreateVector(unique.get(), task.GetBufferSize());

        auto temporal = FlatData::CreateTaskMeta(builder, &trait, buffer);
        flatten.emplace_back(std::move(temporal));
    }

    // Convert std::vector to FlatData::TaskMetaVector
    auto integrated =
        FlatData::CreateTaskMetaVector(builder, builder.CreateVector(flatten));
    builder.Finish(integrated);

    return TaskMeta(TaskMetaTrait(TaskID::TASK_VECTOR, status, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateRequire(TaskID request, BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto flat =
        FlatData::CreateRequireTaskMeta(builder, static_cast<int>(request));

    builder.Finish(flat);
    return TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateResponseMulligan(const BYTE* index, size_t size)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto vector = builder.CreateVector(index, size);
    auto flat = FlatData::CreateResponseMulligan(builder, vector);

    builder.Finish(flat);
    return TaskMeta(TaskMetaTrait(TaskID::MULLIGAN), builder.GetSize(),
                    builder.GetBufferPointer());
}

TaskMeta CreateResponsePlayCard(size_t cardIndex)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto flat =
        FlatData::CreateResponsePlayCard(builder, static_cast<BYTE>(cardIndex));

    builder.Finish(flat);
    return TaskMeta(TaskMetaTrait(TaskID::SELECT_CARD, MetaData::SELECT_CARD),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateResponsePlayMinion(size_t position)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto flat = FlatData::CreateResponsePlayMinion(builder,
                                                   static_cast<BYTE>(position));

    builder.Finish(flat);
    return TaskMeta(
        TaskMetaTrait(TaskID::SELECT_POSITION, MetaData::SELECT_POSITION),
        builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateResponsePlaySpell(TargetType targetType, size_t targetPosition)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto flat = FlatData::CreateResponsePlaySpell(
        builder, static_cast<BYTE>(targetType),
        static_cast<BYTE>(targetPosition));

    builder.Finish(flat);
    return TaskMeta(
        TaskMetaTrait(TaskID::SELECT_TARGET, MetaData::SELECT_TARGET),
        builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateResponseTarget(size_t src, size_t dst)
{
    flatbuffers::FlatBufferBuilder builder(32);
    auto flat = FlatData::CreateResponseTarget(builder, static_cast<BYTE>(src),
                                               static_cast<BYTE>(dst));

    builder.Finish(flat);
    return TaskMeta(
        TaskMetaTrait(TaskID::SELECT_TARGET, MetaData::SELECT_TARGET),
        builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreatePlayerSetting(const std::string& player1,
                             const std::string& player2)
{
    flatbuffers::FlatBufferBuilder builder(256);

    auto setting = FlatData::CreatePlayerSetting(
        builder, builder.CreateString(player1), builder.CreateString(player2));

    builder.Finish(setting);
    return TaskMeta(
        TaskMetaTrait(TaskID::PLAYER_SETTING, MetaData::PLAYER_SETTING_REQUEST),
        builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateGameStatus(TaskID taskID, MetaData status, const Player& player1,
                          const Player& player2)
{
    using EntityOffset = flatbuffers::Offset<FlatData::Entity>;
    using VectorOffset = flatbuffers::Offset<flatbuffers::Vector<EntityOffset>>;

    flatbuffers::FlatBufferBuilder builder(256);

    auto makeOffset = [&builder](auto&& vec) -> VectorOffset {
        std::vector<EntityOffset> dest(vec.size());
        std::transform(vec.begin(), vec.end(), dest.begin(),
                       [&builder](Entity* entity) {
                           return CreateEntity(builder, entity);
                       });
        return builder.CreateVector(dest);
    };

    // Tie multi card vector
    auto target = { player1.field, player2.field };
    std::vector<VectorOffset> result(target.size());

    // Convert Card vector to FlatData::Card vector
    std::transform(target.begin(), target.end(), result.begin(), makeOffset);

    auto gameStatus = FlatData::CreateGameStatus(
        builder, player1.id, player2.id, player1.existMana, player2.existMana,
        CreateEntity(builder, player1.hero),
        CreateEntity(builder, player2.hero), result[0],
        makeOffset(player1.hand), result[1],
        static_cast<BYTE>(player2.hand.size()),
        static_cast<BYTE>(player1.cards.size()),
        static_cast<BYTE>(player2.cards.size()));

    builder.Finish(gameStatus);
    return TaskMeta(TaskMetaTrait(taskID, status, player1.id),
                    builder.GetSize(), builder.GetBufferPointer());
}
}  // namespace Hearthstonepp::Serializer
