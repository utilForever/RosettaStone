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

namespace Hearthstonepp
{
	GameInterface::GameInterface(GameAgent& agent, std::ostream& output, std::istream& input) :
			m_agent(agent), m_ostream(output), m_istream(input)
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

//		using GameEndTaskMeta = FlatData::GameEndTaskMeta;
//		GameEndTaskMeta meta = Serializer<GameEndTaskMeta>::Deserialize(m_buffer);
//
//		GameResult result;
//		result.winnerID = meta.winnerID;
//
//		return result;
		return GameResult();
	}

	size_t GameInterface::HandleMessage(const TaskMeta& serialized)
	{
		if (m_handler.find(serialized.id) != m_handler.end())
		{
			// find from handler table and call it
			m_handler[serialized.id](*this, serialized);
		}

//		if (serialized.id == TaskID::GAME_END)
//		{
//			return HANDLE_STOP;
//		}

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

	void GameInterface::ShowCards(const CardVector& cards, int size)
	{
		for (int i = 0; i < size; ++i)
		{
		    CardType cardType = CardType::_from_integral(cards[i]->cardType());
			m_ostream << '[' << cards[i]->name()->c_str() << '(' << cardType._name() << " / " << cards[i]->cost() << ")] ";
			if (cardType._to_integral() == (+CardType::MINION)._to_integral())
			{
				m_ostream << "(ATK " << cards[i]->attack() << "/HP " << cards[i]->health() << ")";
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
				ShowCards(*meta->burnt(), meta->burnt()->size());
			}
		}
	}

//	void GameInterface::InputMulligan(const FlatData::RequireTaskMeta& meta)
//	{
//		using RequireMulliganTaskMeta = FlatData::RequireMulliganTaskMeta;
//		RequireMulliganTaskMeta mulligan;
//
//		LogWriter(m_users[meta.userID]) << "Input Mulligan" << std::endl;
//
//		size_t numMulligan;
//		while (true)
//		{
//			m_ostream << "[*] How many cards to mulligan ? (0 ~ 3) ";
//			m_istream >> numMulligan;
//
//			if (numMulligan <= NUM_BEGIN_DRAW)
//			{
//				break;
//			}
//		}
//
//		for (size_t i = 0; i < numMulligan; ++i)
//		{
//			while (true)
//			{
//				size_t index = 0;
//				m_ostream << "[*] Input card index " << i+1 << " (0 ~ 2) : ";
//				m_istream >> index;
//
//				if (index <= NUM_BEGIN_DRAW - 1)
//				{
//					mulligan.mulligan[i] = static_cast<BYTE>(index);
//					break;
//				}
//			}
//		}
//
//		mulligan.size = static_cast<BYTE>(numMulligan);
//		TaskMeta result = Serializer<FlatData::RequireMulliganTaskMeta>::Serialize(mulligan);
//
//		// send index to agent
//		m_agent.WriteSyncBuffer(std::move(result));
//	}
//
//	void GameInterface::HandleMulligan(const TaskMeta& serialized)
//	{
//		TaskMeta meta = Serializer<TaskMeta>::Deserialize(serialized);
//		std::ostream& stream = LogWriter(m_users[meta.userID]);
//
//		switch (meta.status)
//		{
//			case MetaData::MULLIGAN_SUCCESS:
//				stream << "Mulligan Success" << std::endl;
//				break;
//
//			case MetaData::MULLIGAN_INDEX_OUT_OF_RANGE:
//				stream << "Mulligan Index out of range exception" << std::endl;
//				break;
//
//			case MetaData::MULLIGAN_DUPLICATED_INDEX:
//				stream << "Mulligan Duplicated index exception" << std::endl;
//				break;
//		}
//	}
//
//	void GameInterface::HandleManaModification(const TaskMeta& serialized)
//	{
//		using ModifyManaTaskMeta = FlatData::ModifyManaTaskMeta;
//		ModifyManaTaskMeta meta = Serializer<ModifyManaTaskMeta>::Deserialize(serialized);
//
//		std::string manaMode = "";
//		switch (meta.manaMode)
//		{
//			case BasicTask::MANA_EXIST:
//				manaMode = "exist";
//				break;
//			case BasicTask::MANA_TOTAL:
//				manaMode = "total";
//				break;
//		}
//
//		std::string numMode = "";
//		switch (meta.numMode)
//		{
//			case BasicTask::NUM_ADD:
//				numMode = "add";
//				break;
//			case BasicTask::NUM_SUB:
//				numMode = "sub";
//				break;
//			case BasicTask::NUM_SYNC:
//				numMode = "synchronize";
//				break;
//		}
//
//		LogWriter(m_users[meta.userID]) << "Modify Mana : "
//										<< numMode << " "
//										<< static_cast<int>(meta.object) << " to "
//										<< manaMode << " mana,"
//										<< " result " << static_cast<int>(meta.result) << std::endl;
//	}
//
//	void GameInterface::HandleHealthModification(const TaskMeta& serialized)
//	{
//		using ModifyHealthTaskMeta = FlatData::ModifyHealthTaskMeta;
//		ModifyHealthTaskMeta meta = Serializer<ModifyHealthTaskMeta>::Deserialize(serialized);
//
//		LogWriter(m_users[meta.userID]) << "Modify Health : "
//										<< meta.card->GetName() << " get damage "
//										<< meta.damage << ", result" << meta.hurted << std::endl;
//	}
//
//	void GameInterface::HandleSummonMinion(const TaskMeta& serialized)
//	{
//		using SummonMinionTaskMeta = FlatData::SummonMinionTaskMeta;
//		SummonMinionTaskMeta meta = Serializer<SummonMinionTaskMeta>::Deserialize(serialized);
//
//		std::ostream& stream = LogWriter(m_users[meta.userID]) << "Summon Minion : ";
//		switch (meta.status)
//		{
//			case MetaData::SUMMON_SUCCESS:
//				stream << meta.card->GetName() << " at " << meta.index << std::endl;
//				break;
//
//			case MetaData::SUMMON_CARD_IDX_OUT_OF_RANGE:
//				stream << "Card index out of range of hand." << std::endl;
//				break;
//
//			case MetaData::SUMMON_NOT_ENOUGH_MANA:
//				stream << "Not enough mana" << std::endl;
//				break;
//
//			case MetaData::SUMMON_POSITION_OUT_OF_RANGE:
//				stream << "Position out of range of field" << std::endl;
//				break;
//		}
//	}
//
//	void GameInterface::HandleCombat(const TaskMeta& serialized)
//	{
//		using CombatTaskMeta = FlatData::CombatTaskMeta;
//		CombatTaskMeta meta = Serializer<CombatTaskMeta>::Deserialize(serialized);
//
//		LogWriter(m_users[meta.userID])
//				<< "Combat : {src " << meta.srcCard->GetName() << "} "
//				<< "vs {dst " << meta.dstCard->GetName() << "}" << std::endl;
//	}

	void GameInterface::HandleRequire(const TaskMeta& serialized)
	{
//		using RequireTaskMeta = FlatData::RequireTaskMeta;
//		RequireTaskMeta meta = Serializer<RequireTaskMeta>::Deserialize(serialized);
//
//		if (m_inputHandler.find(meta.required) != m_inputHandler.end())
//		{
//			m_inputHandler[meta.required](*this, meta);
//		}
	}

//	void GameInterface::HandleBrief(const TaskMeta& serialized)
//	{
//		using BriefTaskMeta = FlatData::BriefTaskMeta;
//		BriefTaskMeta meta = Serializer<BriefTaskMeta>::Deserialize(serialized);
//
//		m_briefCache = meta;
//
//		std::ostream& stream = LogWriter(m_users[meta.currentUser]) << "Game Briefing" << std::endl;
//
//		stream << m_users[meta.opponentUser]
//			   << " - Hero " << meta.opponentHero->GetName()
//			   << ", Health " << meta.opponentHero->GetHealth()
//			   << ", Mana " << static_cast<int>(meta.opponentMana)
//			   << ", Hand " << static_cast<int>(meta.numOpponentHand)
//			   << std::endl;
//
//		stream << m_users[meta.opponentUser] << " Field" << std::endl;
//		ShowCards(meta.opponentField, meta.numOpponentField);
//
//		stream << m_users[meta.currentUser]
//			   << " - Hero " << meta.currentHero->GetName()
//			   << ", Health " << meta.currentHero->GetHealth()
//			   << ", Mana " << static_cast<int>(meta.currentMana)
//			   << ", Hand " << static_cast<int>(meta.numCurrentHand)
//			   << std::endl;
//
//		stream << m_users[meta.currentUser] << " Field" << std::endl;
//		ShowCards(meta.currentField, meta.numCurrentField);
//
//		stream << m_users[meta.currentUser] << " Hand" << std::endl;
//		ShowCards(meta.currentHand, meta.numCurrentHand);
//	}
//
//	void GameInterface::InputSelectMenu(const FlatData::RequireTaskMeta& meta)
//	{
//		LogWriter(m_users[meta.userID]) << "Main Menu" << std::endl;
//		ShowMenus(m_mainMenuStr);
//
//		size_t input;
//		while (true)
//		{
//			m_ostream << "[*] Input menu : ";
//			m_istream >> input;
//
//			if (input > 0 && input <= GAME_MAIN_MENU_SIZE)
//			{
//				input -= 1;
//				break;
//			}
//		}
//
//		TaskMeta result(TaskID::SELECT_MENU, static_cast<TaskMetaTrait::status_t>(input));
//		m_agent.WriteSyncBuffer(Serializer<TaskMeta>::Serialize(result));
//	}
//
//	void GameInterface::InputSelectCard(const FlatData::RequireTaskMeta& meta)
//	{
//		LogWriter(m_users[meta.userID]) << "Select Card" << std::endl;
//
//		int in;
//		while (true)
//		{
//			m_ostream << "Select card index (0 ~ " << static_cast<int>(m_briefCache.numCurrentHand) - 1 << ") : ";
//
//			m_istream >> in;
//			if (in >= 0 && in < m_briefCache.numCurrentHand)
//			{
//				if(m_briefCache.currentHand[in]->GetCost() > m_briefCache.currentMana)
//				{
//					m_ostream << "Not enough mana" << std::endl;
//				}
//				else
//				{
//					break;
//				}
//			}
//		}
//
//		// if selected card type is minion
//		if (m_briefCache.currentHand[in]->GetCardType() == CardType::MINION)
//		{
//			int pos;
//			while (true)
//			{
//				m_ostream << "Select Position (0 ~ " << static_cast<int>(m_briefCache.numCurrentField) << ") : ";
//
//				m_istream >> pos;
//				if (pos >= 0 && pos <= m_briefCache.numCurrentField)
//				{
//					break;
//				}
//			}
//
//			FlatData::RequireSummonMinionTaskMeta minion;
//			minion.cardIndex = static_cast<BYTE>(in);
//			minion.position = static_cast<BYTE>(pos);
//
//			TaskMeta serialized = Serializer<FlatData::RequireSummonMinionTaskMeta>::Serialize(minion);
//			m_agent.WriteSyncBuffer(std::move(serialized));
//		}
//		else
//		{
//			// TODO : if not minion
//			m_agent.WriteSyncBuffer(TaskMeta());
//		}
//	}
//
//	void GameInterface::InputTargeting(const FlatData::RequireTaskMeta& meta)
//	{
//		LogWriter(m_users[meta.userID]) << "Targeting" << std::endl;
//
//		m_ostream << "User field : " << std::endl;
//		ShowCards(m_briefCache.currentField, m_briefCache.numCurrentField);
//
//		m_ostream << "Opponent field : " << std::endl;
//		ShowCards(m_briefCache.opponentField, m_briefCache.numOpponentField);
//
//		int src;
//		while (true)
//		{
//			m_ostream << "Select source minion (0 ~ " << static_cast<int>(m_briefCache.numCurrentField) - 1 << ") : ";
//
//			m_istream >> src;
//			if (src >= 0 && src < m_briefCache.numCurrentField)
//			{
//				Card** start = m_briefCache.currentAttacked;
//				Card** end = start + m_briefCache.numCurrentAttacked;
//				if (std::find(start, end, m_briefCache.currentField[src]) != end)
//				{
//					m_ostream << "Already attacked minion." << std::endl;
//				}
//				else
//				{
//					break;
//				}
//			}
//		}
//
//		int dst;
//		while (true)
//		{
//			m_ostream
//					<< "Select destination (0 for hero, 1 ~ "
//					<< static_cast<int>(m_briefCache.numOpponentField) << " for minion) : ";
//
//			m_istream >> dst;
//			if (dst >= 0 && dst <= m_briefCache.numOpponentField)
//			{
//				break;
//			}
//		}
//
//		FlatData::RequireTargetingTaskMeta targeting;
//		targeting.src = static_cast<BYTE>(src);
//		targeting.dst = static_cast<BYTE>(dst);
//
//		m_agent.WriteSyncBuffer(Serializer<FlatData::RequireTargetingTaskMeta>::Serialize(targeting));
//	}

	void GameInterface::HandleTaskTuple(const TaskMeta& serialized)
	{
		auto buffer = serialized.GetBuffer();
		auto metaVector = flatbuffers::GetRoot<FlatData::TaskMetaVector>(buffer.get());

		for (const auto& meta : *metaVector->vector())
		{
			HandleMessage(TaskMeta::ConvertFrom(meta));
		}
	}

//	void GameInterface::HandleGameEnd(const TaskMeta& serialized)
//	{
//		using GameEndTaskMeta = FlatData::GameEndTaskMeta;
//		GameEndTaskMeta meta = Serializer<GameEndTaskMeta>::Deserialize(serialized);
//
//		LogWriter(meta.winnerID) << "Win" << std::endl;
//	}
}