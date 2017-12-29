/*************************************************************************
> File Name: GameAgent.cpp
> Project Name: Hearthstone++
> Author: Young-Joong Kim
> Purpose: Hearthstone Game Agent
> Created Time: 2017/09/26
> Copyright (c) 2017, Young-Joong Kim
*************************************************************************/
#include <Agents/GameAgent.h>
#include <Commons/Constants.h>

#include <algorithm>

namespace Hearthstonepp
{
	GameAgent::GameAgent(User& user1, User& user2, int maxBufferSize) :
		m_userCurrent(user1), m_userOpponent(user2), m_bufferCapacity(maxBufferSize)
		, m_inBuffer(maxBufferSize), m_outBuffer(maxBufferSize), m_generator(m_rd())
	{
		m_buffer = new BYTE[maxBufferSize];
	}

	GameAgent::GameAgent(User&& user1, User&& user2, int maxBufferSize) :
		m_userCurrent(std::move(user1)), m_userOpponent(std::move(user2)), m_bufferCapacity(maxBufferSize),
		m_inBuffer(maxBufferSize), m_outBuffer(maxBufferSize), m_generator(m_rd())
	{
		m_buffer = new BYTE[maxBufferSize];
	}

	std::thread GameAgent::StartAgent(GameResult& result)
	{
		return std::thread([this](GameResult& result)
		{
			BeginPhase();

			while (true)
			{
				const int result = MainPhase();
				if (result == GAME_END)
				{
					break;
				}
			}

			FinalPhase(result);
		}, std::ref(result));
	}

	void GameAgent::BeginPhase()
	{
		// userCurrent : user who start first
		// userOpponent : user who start later
		BeginFirst();

		BeginShuffle(m_userCurrent);
		BeginShuffle(m_userOpponent);

		BeginDraw(m_userCurrent);
		BeginDraw(m_userOpponent);

		BeginMulligan(m_userCurrent);
		BeginMulligan(m_userOpponent);

		// TODO: Coin for later user
		m_userOpponent.hand.push_back(new Card());
	}

	const int GameAgent::MainPhase()
	{
		MainReady(m_userCurrent);

		const int result = MainMenu(m_userCurrent, m_userOpponent);

		if (result == GAME_CONTINUE)
		{
			std::swap(m_userCurrent, m_userOpponent);
		}

		return result;
	}

	void GameAgent::FinalPhase(GameResult& result)
	{
		int winnerID = -1;
		std::string winner;

		if (m_userCurrent.hero->GetHealth() <= 0)
		{
			winner = m_userOpponent.userID;
			winnerID = m_userOpponent.id;
		}
		else
		{
			winner = m_userCurrent.userID;
			winnerID = m_userCurrent.id;
		}

		result.winner = winner;

		FinalGameOverStructure data(winnerID);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(FinalGameOverStructure));
	}

	void GameAgent::BeginFirst()
	{
		// get random number, zero or one.
		std::uniform_int_distribution<int> bin(0, 1);
		if (bin(m_generator) == 1) // swap user with 50% probability
		{
			std::swap(m_userCurrent, m_userOpponent);
		}

		m_userCurrent.id = 0;
		m_userOpponent.id = 1;

		BeginFirstStructure data(m_userCurrent.userID, m_userOpponent.userID);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(BeginFirstStructure));
	}

	void GameAgent::BeginShuffle(User& user)
	{
		std::vector<Card*>& deck = user.deck;
		std::shuffle(deck.begin(), deck.end(), m_generator); // shuffle with random generator

		BeginShuffleStructure data(user.id);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(BeginShuffleStructure));
	}

	void GameAgent::BeginDraw(User& user)
	{
		Draw(user, NUM_BEGIN_DRAW);

		BYTE drawType = static_cast<BYTE>(Step::BEGIN_DRAW);
		DrawStructure data(drawType, user.id, NUM_BEGIN_DRAW, user.hand.data());
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(DrawStructure));
	}

	void GameAgent::BeginMulligan(User& user)
	{
		BeginMulliganStructure data(user.id);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(BeginMulliganStructure));

		BYTE index[NUM_BEGIN_DRAW] = { 0, };
		const int read = ReadInputBuffer(index, NUM_BEGIN_DRAW); // read index of the card to be mulligan

		std::sort(index, index + read, std::greater<int>());
		if (index[0] >= NUM_BEGIN_DRAW)
		{
			throw std::runtime_error("Mulligan index should be under NUM_BEGIN_DRAW.");
		}

		for (int i = 1; i < read; ++i)
		{
			if (index[i] == index[i - 1])
			{
				throw std::runtime_error("Mulligan index should all be different.");
			}
		}

		std::vector<Card*>& deck = user.deck;
		std::vector<Card*>& hand = user.hand;

		for (int i = 0; i < read; ++i)
		{
			deck.emplace_back(hand[index[i]]);
			hand.erase(hand.begin() + index[i]); // erase card with given index
		}

		std::shuffle(deck.begin(), deck.end(), m_generator);
		Draw(user, read);

		BYTE drawType = static_cast<BYTE>(Step::BEGIN_MULLIGAN);
		DrawStructure data2(drawType, user.id, read, &*hand.end() - read);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data2), sizeof(DrawStructure)); // send new card data
	}

	void GameAgent::MainReady(User& user)
	{
		MainReadyStructure data(user.id);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(MainReadyStructure));

		MainDraw(user);
		ModifyMana(user, NumericModification::ADD, MANA_TOTAL, 1);
		ModifyMana(user, NumericModification::SYNC, MANA_EXIST, user.totalMana);

		user.attacked.clear();
	}

	void GameAgent::MainDraw(User& user)
	{
		int result = Draw(user, 1);
		if (result == DRAW_SUCCESS)
		{
			BYTE drawType = static_cast<BYTE>(Step::MAIN_DRAW);
			DrawStructure data(drawType, user.id, 1, &*user.hand.end() - 1);
			WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(DrawStructure));
		}	
	}

	const int GameAgent::MainMenu(User& user, User& enemy)
	{
		if (IsGameEnd())
		{
			return GAME_END;
		}

		GameBrief brief(
			user.id, enemy.id, user.existMana, enemy.existMana, 
			user.hand.size(), enemy.hand.size(), user.field.size(), enemy.field.size(),
			user.hero, enemy.hero,
			user.field.data(), user.hand.data(), enemy.field.data());

		WriteOutputBuffer(reinterpret_cast<BYTE*>(&brief), sizeof(GameBrief));

		MainMenuStructure data(user.id);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(MainMenuStructure));

		BYTE menu;
		ReadInputBuffer(&menu, 1);

		if (menu >= 0 && menu < GAME_MAIN_MENU_SIZE - 1)
		{
			m_mainMenuFuncs[menu](*this, user);
			return MainMenu(user, enemy);
		}
		else if (menu == GAME_MAIN_MENU_SIZE - 1)
		{
			MainEnd(user);
		}
		else
		{
			throw std::runtime_error("Main menu should be in range [0, GAME_MAIN_MENU_SIZE).");
		}

		return GAME_CONTINUE;
	}

	void GameAgent::MainUseCard(User& user)
	{
		MainUseCardStructure data(user.id, user.existMana, user.field.size(), user.hand.size(), user.hand.data());
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(MainUseCardStructure));

		ReadInputBuffer(m_buffer, m_bufferCapacity);

		if (m_buffer[0] == static_cast<BYTE>(CardType::MINION))
		{
			MainUseMinionStructure* minion = reinterpret_cast<MainUseMinionStructure*>(m_buffer);
			if (user.hand[minion->cardIndex]->GetCost() > user.existMana)
			{
				throw std::runtime_error("Cost of the card must be under or equal with user.existMana.");
			}

			if (minion->position < 0 || minion->position > user.field.size())
			{
				throw std::runtime_error("Minion position should be in range [0, user.field.size].");
			}

			if (minion->cardIndex < 0 || minion->cardIndex >= user.hand.size())
			{
				throw std::runtime_error("Card index should be in range [0, user.hand.size).");
			}

			user.attacked.emplace_back(user.hand[minion->cardIndex]);
			ModifyMana(user, NumericModification::SUB, MANA_EXIST, user.hand[minion->cardIndex]->GetCost());

			user.field.insert(user.field.begin() + minion->position, user.hand[minion->cardIndex]);
			user.hand.erase(user.hand.begin() + minion->cardIndex);
		}
	}

	void GameAgent::MainCombat(User& user)
	{
		User& opponent = GetOpponentOf(user);
		MainCombatStructure data(
			user.id, user.field.size(), opponent.field.size(), 
			user.field.data(), opponent.field.data());

		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(MainCombatStructure));

		ReadInputBuffer(m_buffer, sizeof(TargetingStructure));
		TargetingStructure* targeting = reinterpret_cast<TargetingStructure*>(m_buffer);

		int src = static_cast<int>(targeting->src);
		int dst = static_cast<int>(targeting->dst);

		if (src < 0 || src >= user.field.size())
		{
			throw std::runtime_error("Combat source index must be in range [0, user.field.size).");
		}

		std::vector<Card*>& attacked = user.attacked;
		if (std::find(attacked.begin(), attacked.end(), user.field[src]) != attacked.end())
		{
			throw std::runtime_error("Combat source minion couldn't attack dst.");
		}

		attacked.emplace_back(user.field[src]);

		if (dst < 0 || dst > opponent.field.size())
		{
			throw std::runtime_error("Combat target index must be in range [0, opponent.field.size].");
		}

		Card* source = user.field[src];
		Card* target = nullptr;
		if (dst == 0)
		{
			target = opponent.hero;
		}
		else
		{
			target = opponent.field[dst - 1];
		}

		int targetHurted = target->GetHealth() - source->GetAttack();
		target->SetHealth(targetHurted);

		if (targetHurted > 0)
		{
			ModifyHealthStructure modified(user.id, target);
			WriteOutputBuffer(reinterpret_cast<BYTE*>(&modified), sizeof(ModifyHealthStructure));
		}
		else if (dst != 0)
		{
			opponent.usedMinion.emplace_back(target);

			std::vector<Card*>& field = opponent.field;
			field.erase(field.begin() + dst - 1);

			ExhaustMinionStructure exhausted(user.id, target);
			WriteOutputBuffer(reinterpret_cast<BYTE*>(&exhausted), sizeof(ExhaustMinionStructure));
		}

		int sourceHurted = source->GetHealth() - target->GetAttack();
		source->SetHealth(sourceHurted);

		if (sourceHurted > 0)
		{
			ModifyHealthStructure modified(user.id, source);
			WriteOutputBuffer(reinterpret_cast<BYTE*>(&modified), sizeof(ModifyHealthStructure));
		}
		else
		{
			user.usedMinion.emplace_back(source);

			std::vector<Card*>& field = user.field;
			field.erase(field.begin() + src);

			ExhaustMinionStructure exhausted(user.id, source);
			WriteOutputBuffer(reinterpret_cast<BYTE*>(&exhausted), sizeof(ExhaustMinionStructure));
		}
	}

	void GameAgent::MainEnd(User& user)
	{
		MainEndStructure data(user.id);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(MainEndStructure));
	}

	User& GameAgent::GetOpponentOf(User& user)
	{
		if (user.id == m_userCurrent.id)
		{
			return m_userOpponent;
		}
		else
		{
			return m_userCurrent;
		}
	}

	bool GameAgent::IsGameEnd()
	{
		int healthCurrent = m_userCurrent.hero->GetHealth();
		int healthOpponent = m_userOpponent.hero->GetHealth();

		if (healthCurrent < 1 || healthOpponent < 1) {
			return true;
		}
		else {
			return false;
		}
	}

	int GameAgent::Draw(User& user, int num)
	{
		int result = DRAW_SUCCESS;
		std::vector<Card*>& deck = user.deck;
		std::vector<Card*>& hand = user.hand;

		if (deck.size() < num)
		{
			ExhaustDeckStructure data(user.id, num - deck.size());
			WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(ExhaustDeckStructure));

			for (int i = 1; i <= num - deck.size(); ++i)
			{
				int hurted = user.hero->GetHealth() - (user.exhausted + i);
				user.hero->SetHealth(hurted);

				ModifyHealthStructure data(user.id, user.hero);
				WriteOutputBuffer(reinterpret_cast<BYTE*>(&data),  sizeof(ModifyHealthStructure));
			}

			user.exhausted += num - deck.size();
			num = deck.size();

			result = DRAW_FAIL;
		}

		if (hand.size() + num > 10)
		{
			int over = hand.size() + num - 10;
			Card** burnt = new Card*[over];

			for (int i = 0; i < over; ++i)
			{
				burnt[i] = deck.back();
				deck.pop_back();
			}

			OverDrawStructure data(user.id, over, burnt);
			WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(OverDrawStructure));

			num = 10 - hand.size();
			result = DRAW_FAIL;
		}

		for (int i = 0; i < num; ++i)
		{
			hand.push_back(deck.back());
			deck.pop_back();
		}

		return result;
	}

	void GameAgent::ModifyMana(User& user, NumericModification mod, int type, int num)
	{
		auto getMana = [this](User& user, int type) -> int& {
			if (type == MANA_TOTAL)
				return user.totalMana;
			else
				return user.existMana;
		};

		int& mana = getMana(user, type);
		switch(mod)
		{
			case NumericModification::ADD:
				mana += num;
				break;
			case NumericModification::SUB:
				mana -= num;
				break;
			case NumericModification::SYNC:
				mana = num;
				break;
		}

		if (mana > 10) {
			mana = 10;
		}
		else if (mana < 0) {
			mana = 0;
		}

		ModifyManaStructure modified(user.id, mana);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&modified), sizeof(ModifyManaStructure));
	}

	int GameAgent::GetBufferCapacity() const
	{
		return m_bufferCapacity;
	}

	int GameAgent::ReadBuffer(BYTE* arr, int maxSize)
	{
		return m_outBuffer.ReadBuffer(arr, maxSize);
	}

	int GameAgent::WriteBuffer(BYTE* arr, int size)
	{
		return m_inBuffer.WriteBuffer(arr, size);
	}

	int GameAgent::ReadInputBuffer(BYTE* arr, int maxSize)
	{
		return m_inBuffer.ReadBuffer(arr, maxSize);
	}

	int GameAgent::WriteOutputBuffer(BYTE* arr, int size)
	{
		return m_outBuffer.WriteBuffer(arr, size);
	}
}
