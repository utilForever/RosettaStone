// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_TASK_SERIALIZER_H
#define HEARTHSTONEPP_TASK_SERIALIZER_H

#include <hspp/Accounts/Player.h>
#include <hspp/Cards/Entity.h>
#include <hspp/Cards/Hero.h>
#include <hspp/Tasks/TaskMeta.h>

#include <hspp/Flatbuffers/generated/FlatData_generated.h>

namespace Hearthstonepp::Serializer
{
using BYTE = unsigned char;

//! Converts Entity object to FlatData::Entity object.
//! \param builder The builder for flatbuffers.
//! \param entity A pointer to Entity object to convert.
//! \return Converted entity object.
flatbuffers::Offset<FlatData::Entity> CreateEntity(
    flatbuffers::FlatBufferBuilder& builder, const Entity* entity);

//! Converts Card object to FlatData::Card object.
//! \param builder The builder for flatbuffers.
//! \param card A pointer to Card object to convert.
//! \param entity A pointer to Entity object to convert (nullptr as default).
//! \return Converted card object.
flatbuffers::Offset<FlatData::Card> CreateCard(
    flatbuffers::FlatBufferBuilder& builder, const Card& card,
    const Entity* entity = nullptr);

//! Converts std::vector<Entity*> to FlatData::EntityVector object.
//! \param trait A task meta data.
//! \param vector A list of pointers to Entity object.
//! \return Converted task meta object as entity vector.
TaskMeta CreateEntityVector(const TaskMetaTrait& trait,
                            const std::vector<Entity*>& vector);

//! Converts std::vector<TaskMeta> to FlatData::TaskMetaVector object.
//! \param vector A list of TaskMeta objects.
//! \param status The task status.
//! \param userID The unique user ID.
//! \return Converted task meta object as task meta vector.
TaskMeta CreateTaskMetaVector(const std::vector<TaskMeta>& vector,
                              MetaData status = MetaData::INVALID,
                              BYTE userID = TaskMeta::USER_INVALID);

//! Creates task meta object for packing require task.
//! \param request The task ID.
//! \param userID The unique user ID.
//! \return Created task meta object as require.
TaskMeta CreateRequire(TaskID request, BYTE userID);

//! Creates task meta object for packing mulligan task.
//! \param index A pointer to the start position of the array that stores the
//! card position to change.
//! \param size The number of cards to change.
//! \return Created task meta object as mulligan.
TaskMeta CreateResponseMulligan(const BYTE* index, size_t size);

//! Creates task meta object for playing card task that selects card from hand.
//! \param cardIndex The position of card to play.
//! \return Created task meta object as select card.
TaskMeta CreateResponsePlayCard(size_t cardIndex);

//! Creates task meta object for playing minion task that selects position where
//! minion will summon.
//! \param position The position of field to summon minion.
//! \return Created task meta object as select position.
TaskMeta CreateResponsePlayMinion(size_t position);

//! Creates task meta object for playing spell task that selects target type and
//! position where caster will cast.
//! \param type An entity type of the target.
//! \param targetPosition The position of field where caster will cast.
//! \return Created task meta object as select target.
TaskMeta CreateResponsePlaySpell(EntityType type, size_t targetPosition);

//! Creates task meta object for targeting task (e.g. combat).
//! \param src The position of source in field.
//! \param dst The position of target in field.
//! \return Created task meta object as select target.
TaskMeta CreateResponseTarget(size_t src, size_t dst);

//! Creates task meta object for packing two player's email.
//! \param player1 The email address of first player.
//! \param player2 The email address of second player.
//! \return Created task meta object as player setting.
TaskMeta CreatePlayerSetting(const std::string& player1,
                             const std::string& player2);

//! Creates task meta object for packing game status.
//! \param taskID The task ID.
//! \param status The task status.
//! \param player1 The first player.
//! \param player2 The second player.
//! \return Created task meta object as game status.
TaskMeta CreateGameStatus(TaskID taskID, MetaData status, const Player& player1,
                          const Player& player2);
}  // namespace Hearthstonepp::Serializer

#endif  // HEARTHSTONEPP_TASK_SERIALIZER_H
