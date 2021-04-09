// This code is based on Sabberstone project.
// Copyright (c) 2017-2019 SabberStone Team, darkfriend77 & rnilva
// RosettaStone is hearthstone simulator using C++ with reinforcement learning.
// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

#ifndef ROSETTASTONE_PLAYMODE_MATH_NUMBER_INDEX_TASK_HPP
#define ROSETTASTONE_PLAYMODE_MATH_NUMBER_INDEX_TASK_HPP

#include <Rosetta/PlayMode/Tasks/ITask.hpp>

// Forward declaration
namespace RosettaStone::PlayMode
{
struct TaskStack;
}  // namespace RosettaStone::PlayMode

namespace RosettaStone::PlayMode::SimpleTasks
{
//! The operation of mathematics.
enum class MathOperation
{
    ADD,  //!< Addition.
    SUB,  //!< Subtraction.
    MUL,  //!< Multiplication.
    DIV   //!< Division.
};

//!
//! \brief MathNumberIndexTask class.
//!
//! This class represents the task for calculating two indexes.
//!
class MathNumberIndexTask : public ITask
{
 public:
    //! Constructs task with given \p indexA, \p indexB, \p mathOp
    //! and \p resultIndex.
    //! \param indexA The first index to calculate.
    //! \param indexB The second index to calculate.
    //! \param mathOp The operation of mathematics to calculate.
    //! \param resultIndex The index to store the result in task stack.
    MathNumberIndexTask(int indexA, int indexB, MathOperation mathOp,
                        int resultIndex = 0);

 private:
    //! Processes task logic internally and returns meta data.
    //! \param player The player to run task.
    //! \return The result of task processing.
    TaskStatus Impl(Player* player) override;

    //! Internal method of Clone().
    //! \return The cloned task.
    std::unique_ptr<ITask> CloneImpl() override;

    //! Returns the number of index from task stack.
    //! \param index The index to get number.
    //! \param taskStack The task stack.
    //! \return The number of index.
    int GetNumber(int index, const TaskStack& taskStack);

    int m_indexA = 0;
    int m_indexB = 0;
    MathOperation m_mathOp;
    int m_resultIndex = 0;
};
}  // namespace RosettaStone::PlayMode::SimpleTasks

#endif  // ROSETTASTONE_PLAYMODE_MATH_NUMBER_INDEX_TASK_HPP
