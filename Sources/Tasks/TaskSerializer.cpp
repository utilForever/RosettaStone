/*************************************************************************
> File Name: TaskSerializer.cpp
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose: Serializer for TaskMeta and MetaData
> Created Time: 2018/05/20
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/
#include <Tasks/TaskSerializer.h>

namespace Hearthstonepp
{
    namespace Serializer
    {
        using fb = flatbuffers;

        void CreateTaskMetaVector(TaskMeta& meta, const std::vector<TaskMeta>& vector)
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

            meta = TaskMeta(TaskMetaTrait(TaskID::TASK_TUPLE), builder.GetSize(), builder.GetBufferPoint());
        }
    }
}
