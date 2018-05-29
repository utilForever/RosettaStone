/*************************************************************************
> File Name: TaskSerializer.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Serializer for TaskMeta and MetaData
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/TaskSerializer.h>
#include <Tasks/MetaData.h>

#include <algorithm>

namespace Hearthstonepp
{
    namespace Serializer
    {
        using fb = flatbuffers;

        BriefTaskMeta::BriefTaskMeta(BYTE currentUser, BYTE opponentUser,
                                     BYTE currentMana, BYTE opponentMana, BYTE numOpponentHand,
                                     const std::vector<Card *> &currentHand,
                                     const std::vector<Card *> &currentField,
                                     const std::vector<Card *> &opponentField,
                                     const std::vector<Card *> &currentAttacked,
                                     const std::vector<Card *> &opponentAttacked,
                                     Card *currentHero, Card *opponentHero) :
                currentUser(currentUser), opponentUser(opponentUser),
                currentMana(currentMana), opponentMana(opponentMana), numOpponentHand(numOpponentHand),
                currentHand(currentHand), currentField(currentField), opponentField(opponentField),
                currentAttacked(currentAttacked), opponentAttacked(opponentAttacked),
                currentHero(currentHero), opponentHero(opponentHero)
        {
            // Do Nothing
        }

        fb::Offset<FlatData::Card> CreateCard(fb::FlatBufferBuilder& builder, const Card* card)
        {
            std::vector<int> mechanics(card->GetMechanics().size());
            for (const auto& mechanic : card->GetMechanics())
            {
                mechanics.emplace_back(static_cast<int>(mechanic));
            }

            return FlatData::CreateCard(
                    builder,
                    builder.CreateString(card->GetID()),
                    static_cast<int>(card->GetRarity()),
                    static_cast<int>(Faction::INVALID),
                    static_cast<int>(CardSet::INVALID),
                    static_cast<int>(card->GetCardClass()),
                    static_cast<int>(card->GetCardType()),
                    static_cast<int>(card->GetRace()),
                    builder.CreateString(card->GetName()),
                    builder.CreateString(""),
                    card->GetCollectible(),
                    card->GetCost(),
                    card->GetAttack(),
                    card->GetHealth(),
                    card->GetDurability(),
                    builder.CreateVector(mechanics),
                    0,
                    0,
                    card->GetMaxAllowedInDeck())
        }

        TaskMeta CreateTaskMetaVector(const std::vector<TaskMeta>& vector)
        {
            fb::FlatBufferBuilder builder(1024);
            std::vector<fb::Offset<FlatData::TaskMeta>> flatten;

            for (const auto& task : vector)
            {
                auto trait = FlatData::TaskMetaTrait(static_cast<int>(task.id), task.status, task.userID);
                auto buffer = builder.CreateVector(task.GetBuffer(), task.GetBufferSize());

                auto temporal = FlatData::CreateTaskMeta(builder, trait, buffer);
                flatten.emplace_back(std::move(temporal));
            }

            auto integrated = FlatData::CreateTaskMetaVector(fb, flatten);
            builder.Finish(integrated);

            return TaskMeta(TaskMetaTrait(TaskID::TASK_TUPLE), builder.GetSize(), builder.GetBufferPoint());
        }

        TaskMeta CreateRequireTaskMeta(TaskID request, BYTE userID)
        {
            fb:FlatBufferBuilder builder(32);
            auto flat = FlatData::CreateRequireTaskMeta(fb, static_cast<int>(request));

            builder.Finish(flat);
            return TaskMeta(
                    TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID, userID),
                    builder.GetSize(),
                    builder.GetBufferPointer());
        }

        TaskMeta CreateRequireMulliganTaskMeta(const BYTE* index, size_t size)
        {
            fb::FlatBufferBuilder builder(32);
            auto vector = builder.CreateVector(index, size);
            auto flat = FlatData::CreateRequireMulliganTaskMeta(fb, vector);

            builder.Finish(flat);
            return TaskMeta(
                    TaskMetaTrait(TaskID::MULLIGAN),
                    builder.GetSize(),
                    builder.GetBufferPointer());
        }

        TaskMeta CreateRequireSummonMinionTaskMeta(int cardIndex, int position)
        {
            fb::FlatBufferBuilder builder(32);
            auto flat = FlatData::CreateRequireSummonMinionTaskMeta(fb,
                    static_cast<BYTE>(cardIndex), static_cast<BYTE>(position));

            builder.Finish(flat);
            return TaskMeta(
                    TaskMetaTrait(TaskID::SELECT_CARD),
                    builder.GetSize(),
                    builder.GetBufferPointer());
        }

        TaskMeta CreateRequireTargetingTaskMeta(int src, int dst)
        {
            fb::FlatBufferBuilder builder(32);
            auto flat = FlatData::CreateRequireTargetingTaskMeta(fb,
                    static_cast<BYTE>(src), static_cast<BYTE>(dst));

            builder.Finish(flat);
            return TaskMeta(
                    TaskMetaTrait(TaskID::SELECT_TARGET),
                    builder.GetSize(),
                    builder.GetBufferPointer());
        }

        void CreateUserSettingTaskMeta(const std::string& firstUserID, const std::string& secondUserID)
        {
            fb::FlatBufferBuilder builder(128);
            auto firstID = builder.CreateString(firstUserID);
            auto secondID = builder.CreateString(secondUserID);

            auto flat = FlatData::CreateUserSettingTaskMeta(builder, firstID, secondID);
            builder.Finish(flat);

            return TaskMeta(TaskMetaTrait(TaskID::USER_SETTING), builder.GetSize(), builder.GetBufferPointer())
        }

        void CreateDrawTaskMeta(const DrawTaskMeta& meta, TaskMeta::status_t status, BYTE userID)
        {
            fb::FlatBufferBuilder builder(512);
            std::vector<fb::Offset<FlatData::Card>> burnt;

            for (const auto& card : meta.burnt)
            {
                burnt.emplace_back(CreateCard(builder, card));
            }

            auto flat = FlatData::CreateDrawTaskMeta(
                    builder,
                    meta.numDraw,
                    meta.numExhausted,
                    meta.numHearts,
                    meta.numOverdraw,
                    burnt);

            builder.Finish(flat);

            return TaskMeta(
                    TaskMetaTrait(TaskID::DRAW, status, userID),
                    builder.GetSize(),
                    builder.GetBufferPointer());
        }

        TaskMeta CreateModifyManaTaskMeta(const ModifyManataskMeta& meta, TaskMeta::status_t status, BYTE userID)
        {
            fb::FlatBufferBuilder builder(32);
            auto manaTask = FlatData::CreateModifyManaTaskMeta(
                    builder, meta.numMode, meta.manaMode, meta.object, meta.result);

            builder.Finish(manaTask);

            return TaskMeta(
                    TaskMetaTrait(TaskID::MODIFY_MANA, status, userID),
                    builder.GetSize(),
                    builder.GetBufferPointer());
        }

        TaskMeta CreateModifyHealthTaskMeta(const ModifyHealthTaskMeta& meta, TaskMeta::status_t status, BYTE userID)
        {
            fb::FlatBufferBuilder builder(32);
            auto card = CreateCard(builder, meta.card);
            auto healthTask = FlatData::CreateModifyHealthTaskMeta(
                    builder, card, meta.damage, meta.hurted, meta.isExhausted);

            builder.Finish(healthTask);
            return TaskMeta(
                    TaskMetaTrait(TaskID::MODIFY_HEALTH, status, userID),
                    builder.GetSize(),
                    builder.GetBufferPointer());
        }

        TaskMeta CreateBriefTaskMeta(const BriefTaskMeta& meta, TaskMeta::status_t status, BYTE userID)
        {
            using CardOffset = fb::Offset<FlatData::Card>;
            using VectorOffset = fb::Offset<fb::Vector<CardOffset>>;

            fb::FlatBufferBuilder builder(256);

            auto target = { meta.currentField, meta.currentHand, meta.opponentField, meta.currentAttacked, meta.opponentAttacked };
            std::vector<VectorOffset> result(target.size());

            std::transform(target.begin(), target.end(), result.begin(), [&builder](auto&& vec)
            {
                std::vector<CardOffset> dest(vec.size());
                std::transform(vec.begin(), vec.end(), dest.begin(),
                               [&builder](const Card* card) { return CreateCard(builder, card); });

                return builder.CreateVector(dest);
            });

            auto brief = FlatData::CreateBriefTaskMeta(builder, meta.currentUser, meta.opponetUser, meta.currentMana, meta.opponetMana,
                    CreateCard(builder, meta.currentHero), CreateCard(builder, meta.opponentHero),
                    result[0], result[1], result[2], meta.numOpponentHand, result[3], result[4]);

            builder.Finish(brief);
            return TaskMeta(
                    TaskMetaTrait(TaskID::BRIEF, status, userID),
                    builder.GetSize(),
                    builder.GetBufferPointer());
        }

        TaskMeta CreateGameEndTaskMeta(const std::string& winner)
        {
            fb::FlatBufferBuilder builder(128);
            auto winnerID = builder.CreateString(winner);
            auto flat = FlatData::CreateGameEndTaskMeta(fb, winnerID);

            builder.Finish(flat);
            return TaskMeta(
                    TaskMetaTrait(TaskID::GAME_END),
                    builder.GetSize(),
                    builder.GetBufferPointer());
        }
    }
}
