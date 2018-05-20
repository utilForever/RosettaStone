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

namespace Hearthstonepp
{
    namespace Serializer
    {
        void CreateTaskMetaVector(TaskMeta& meta, const std::vector<TaskMeta>& vector);
    }
}

#endif //HEARTHSTONEPP_TASKSERIALIZER_H
