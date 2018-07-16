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
#include <Tasks/TaskMeta.h>

#include <Flatbuffers/generated/MetaData_generated.h>

namespace Hearthstonepp::Serializer
{
using BYTE = unsigned char;

struct DrawTaskMeta
{
    BYTE numDraw;
    BYTE numExhausted;
    BYTE numHearts;
    BYTE numOverdraw;
    std::vector<Entity*> burnt;
};

struct ModifyManaTaskMeta
{
    BYTE numMode;
    BYTE manaMode;
    BYTE object;
    BYTE result;
};

struct ModifyHealthTaskMeta
{
    Entity* card;
    BYTE damage;
    BYTE hurted;
    bool isExhausted;
};

struct BriefTaskMeta
{
    BriefTaskMeta(BYTE currentPlayer, BYTE opponentPlayer, BYTE currentMana,
                  BYTE opponentMana, BYTE numCurrentDeck, BYTE numOpponentDeck,
                  BYTE numOpponentHand, const std::vector<Entity*>& currentHand,
                  const std::vector<Character*>& currentField,
                  const std::vector<Character*>& opponentField,
                  const std::vector<Character*>& currentAttacked,
                  const std::vector<Character*>& opponentAttacked,
                  Hero* currentHero, Hero* opponentHero);

    BYTE currentPlayer;
    BYTE opponentPlayer;

    BYTE currentMana;
    BYTE opponentMana;

    BYTE numCurrentDeck;
    BYTE numOpponentDeck;

    BYTE numOpponentHand;

    const std::vector<Entity*>& currentHand;

    const std::vector<Character*>& currentField;
    const std::vector<Character*>& opponentField;

    const std::vector<Character*>& currentAttacked;
    const std::vector<Character*>& opponentAttacked;

    Hero* currentHero;
    Hero* opponentHero;
};

// Convert Entity to FlatData::Entity
flatbuffers::Offset<FlatData::Entity> CreateEntity(
    flatbuffers::FlatBufferBuilder& builder, Entity* entity);

// Convert Card to FlatData::Card
flatbuffers::Offset<FlatData::Card> CreateCard(
    flatbuffers::FlatBufferBuilder& builder, Card* card);

// Convert std::vector<TaskMeta> to FlatData::TaskMetaVector
TaskMeta CreateTaskMetaVector(
    const std::vector<TaskMeta>& vector,
    TaskMeta::status_t status = TaskMeta::STATUS_INVALID,
    BYTE userID = TaskMeta::USER_INVALID);

// From BasicTask::RequireMethod
TaskMeta CreateRequireTaskMeta(TaskID request, BYTE userID);
// From BasicTask::RawMulligan
TaskMeta CreateRequireMulliganTaskMeta(const BYTE* index, size_t size);
// From GameInterface::InputSelectCard
TaskMeta CreateRequireSummonMinionTaskMeta(int cardIndex, int position);
// From GameInterface::InputTargeting
TaskMeta CreateRequireTargetingTaskMeta(int src, int dst);
// From BasicTask::RawPlayerSetting
TaskMeta CreatePlayerSettingTaskMeta(const std::string& firstPlayerID,
                                     const std::string& secondPlayerID);
// From BasicTask::RawDraw
TaskMeta CreateDrawTaskMeta(const DrawTaskMeta& draw, TaskMeta::status_t status,
                            BYTE userID);
// From BasicTask::RawModifyMana
TaskMeta CreateModifyManaTaskMeta(const ModifyManaTaskMeta& mana,
                                  TaskMeta::status_t status, BYTE userID);
// From BasicTask::RawModifyHealth
TaskMeta CreateModifyHealthTaskMeta(const ModifyHealthTaskMeta& meta,
                                    TaskMeta::status_t status, BYTE userID);
// From BasicTask::RawBrief
TaskMeta CreateBriefTaskMeta(const BriefTaskMeta& meta,
                             TaskMeta::status_t status, BYTE userID);
// From BasicTask::RawSummonMinion
TaskMeta CreateSummonMinionTaskMeta(const TaskMetaTrait& trait, Entity* card,
                                    size_t position);
// From BasicTask::RawCombat
TaskMeta CreateCombatTaskMeta(const TaskMetaTrait& trait, Entity* src,
                              Entity* dst);
// From BasicTask::RawGameEnd
TaskMeta CreateGameEndTaskMeta(const std::string& winner);
}  // namespace Hearthstonepp::Serializer

#endif  // HEARTHSTONEPP_TASKSERIALIZER_H
