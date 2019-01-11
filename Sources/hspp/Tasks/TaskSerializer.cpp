// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <hspp/Cards/Character.hpp>
#include <hspp/Cards/Weapon.hpp>
#include <hspp/Tasks/MetaData.hpp>
#include <hspp/Tasks/TaskSerializer.hpp>

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
    return FlatData::CreateEntity(
        builder, CreateCard(builder, *entity->card, entity), 0);
}

flatbuffers::Offset<FlatData::Card> CreateCard(
    flatbuffers::FlatBufferBuilder& builder, const Card& card,
    const Entity* entity)
{
    std::vector<int> mechanics;
    mechanics.reserve(card.mechanics.size());
    for (const auto& mechanic : card.mechanics)
    {
        mechanics.emplace_back(static_cast<int>(mechanic));
    }

    std::vector<flatbuffers::Offset<FlatData::PlayRequirements>> requirements;
    requirements.reserve(card.playRequirements.size());
    for (const auto& [req, num] : card.playRequirements)
    {
        auto playReq = FlatData::CreatePlayRequirements(
            builder, static_cast<int>(req), num);
        requirements.emplace_back(playReq);
    }

    std::vector<flatbuffers::Offset<flatbuffers::String>> entourages;
    entourages.reserve(card.entourages.size());
    for (const auto& entourage : card.entourages)
    {
        entourages.emplace_back(builder.CreateString(entourage));
    }

    size_t attack = card.attack ? *card.attack : 0;
    size_t health = card.health ? *card.health : 0;
    size_t durability = card.durability ? *card.durability : 0;

    if (entity != nullptr)
    {
        if (const auto character = dynamic_cast<const Character*>(entity);
            character != nullptr)
        {
            attack = character->GetAttack();
            health = character->health;
        }
        if (const auto weapon = dynamic_cast<const Weapon*>(entity);
            weapon != nullptr)
        {
            durability = weapon->GetDurability();
        }
    }
    return FlatData::CreateCard(
        builder, builder.CreateString(card.id), static_cast<int>(card.rarity),
        static_cast<int>(card.faction), static_cast<int>(card.cardSet),
        static_cast<int>(card.cardClass), static_cast<int>(card.cardType),
        static_cast<int>(card.race), builder.CreateString(card.name),
        builder.CreateString(card.text), card.isCollectible,
        static_cast<int>(card.cost), static_cast<uint32_t>(attack),
        static_cast<uint32_t>(health), static_cast<uint32_t>(durability),
        builder.CreateVector(mechanics), builder.CreateVector(requirements),
        builder.CreateVector(entourages), card.GetMaxAllowedInDeck());
}

TaskMeta CreateEntityVector(const TaskMetaTrait& trait,
                            const std::vector<Entity*>& vector)
{
    flatbuffers::FlatBufferBuilder builder(1024);
    std::vector<flatbuffers::Offset<FlatData::Entity>> flatten;

    flatten.reserve(vector.size());
    for (const auto entity : vector)
    {
        flatten.emplace_back(CreateEntity(builder, entity));
    }

    const auto entities =
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
        auto trait = FlatData::TaskMetaTrait(
            static_cast<int>(task.GetID()),
            static_cast<status_t>(task.GetStatus()), task.GetUserID());
        const auto& unique = task.GetBuffer();
        const auto buffer =
            builder.CreateVector(unique.get(), task.GetBufferSize());

        auto temporal = FlatData::CreateTaskMeta(builder, &trait, buffer);
        flatten.emplace_back(temporal);
    }

    // Convert std::vector to FlatData::TaskMetaVector
    const auto integrated =
        FlatData::CreateTaskMetaVector(builder, builder.CreateVector(flatten));
    builder.Finish(integrated);

    return TaskMeta(TaskMetaTrait(TaskID::TASK_VECTOR, status, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateRequire(TaskID request, BYTE userID)
{
    flatbuffers::FlatBufferBuilder builder(32);
    const auto flat =
        FlatData::CreateRequireTaskMeta(builder, static_cast<int>(request));

    builder.Finish(flat);
    return TaskMeta(TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID, userID),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateResponseMulligan(const BYTE* index, size_t size)
{
    flatbuffers::FlatBufferBuilder builder(32);
    const auto vector = builder.CreateVector(index, size);
    const auto flat = FlatData::CreateResponseMulligan(builder, vector);

    builder.Finish(flat);
    return TaskMeta(TaskMetaTrait(TaskID::MULLIGAN), builder.GetSize(),
                    builder.GetBufferPointer());
}

TaskMeta CreateResponsePlayCard(size_t cardIndex)
{
    flatbuffers::FlatBufferBuilder builder(32);
    const auto flat =
        FlatData::CreateResponsePlayCard(builder, static_cast<BYTE>(cardIndex));

    builder.Finish(flat);
    return TaskMeta(TaskMetaTrait(TaskID::SELECT_CARD, MetaData::SELECT_CARD),
                    builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateResponsePlayMinion(size_t position)
{
    flatbuffers::FlatBufferBuilder builder(32);
    const auto flat = FlatData::CreateResponsePlayMinion(
        builder, static_cast<BYTE>(position));

    builder.Finish(flat);
    return TaskMeta(
        TaskMetaTrait(TaskID::SELECT_POSITION, MetaData::SELECT_POSITION),
        builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateResponsePlaySpell(EntityType type, size_t targetPosition)
{
    flatbuffers::FlatBufferBuilder builder(32);
    const auto flat = FlatData::CreateResponsePlaySpell(
        builder, static_cast<BYTE>(type), static_cast<BYTE>(targetPosition));

    builder.Finish(flat);
    return TaskMeta(
        TaskMetaTrait(TaskID::SELECT_TARGET, MetaData::SELECT_TARGET),
        builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateResponseTarget(size_t src, size_t dst)
{
    flatbuffers::FlatBufferBuilder builder(32);
    const auto flat = FlatData::CreateResponseTarget(
        builder, static_cast<BYTE>(src), static_cast<BYTE>(dst));

    builder.Finish(flat);
    return TaskMeta(
        TaskMetaTrait(TaskID::SELECT_TARGET, MetaData::SELECT_TARGET),
        builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreatePlayerSetting(const std::string& player1,
                             const std::string& player2)
{
    flatbuffers::FlatBufferBuilder builder(256);

    const auto setting = FlatData::CreatePlayerSetting(
        builder, builder.CreateString(player1), builder.CreateString(player2));

    builder.Finish(setting);
    return TaskMeta(
        TaskMetaTrait(TaskID::PLAYER_SETTING, MetaData::PLAYER_SETTING_REQUEST),
        builder.GetSize(), builder.GetBufferPointer());
}

TaskMeta CreateGameStatus(Player& player, TaskID taskID, MetaData status)
{
    using EntityOffset = flatbuffers::Offset<FlatData::Entity>;
    using VectorOffset = flatbuffers::Offset<flatbuffers::Vector<EntityOffset>>;

    flatbuffers::FlatBufferBuilder builder(256);

    const auto makeOffset = [&builder](auto&& vec) -> VectorOffset {
        std::vector<EntityOffset> dest(vec.size());
        std::transform(vec.begin(), vec.end(), dest.begin(),
                       [&builder](Entity* entity) {
                           return CreateEntity(builder, entity);
                       });
        return builder.CreateVector(dest);
    };

    // Tie multi card vector
    auto target = { player.GetField().GetAllMinions(),
                    player.GetOpponent().GetField().GetAllMinions() };
    std::vector<VectorOffset> result(target.size());

    // Convert Card vector to FlatData::Card vector
    std::transform(target.begin(), target.end(), result.begin(), makeOffset);

    const auto gameStatus = FlatData::CreateGameStatus(
        builder, player.GetID(), player.GetOpponent().GetID(),
        player.GetAvailableMana(), player.GetOpponent().GetAvailableMana(),
        CreateEntity(builder, player.GetHero()),
        CreateEntity(builder, player.GetOpponent().GetHero()), result[0],
        makeOffset(player.GetHand()), result[1],
        static_cast<BYTE>(player.GetOpponent().GetHand().size()),
        static_cast<BYTE>(player.GetDeck().size()),
        static_cast<BYTE>(player.GetOpponent().GetDeck().size()));

    builder.Finish(gameStatus);
    return TaskMeta(TaskMetaTrait(taskID, status, player.GetID()),
                    builder.GetSize(), builder.GetBufferPointer());
}
}  // namespace Hearthstonepp::Serializer
