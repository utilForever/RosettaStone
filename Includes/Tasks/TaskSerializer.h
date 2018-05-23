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

        TaskMeta CreateTaskMetaVector(const std::vector<TaskMeta>& vector);
        TaskMeta CreateRequireTaskMeta(TaskID request, BYTE userID);
        TaskMeta CreateUserSettingTaskMeta(const std::string& firstUserID, const std::string& secondUserID);
        TaskMeta CreateDrawTaskMeta(const DrawTaskMeta& draw, TaskMeta::status_t status, BYTE userID);
    }
}

#endif //HEARTHSTONEPP_TASKSERIALIZER_H
