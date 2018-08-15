/*************************************************************************
> File Name: TaskSerializer.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Serializer for TaskMeta and MetaData
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#ifndef HEARTHSTONEPP_TASKSERIALIZER_H
#define HEARTHSTONEPP_TASKSERIALIZER_H

#include <Cards/Entity.h>
#include <Cards/Hero.h>
#include <Managers/Player.h>
#include <Tasks/TaskMeta.h>

#include <Flatbuffers/generated/FlatData_generated.h>

namespace Hearthstonepp::Serializer
{
using BYTE = unsigned char;

// Convert Entity to FlatData::Entity
flatbuffers::Offset<FlatData::Entity> CreateEntity(
    flatbuffers::FlatBufferBuilder& builder, const Entity* entity);

// Convert Card to FlatData::Card
flatbuffers::Offset<FlatData::Card> CreateCard(
    flatbuffers::FlatBufferBuilder& builder, const Card* card,
    const Entity* entity = nullptr);

// Convert std::vector<Entity*> to FlatData::EntityVector
TaskMeta CreateEntityVector(const TaskMetaTrait& trait,
                            const std::vector<Entity*>& vector);

// Convert std::vector<TaskMeta> to FlatData::TaskMetaVector
TaskMeta CreateTaskMetaVector(const std::vector<TaskMeta>& vector,
                              MetaData status = MetaData::INVALID,
                              BYTE userID = TaskMeta::USER_INVALID);

// Create Requirements with TaskID
TaskMeta CreateRequire(TaskID request, BYTE userID);
// Create Response for Mulligan Task
TaskMeta CreateResponseMulligan(const BYTE* index, size_t size);
// Create Response For PlayCard Task, Select Card from Hand
TaskMeta CreateResponsePlayCard(size_t cardIndex);
// Create Response for PlayMinion Task, Select position where minion will summon
TaskMeta CreateResponsePlayMinion(size_t position);
// Create response for PlaySpell task, select target type and position where
// caster will cast
TaskMeta CreateResponsePlaySpell(TargetType targetType, size_t targetPosition);
// Create Response for Targeting Tasks, eg. Combat
TaskMeta CreateResponseTarget(size_t src, size_t dst);

// Pack email of both players and set id
TaskMeta CreatePlayerSetting(const std::string& player1,
                             const std::string& player2);

// Create GameStatus TaskMeta
TaskMeta CreateGameStatus(TaskID taskID, MetaData status, const Player& player1,
                          const Player& player2);
}  // namespace Hearthstonepp::Serializer

#endif  // HEARTHSTONEPP_TASKSERIALIZER_H
