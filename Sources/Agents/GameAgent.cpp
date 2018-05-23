/*************************************************************************
> File Name: GameAgent.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hearthstone Game Agent
> Created Time: 2017/09/26
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/GameAgent.h>
#include <Tasks/BasicTask.h>

#include <random>

namespace Hearthstonepp
{
    template <typename UserT, typename = void>
	GameAgent::GameAgent(UserT&& user1, UserT&& user2) :
			m_current(std::forward<UserT>(user1)), m_opponent(std::forward<UserT>(user2))
	{
		// Do Nothing
	}

	std::thread GameAgent::StartAgent()
	{
		auto flow = [this]() {
			BeginPhase();
//			while (true)
//			{
//				bool isGameEnd = MainPhase();
//				if (isGameEnd)
//				{
//					break;
//				}
//			}
//
//			FinalPhase();
		};

		return std::thread(std::move(flow));
	}

	void GameAgent::GetTaskMeta(TaskMeta& meta)
	{
		m_taskAgent.Read(meta);
	}

	void GameAgent::WriteSyncBuffer(TaskMeta&& data, bool sideChannel)
	{
	    m_taskAgent.Notify(std::move(data), sideChannel);
	}

	void GameAgent::BeginPhase()
	{
		std::random_device rd;
		std::default_random_engine gen(rd());

		// get random number, zero or one.
		std::uniform_int_distribution<int> bin(0, 1);
		// swap user with 50% probability
		if (bin(gen) == 1)
		{
			m_taskAgent.Add(BasicTask::SwapUserTask());
		}

//		auto untilMulliganSuccess = [](const TaskSerialized& serialized) {
//			return serialized.status == MetaData::MULLIGAN_SUCCESS;
//		};

		m_taskAgent.Add(BasicTask::UserSettingTask());
		m_taskAgent.Add(BasicTask::DoBothUser(BasicTask::ShuffleTask()));
		m_taskAgent.Add(BasicTask::DoBothUser(BasicTask::DrawTask(NUM_BEGIN_DRAW)));
//		m_taskAgent.Add(BasicTask::BriefTask());
//		m_taskAgent.Add(BasicTask::DoUntil(BasicTask::MulliganTask(NUM_BEGIN_DRAW, m_taskAgent), untilMulliganSuccess));
		m_taskAgent.Add(BasicTask::SwapUserTask());
//		m_taskAgent.Add(BasicTask::BriefTask());
//		m_taskAgent.Add(BasicTask::DoUntil(BasicTask::MulliganTask(NUM_BEGIN_DRAW, m_taskAgent), untilMulliganSuccess));
		m_taskAgent.Add(BasicTask::SwapUserTask());

        TaskMeta meta;
		m_taskAgent.Run(meta, m_current, m_opponent);
		m_taskAgent.Clear();

		// TODO: Coin for later user
		m_opponent.hand.push_back(new Card());
	}

	bool GameAgent::MainPhase()
	{
		// Ready for main phase
		MainReady();
		// Get game status from method MainMenu
		return MainMenu();
	}

	void GameAgent::FinalPhase()
	{
	    TaskMeta meta;
//		m_taskAgent.Run(BasicTask::GameEndTask(), meta, m_current, m_opponent, false);
	}

	void GameAgent::MainReady()
	{
		m_taskAgent.Add(BasicTask::DrawTask(1));
//		m_taskAgent.Add(BasicTask::ModifyManaTask(BasicTask::NUM_ADD, BasicTask::MANA_TOTAL, 1));
//		m_taskAgent.Add(BasicTask::ModifyManaByRef(BasicTask::NUM_SYNC, BasicTask::MANA_EXIST, m_current.totalMana));

		TaskMeta meta;
		m_taskAgent.Run(meta, m_current, m_opponent);
		m_taskAgent.Clear();

		m_current.attacked.clear();
	}

	bool GameAgent::MainMenu()
	{
		// Check before starting main phase
		if (IsGameEnd())
		{
			return true;
		}

		TaskMeta meta;
//		m_taskAgent.Run(BasicTask::BriefTask(), meta, m_current, m_opponent, false);
//		m_taskAgent.Run(BasicTask::SelectMenuTask(m_taskAgent), meta, m_current, m_opponent);

		TaskMeta::status_t menu = meta.status;

		if (menu == GAME_MAIN_MENU_SIZE - 1)
		{
			// Main End phase
			m_taskAgent.Run(BasicTask::SwapUserTask(), meta, m_current, m_opponent);
		}
		else
		{
			if (menu >= 0 && menu < GAME_MAIN_MENU_SIZE - 1)
			{
				// call action methods, like UseCard or Combat
				m_mainMenuFuncs[menu](*this);
			}
			return MainMenu();
		}

		return false;
	}

	void GameAgent::MainUseCard()
	{
		// Read what kinds of card user wants to use
//        TaskMeta meta;
//        m_taskAgent.Run(BasicTask::SelectCardTask(m_taskAgent), meta, m_current, m_opponent);
//
//		if (meta.status == MetaData::SELECT_CARD_MINION)
//		{
//			using Require = MetaData::RequireSummonMinionTaskMeta;
//			Require minion = Serializer<Require>::Deserialize(meta);
//			m_taskAgent.Run(BasicTask::SummonMinionTask(minion.cardIndex, minion.position), meta, m_current, m_opponent);
//		}
	}

	void GameAgent::MainCombat()
	{
//	    TaskMeta meta;
//		m_taskAgent.Run(BasicTask::SelectTargetingTask(m_taskAgent), meta, m_current, m_opponent);
//
//		using Require = MetaData::RequireTargetingTaskMeta;
//		Require targeting = Serializer<Require>::Deserialize(meta);
//
//		m_taskAgent.Run(BasicTask::CombatTask(targeting.src, targeting.dst), meta, m_current, m_opponent);
	}

	bool GameAgent::IsGameEnd()
	{
		int healthCurrent = m_current.hero->GetHealth();
		int healthOpponent = m_opponent.hero->GetHealth();

		if (healthCurrent < 1 || healthOpponent < 1) {
			return true;
		}
		else {
			return false;
		}

	}
}
