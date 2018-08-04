#include "TestTasks.h"

TestTask::TestTask(TaskID id, std::function<MetaData(Player &, Player &)> &&impl)
	: m_id(id), m_impl(std::move(impl))
{
	// Do Nothing
}

TaskID TestTask::GetTaskID() const
{
	return m_id;
}

MetaData TestTask::Impl(Player &player1, Player &player2)
{
	return m_impl(player1, player2);
}

