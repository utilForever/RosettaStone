/*************************************************************************
> File Name: Interface.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Interface for Hearthstone Game Agent
> Created Time: 2017/10/24
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Interface/Interface.h>
#include <Tasks/BasicTask.h>
#include <Tasks/TaskSerializer.h>

namespace Hearthstonepp
{
	GameInterface::GameInterface(GameAgent& agent, std::ostream& output, std::istream& input) :
			m_agent(agent), m_briefCache(nullptr), m_ostream(output), m_istream(input)
	{
		// Do Nothing
	}

	GameResult GameInterface::StartGame()
	{
		std::thread at = m_agent.StartAgent();

		while (true)
		{
			m_agent.GetTaskMeta(m_buffer);

			const size_t msg = HandleMessage(m_buffer);
			if (msg == HANDLE_STOP)
			{
				break;
			}
		}

		// join agent thread
		at.join();

		using GameEndTaskMeta = FlatData::GameEndTaskMeta;
		auto buffer = m_buffer.GetBuffer();
		auto meta = flatbuffers::GetRoot<GameEndTaskMeta>(buffer.get());

		GameResult result;
		result.winnerUserID = meta->winnerID()->c_str();

		return result;
	}

	size_t GameInterface::HandleMessage(const TaskMeta& serialized)
	{
		if (m_handler.find(serialized.id) != m_handler.end())
		{
			// find from handler table and call it
			m_handler[serialized.id](*this, serialized);
		}

		if (serialized.id == +TaskID::GAME_END)
		{
			return HANDLE_STOP;
		}

		return HANDLE_CONTINUE;
	}

	std::ostream& GameInterface::LogWriter(const std::string& name)
	{
		m_ostream << "[*] " << name << " : ";
		return m_ostream;
	}

	template <std::size_t SIZE>
	void GameInterface::ShowMenus(std::array<std::string, SIZE> menus)
	{
		for (auto& menu : menus)
		{
			m_ostream << menu << std::endl;
		}
	}

	void GameInterface::ShowCards(const CardVector& cards)
	{
		for (const auto& card : cards)
		{
			CardType cardType = CardType::_from_integral(card->cardType());
			m_ostream << '[' << card->name()->c_str() << '(' << cardType._name() << " / " << card->cost() << ")] ";
			if (cardType == +CardType::MINION)
			{
				m_ostream << "(ATK " << card->attack() << "/HP " << card->health() << ")";
			}
			m_ostream << std::endl;
		}
	}

	void GameInterface::HandleInvalid(const TaskMeta&)
	{
		// Do Nothing
	}

	void GameInterface::HandleUserSetting(const TaskMeta& serialized)
	{
		using UserSettingTaskMeta = FlatData::UserSettingTaskMeta;
		auto buffer = serialized.GetBuffer();
		auto meta = flatbuffers::GetRoot<UserSettingTaskMeta>(buffer.get());

		m_users[0] = meta->firstID()->c_str();
		m_users[1] = meta->secondID()->c_str();

		std::string name = "User Setting";
		LogWriter(name)
				<< "first : " << m_users[0] << " / "
				<< "second : " << m_users[1] << std::endl;
	}

	void GameInterface::HandleSwap(const TaskMeta&)
	{
		std::string name = "User";
		LogWriter(name) << "Swap" << std::endl;
	}

	void GameInterface::HandleShuffle(const TaskMeta& serialized)
	{
		LogWriter(m_users[serialized.userID]) << "Shuffled" << std::endl;
	}

	void GameInterface::HandleDraw(const TaskMeta& serialized)
	{
		using DrawTaskMeta = FlatData::DrawTaskMeta;
		auto buffer = serialized.GetBuffer();
		auto meta = flatbuffers::GetRoot<DrawTaskMeta>(buffer.get());

		std::ostream& stream = LogWriter(m_users[serialized.userID]);
		if (serialized.status == MetaData::DRAW_SUCCESS)
		{
			stream << "Draw Success" << std::endl;
		}
		else
		{
			if (serialized.status == MetaData::DRAW_EXHAUST ||
                serialized.status == MetaData::DRAW_EXHAUST_OVERDRAW)
			{
				stream << "Draw Exhausted : "
					   << meta->numExhausted() << " Cards, "
					   << meta->numHearts() << " Hearts" << std::endl;
			}

			if (serialized.status == MetaData::DRAW_OVERDRAW ||
                serialized.status == MetaData::DRAW_EXHAUST_OVERDRAW)
			{
				stream << "Draw OverDraw : " << meta->numOverdraw() << " Cards" << std::endl;
				ShowCards(*meta->burnt());
			}
		}
	}

	void GameInterface::InputMulligan(const TaskMeta& meta)
	{
		LogWriter(m_users[meta.userID]) << "Input Mulligan" << std::endl;

		size_t numMulligan;
		while (true)
		{
			m_ostream << "[*] How many cards to mulligan ? (0 ~ 3) ";
			m_istream >> numMulligan;

			if (numMulligan <= NUM_BEGIN_DRAW)
			{
				break;
			}
		}

		BYTE mulligan[NUM_BEGIN_DRAW] = { 0, };
		for (size_t i = 0; i < numMulligan; ++i)
		{
			while (true)
			{
				size_t index = 0;
				m_ostream << "[*] Input card index " << i+1 << " (0 ~ 2) : ";
				m_istream >> index;

				if (index <= NUM_BEGIN_DRAW - 1)
				{
					mulligan[i] = static_cast<BYTE>(index);
					break;
				}
			}
		}

		TaskMeta result = Serializer::CreateRequireMulliganTaskMeta(mulligan, numMulligan);
		m_agent.WriteSyncBuffer(std::move(result));
	}

	void GameInterface::HandleMulligan(const TaskMeta& serialized)
	{
		std::ostream& stream = LogWriter(m_users[serialized.userID]);

		switch (serialized.status)
		{
			case MetaData::MULLIGAN_SUCCESS:
				stream << "Mulligan Success" << std::endl;
				break;

			case MetaData::MULLIGAN_INDEX_OUT_OF_RANGE:
				stream << "Mulligan Index out of range exception" << std::endl;
				break;

			case MetaData::MULLIGAN_DUPLICATED_INDEX:
				stream << "Mulligan Duplicated index exception" << std::endl;
				break;
		}
	}

	void GameInterface::HandleManaModification(const TaskMeta& serialized)
	{
		using ModifyManaTaskMeta = FlatData::ModifyManaTaskMeta;
		auto buffers = serialized.GetBuffer();
		auto meta = flatbuffers::GetRoot<ModifyManaTaskMeta>(buffers.get());

		std::string manaMode = "";
		switch (meta->manaMode())
		{
			case BasicTask::MANA_EXIST:
				manaMode = "exist";
				break;
			case BasicTask::MANA_TOTAL:
				manaMode = "total";
				break;
		}

		std::string numMode = "";
		switch (meta->numMode())
		{
			case BasicTask::NUM_ADD:
				numMode = "add";
				break;
			case BasicTask::NUM_SUB:
				numMode = "sub";
				break;
			case BasicTask::NUM_SYNC:
				numMode = "synchronize";
				break;
		}

		LogWriter(m_users[serialized.userID]) << "Modify Mana : "
										<< numMode << " "
										<< static_cast<int>(meta->object()) << " to "
										<< manaMode << " mana,"
										<< " result " << static_cast<int>(meta->result()) << std::endl;
	}

	void GameInterface::HandleHealthModification(const TaskMeta& serialized)
	{
		using ModifyHealthTaskMeta = FlatData::ModifyHealthTaskMeta;
		auto buffer = serialized.GetBuffer();
		auto meta = flatbuffers::GetRoot<ModifyHealthTaskMeta>(buffer.get());

		LogWriter(m_users[serialized.userID]) << "Modify Health : "
										<< meta->card()->name()->c_str() << " get damage "
										<< meta->damage() << ", result" << meta->hurted() << std::endl;
	}
//
	void GameInterface::HandleSummonMinion(const TaskMeta& serialized)
	{
		using SummonMinionTaskMeta = FlatData::SummonMinionTaskMeta;
		auto buffer = serialized.GetBuffer();
		auto meta = flatbuffers::GetRoot<SummonMinionTaskMeta>(buffer.get());

		auto card = meta->card();

		std::ostream& stream = LogWriter(m_users[serialized.userID]) << "Summon Minion : ";
		switch (serialized.status)
		{
			case MetaData::SUMMON_SUCCESS:
				stream << card->name()->c_str() << " at " << meta->index() << std::endl;
				break;

			case MetaData::SUMMON_CARD_IDX_OUT_OF_RANGE:
				stream << "Card index out of range of hand." << std::endl;
				break;

			case MetaData::SUMMON_NOT_ENOUGH_MANA:
				stream << "Not enough mana" << std::endl;
				break;

			case MetaData::SUMMON_POSITION_OUT_OF_RANGE:
				stream << "Position out of range of field" << std::endl;
				break;
		}
	}

	void GameInterface::HandleCombat(const TaskMeta& serialized)
	{
		using CombatTaskMeta = FlatData::CombatTaskMeta;
		auto buffer = serialized.GetBuffer();
		auto meta = flatbuffers::GetRoot<CombatTaskMeta>(buffer.get());

		LogWriter(m_users[serialized.userID])
				<< "Combat : {src " << meta->src()->name()->c_str() << "} "
				<< "vs {dst " << meta->dst()->name()->c_str() << "}" << std::endl;
	}

	void GameInterface::HandleRequire(const TaskMeta& serialized)
	{
		using RequireTaskMeta = FlatData::RequireTaskMeta;
		auto buffer = serialized.GetBuffer();
		auto meta = flatbuffers::GetRoot<RequireTaskMeta>(buffer.get());

		auto required = TaskID::_from_integral(meta->required());

		if (m_inputHandler.find(required) != m_inputHandler.end())
		{
			m_inputHandler[required](*this, serialized);
		}
	}

	void GameInterface::HandleBrief(const TaskMeta& serialized)
	{
		using BriefTaskMeta = FlatData::BriefTaskMeta;
		m_briefRawCache = serialized.GetBuffer();
		m_briefCache = flatbuffers::GetRoot<BriefTaskMeta>(m_briefRawCache.get());

		std::ostream& stream = LogWriter(m_users[serialized.userID]) << "Game Briefing" << std::endl;

		stream << m_users[m_briefCache->opponentUser()]
			   << " - Hero " << m_briefCache->opponentHero()->name()
			   << ", Health " << m_briefCache->opponentHero()->name()
			   << ", Mana " << static_cast<int>(m_briefCache->opponentMana())
			   << ", Hand " << static_cast<int>(m_briefCache->numOpponentHand())
			   << std::endl;

		stream << m_users[m_briefCache->opponentUser()] << " Field" << std::endl;
		ShowCards(*m_briefCache->opponentField());

		stream << m_users[m_briefCache->currentUser()]
			   << " - Hero " << m_briefCache->currentHero()->name()
			   << ", Health " << m_briefCache->currentHero()->health()
			   << ", Mana " << static_cast<int>(m_briefCache->currentMana())
			   << ", Hand " << static_cast<int>(m_briefCache->currentHand()->size())
			   << std::endl;

		stream << m_users[m_briefCache->currentUser()] << " Field" << std::endl;
		ShowCards(*m_briefCache->currentField());

		stream << m_users[m_briefCache->currentUser()] << " Hand" << std::endl;
		ShowCards(*m_briefCache->currentHand());
	}

	void GameInterface::InputSelectMenu(const TaskMeta& meta)
	{
		LogWriter(m_users[meta.userID]) << "Main Menu" << std::endl;
		ShowMenus(m_mainMenuStr);

		size_t input;
		while (true)
		{
			m_ostream << "[*] Input menu : ";
			m_istream >> input;

			if (input > 0 && input <= GAME_MAIN_MENU_SIZE)
			{
				input -= 1;
				break;
			}
		}

		TaskMeta result(TaskMetaTrait(TaskID::SELECT_CARD, static_cast<TaskMeta::status_t>(input)), 0, nullptr);
		m_agent.WriteSyncBuffer(std::move(result));
	}

	void GameInterface::InputSelectCard(const TaskMeta& meta)
	{
		LogWriter(m_users[meta.userID]) << "Select Card" << std::endl;

		auto currentHand = m_briefCache->currentHand();

		int numCurrentHand = currentHand->size();
		int currentMana = m_briefCache->currentMana();

		int in;
		while (true)
		{
			m_ostream << "Select card index (0 ~ " << numCurrentHand - 1 << ") : ";

			m_istream >> in;
			if (in >= 0 && in < numCurrentHand)
			{
				if(currentHand->Get(in)->cost() > currentMana)
				{
					m_ostream << "Not enough mana" << std::endl;
				}
				else
				{
					break;
				}
			}
		}

		auto currentField = m_briefCache->currentField();

		int numCurrentField = currentField->size();
		CardType cardType = CardType::_from_integral(currentHand->Get(in)->cardType());

		// if selected card type is minion
		if (cardType == +CardType::MINION)
		{
			int pos;
			while (true)
			{
				m_ostream << "Select Position (0 ~ " << numCurrentField << ") : ";

				m_istream >> pos;
				if (pos >= 0 && pos <= numCurrentField)
				{
					break;
				}
			}

			TaskMeta serialized = Serializer::CreateRequireSummonMinionTaskMeta(in, pos);
			m_agent.WriteSyncBuffer(std::move(serialized));
		}
		else
		{
			// TODO : if not minion
			m_agent.WriteSyncBuffer(TaskMeta());
		}
	}

	void GameInterface::InputTargeting(const TaskMeta& meta)
	{
		LogWriter(m_users[meta.userID]) << "Targeting" << std::endl;

		auto currentField = m_briefCache->currentField();
		int numCurrentField = currentField->size();

		m_ostream << "User field : " << std::endl;
		ShowCards(*currentField);

		auto opponentField = m_briefCache->opponentField();
		int numOpponentField = opponentField->size();

		m_ostream << "Opponent field : " << std::endl;
		ShowCards(*m_briefCache->opponentField());

		int src;
		while (true)
		{
			m_ostream << "Select source minion (0 ~ " << numCurrentField - 1 << ") : ";

			m_istream >> src;
			if (src >= 0 && src < numCurrentField)
			{
				auto currentAttacked = m_briefCache->currentAttacked();
				auto begin = currentAttacked->begin();
				auto end = currentAttacked->end();

				if (std::find(begin, end, currentField->Get(src)) != end)
				{
					m_ostream << "Already attacked minion." << std::endl;
				}
				else
				{
					break;
				}
			}
		}

		int dst;
		while (true)
		{
			m_ostream
					<< "Select destination (0 for hero, 1 ~ "
					<< numOpponentField << " for minion) : ";

			m_istream >> dst;
			if (dst >= 0 && dst <= numOpponentField)
			{
				break;
			}
		}

		TaskMeta targeting = Serializer::CreateRequireTargetingTaskMeta(src, dst);
		m_agent.WriteSyncBuffer(std::move(targeting));
	}

	void GameInterface::HandleTaskTuple(const TaskMeta& serialized)
	{
		auto buffer = serialized.GetBuffer();
		auto metaVector = flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());

		for (const auto& meta : *metaVector->vector())
		{
			HandleMessage(TaskMeta::ConvertFrom(meta));
		}
	}

	void GameInterface::HandleGameEnd(const TaskMeta& serialized)
	{
		using GameEndTaskMeta = FlatData::GameEndTaskMeta;
		auto buffer = serialized.GetBuffer();
		auto meta = flatbuffers::GetRoot<GameEndTaskMeta>(buffer.get());

		LogWriter(meta->winnerID()->str()) << "Win" << std::endl;
	}
}