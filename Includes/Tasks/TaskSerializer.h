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

#include <Flatbuffers/MetaData_generated.h>
#include <Models/Card.h>
#include <Tasks/MetaData.h>
#include <Tasks/TaskMeta.h>

namespace Hearthstonepp::Serializer
{
using BYTE = unsigned char;

struct DrawTaskMeta
{
    BYTE numDraw;
    BYTE numExhausted;
    BYTE numHearts;
    BYTE numOverdraw;
    std::vector<const Card*> burnt;
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
    Card* card;
    BYTE damage;
    BYTE hurted;
    bool isExhausted;
};

struct BriefTaskMeta
{
    BriefTaskMeta(BYTE currentUser, BYTE opponentUser, BYTE currentMana,
                  BYTE opponentMana, BYTE numCurrentDeck, BYTE numOpponentDeck,
                  BYTE numOpponentHand, const std::vector<Card*>& currentHand,
                  const std::vector<Card*>& currentField,
                  const std::vector<Card*>& opponentField,
                  const std::vector<Card*>& currentAttacked,
                  const std::vector<Card*>& opponentAttacked, Card* currentHero,
                  Card* opponentHero);

    BYTE currentUser;
    BYTE opponentUser;

    BYTE currentMana;
    BYTE opponentMana;

    BYTE numCurrentDeck;
    BYTE numOpponentDeck;

    BYTE numOpponentHand;

    const std::vector<Card*>& currentHand;

    const std::vector<Card*>& currentField;
    const std::vector<Card*>& opponentField;

    const std::vector<Card*>& currentAttacked;
    const std::vector<Card*>& opponentAttacked;

    Card* currentHero;
    Card* opponentHero;
};

// Convert Card to FlatData::Card
flatbuffers::Offset<FlatData::Card> CreateCard(
    flatbuffers::FlatBufferBuilder& builder, const Card* card);

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
// From BasicTask::RawUserSetting
TaskMeta CreateUserSettingTaskMeta(const std::string& firstUserID, const std::string& secondUserID);
// From BasicTask::RawDraw
TaskMeta CreateDrawTaskMeta(const DrawTaskMeta& draw, TaskMeta::status_t status, BYTE userID);
// From BasicTask::RawModifyMana
TaskMeta CreateModifyManaTaskMeta(const ModifyManaTaskMeta& mana, TaskMeta::status_t status, BYTE userID);
// From BasicTask::RawModifyHealth
TaskMeta CreateModifyHealthTaskMeta(const ModifyHealthTaskMeta& meta, TaskMeta::status_t status, BYTE userID);
// From BasicTask::RawBrief
TaskMeta CreateBriefTaskMeta(const BriefTaskMeta& meta, TaskMeta::status_t status, BYTE userID);
// From BasicTask::RawSummonMinion
TaskMeta CreateSummonMinionTaskMeta(const TaskMetaTrait& trait, const Card* card, size_t position);
// From BasicTask::RawCombat
TaskMeta CreateCombatTaskMeta(const TaskMetaTrait& trait, const Card* src, const Card* dst);
// From BasicTask::RawGameEnd
TaskMeta CreateGameEndTaskMeta(const std::string& winner);
}  // namespace Hearthstonepp::Serializer

#endif  // HEARTHSTONEPP_TASKSERIALIZER_H
