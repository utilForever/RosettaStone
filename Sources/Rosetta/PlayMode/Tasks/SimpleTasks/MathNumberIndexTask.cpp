// This code is based on Sabberstone project.
// Copyright (c) 2017-2023 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2017-2023 Chris Ohk

#include <Rosetta/PlayMode/Games/Game.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/IncludeTask.hpp>
#include <Rosetta/PlayMode/Tasks/SimpleTasks/MathNumberIndexTask.hpp>
#include <Rosetta/PlayMode/Tasks/TaskStack.hpp>

#include <stdexcept>

namespace RosettaStone::PlayMode::SimpleTasks
{
MathNumberIndexTask::MathNumberIndexTask(int indexA, int indexB,
                                         MathOperation mathOp, int resultIndex)
    : m_indexA(indexA),
      m_indexB(indexB),
      m_mathOp(mathOp),
      m_resultIndex(resultIndex)
{
    // Do nothing
}

TaskStatus MathNumberIndexTask::Impl(Player* player)
{
    TaskStack& stack = player->game->taskStack;

    const int numberA = GetNumber(m_indexA, stack);
    const int numberB = GetNumber(m_indexB, stack);

    int result = 0;

    switch (m_mathOp)
    {
        case MathOperation::ADD:
            result = numberA + numberB;
            break;
        case MathOperation::SUB:
            result = numberA - numberB;
            break;
        case MathOperation::MUL:
            result = numberA * numberB;
            break;
        case MathOperation::DIV:
            result = numberA / numberB;
            break;
    }

    switch (m_resultIndex)
    {
        case 0:
            stack.num[0] = result;
            break;
        case 1:
            stack.num[1] = result;
            break;
        case 2:
            stack.num[2] = result;
            break;
        case 3:
            stack.num[3] = result;
            break;
        case 4:
            stack.num[4] = result;
            break;
        default:
            throw std::invalid_argument(
                "MathNumberIndexTask::Impl() - Unknown result index!\n");
    }

    return TaskStatus::COMPLETE;
}

std::unique_ptr<ITask> MathNumberIndexTask::CloneImpl()
{
    return std::make_unique<MathNumberIndexTask>(m_indexA, m_indexB, m_mathOp,
                                                 m_resultIndex);
}

int MathNumberIndexTask::GetNumber(int index, const TaskStack& taskStack)
{
    switch (index)
    {
        case 0:
            return taskStack.num[0];
        case 1:
            return taskStack.num[1];
        case 2:
            return taskStack.num[2];
        case 3:
            return taskStack.num[3];
        case 4:
            return taskStack.num[4];
        default:
            throw std::invalid_argument(
                "MathNumberIndexTask::GetNumber() - Unknown index!\n");
    }
}
}  // namespace RosettaStone::PlayMode::SimpleTasks
