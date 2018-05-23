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

        void CreateTaskMetaVector(const std::vector<TaskMeta>& vector)
        {
            fb::FlatBufferBuilder builder(1024);
            auto flatten = std::vector<fb::Offset<MetaData::TaskMeta>>;

            for (const auto& task : vector)
            {
                auto trait = MetaData::TaskMetaTrait(static_cast<int>(meta.id), meta.status, meta.userID);
                auto temporal = MetaData::CreateTaskMeta(builder, trait, task.GetBuffer());
                flatten.emplace_back(std::move(temporal));
            }

            auto integrated = MetaData::CreateTaskMetaVector(fb, flatten);
            builder.Finish(integrated);

            return TaskMeta(TaskMetaTrait(TaskID::TASK_TUPLE), builder.GetSize(), builder.GetBufferPoint());
        }

        void CreateRequireTaskMeta(TaskID request, BYTE userID)
        {
            fb:FlatBufferBuilder builder(32);
            auto flat = MetaData::CreateRequireTaskMeta(fb, static_cast<int>(request));

            builder.Finish(flat);
            return TaskMeta(
                    TaskMetaTrait(TaskID::REQUIRE, MetaData::INVALID, userID),
                    builder.GetSize(),
                    builder.GetBufferPointer());
        }

        void CreateUserSettingTaskMeta(const std::string& firstUserID, const std::string& secondUserID)
        {
            fb::FlatBufferBuilder builder(128);
            auto firstID = builder.CreateString(firstUserID);
            auto secondID = builder.CreateString(secondUserID);

            auto flat = MetaData::CreateUserSettingTaskMeta(builder, firstID, secondID);
            builder.Finish(flat);

            return TaskMeta(TaskMetaTrait(TaskID::USER_SETTING), builder.GetSize(), builder.GetBufferPointer())
        }

        void CreateDrawTaskMeta(const DrawTaskMeta& meta, TaskMeta::status_t status, BYTE userID)
        {
            fb::FlatBufferBuilder builder(512);
            std::vector<fb::Offset<MetaData::Card>> burnt;

            for (const auto& card : meta.burnt)
            {
                std::vector<int> mechanics(card->GetMechanics().size());
                for (const auto& mechanic : card->GetMechanics())
                {
                    mechanics.emplace_back(static_cast<int>(mechanic));
                }

                burnt.emplace_back(MetaData::CreateCard(
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
                        card->GetMaxAllowedInDeck()));
            }

            auto flat = MetaData::CreateDrawTaskMeta(
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
    }
}
