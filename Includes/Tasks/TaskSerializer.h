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

#include <Cards/Card.h>
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
    std::vector<Card*> burnt;
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
    BriefTaskMeta(BYTE currentPlayer, BYTE opponentPlayer, BYTE currentMana,
                  BYTE opponentMana, BYTE numCurrentDeck, BYTE numOpponentDeck,
                  BYTE numOpponentHand, const std::vector<Card*>& currentHand,
                  const std::vector<Card*>& currentField,
                  const std::vector<Card*>& opponentField,
                  const std::vector<Card*>& currentAttacked,
                  const std::vector<Card*>& opponentAttacked, Card* currentHero,
                  Card* opponentHero);

    BYTE currentPlayer;
    BYTE opponentPlayer;

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
    flatbuffers::FlatBufferBuilder& builder, Card* card);

// Convert std::vector<TaskMeta> to FlatData::TaskMetaVector
TaskMeta CreateTaskMetaVector(const std::vector<TaskMeta>& vector,
                              MetaData status = MetaData::INVALID,
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
TaskMeta CreateDrawTaskMeta(const DrawTaskMeta& draw, MetaData status,
                            BYTE userID);
// From BasicTask::RawModifyMana
TaskMeta CreateModifyManaTaskMeta(const ModifyManaTaskMeta& mana,
                                  MetaData status, BYTE userID);
// From BasicTask::RawModifyHealth
TaskMeta CreateModifyHealthTaskMeta(const ModifyHealthTaskMeta& meta,
                                    MetaData status, BYTE userID);
// From BasicTask::RawBrief
TaskMeta CreateBriefTaskMeta(const BriefTaskMeta& meta, MetaData status,
                             BYTE userID);
// From BasicTask::RawSummonMinion
TaskMeta CreateSummonMinionTaskMeta(const TaskMetaTrait& trait, Card* card,
                                    size_t position);
// From BasicTask::RawCombat
TaskMeta CreateCombatTaskMeta(const TaskMetaTrait& trait, Card* src, Card* dst);
// From BasicTask::RawGameEnd
TaskMeta CreateGameEndTaskMeta(const std::string& winner);
}  // namespace Hearthstonepp::Serializer

#endif  // HEARTHSTONEPP_TASKSERIALIZER_H
