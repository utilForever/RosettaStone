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

namespace Hearthstonepp
{
    namespace Serializer
    {
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
            BriefTaskMeta(BYTE currentUser, BYTE opponentUser, BYTE currentMana, BYTE opponentMana, BYTE numOpponentHand,
                          const std::vector<Card*>& currentHand, const std::vector<Card*>& currentField,
                          const std::vector<Card*>& opponentField, const std::vector<Card*>& currentAttacked,
                          const std::vector<Card*>& opponentAttacked, Card* currentHero, Card* opponentHero);

            BYTE currentUser;
            BYTE opponentUser;

            BYTE currentMana;
            BYTE opponentMana;

            BYTE numOpponentHand;

            const std::vector<Card*>& currentHand;

            const std::vector<Card*>& currentField;
            const std::vector<Card*>& opponentField;

            const std::vector<Card*>& currentAttacked;
            const std::vector<Card*>& opponentAttacked;

            Card* currentHero;
            Card* opponentHero;
        };

        flatbuffers::Offset<FlatData::Card> CreateCard(flatbuffers::FlatBufferBuilder& builder, const Card* card);

        TaskMeta CreateTaskMetaVector(const std::vector<TaskMeta>& vector);
        TaskMeta CreateRequireTaskMeta(TaskID request, BYTE userID);
        TaskMeta CreateRequireMulliganTaskMeta(const BYTE* index, size_t size);
        TaskMeta CreateRequireSummonMinionTaskMeta(int cardIndex, int position);
        TaskMeta CreateRequireTargetingTaskMeta(int src, int dst);
        TaskMeta CreateUserSettingTaskMeta(const std::string& firstUserID, const std::string& secondUserID);
        TaskMeta CreateDrawTaskMeta(const DrawTaskMeta& draw, TaskMeta::status_t status, BYTE userID);
        TaskMeta CreateModifyManaTaskMeta(const ModifyManaTaskMeta& mana, TaskMeta::status_t status, BYTE userID);
        TaskMeta CreateModifyHealthTaskMeta(const ModifyHealthTaskMeta& meta, TaskMeta::status_t status, BYTE userID);
        TaskMeta CreateBriefTaskMeta(const BriefTaskMeta& meta, TaskMeta::status_t status, BYTE userID);
        TaskMeta CreateSummonMinionTaskMeta(const TaskMetaTrait& trait, const Card* card, size_t position);
        TaskMeta CreateCombatTaskMeta(const TaskMetaTrait& trait, const Card* src, const Card* dst);
        TaskMeta CreateGameEndTaskMeta(const std::string& winner);
    }
}

#endif //HEARTHSTONEPP_TASKSERIALIZER_H
