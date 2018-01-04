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
				const unsigned int continuity = MainPhase();
				if (continuity == GAME_END)
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

	unsigned int GameAgent::MainPhase()
	{
		// Ready for main phase
		MainReady(m_userCurrent);

		// Get game status from method MainMenu
		const unsigned int result = MainMenu(m_userCurrent, m_userOpponent);

		if (result == GAME_CONTINUE)
		{
			// swap user
			std::swap(m_userCurrent, m_userOpponent);
		}

		return result;
	}

	void GameAgent::FinalPhase(GameResult& result)
	{
		BYTE winnerUserID = 255;
		std::string winner;

		if (m_userCurrent.hero->GetHealth() <= 0)
		{
			winner = m_userOpponent.userID;
			winnerUserID = m_userOpponent.id;
		}
		else
		{
			winner = m_userCurrent.userID;
			winnerUserID = m_userCurrent.id;
		}

		// return GameResult structure
		result.winnerUserID = winner;

		// Output FinalGameOverStructure to interface
		FinalGameOverStructure data(winnerUserID);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(FinalGameOverStructure));
	}

	void GameAgent::BeginFirst()
	{
		// get random number, zero or one.
		std::uniform_int_distribution<int> bin(0, 1);
		// swap user with 50% probability
		if (bin(m_generator) == 1) 
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
		// shuffle with random generator
		std::shuffle(deck.begin(), deck.end(), m_generator);

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
		// read index of the card to be mulligan
		const size_t read = ReadInputBuffer(index, NUM_BEGIN_DRAW); 

		std::sort(index, index + read, std::greater<int>());
		if (index[0] >= NUM_BEGIN_DRAW)
		{
			// Mulligan index must be in range 0 to hand size
			throw std::runtime_error("Mulligan index should be under NUM_BEGIN_DRAW.");
		}

		for (size_t i = 1; i < read; ++i)
		{
			if (index[i] == index[i - 1])
			{
				// avoid index overlaping
				throw std::runtime_error("Mulligan index should all be different.");
			}
		}

		std::vector<Card*>& deck = user.deck;
		std::vector<Card*>& hand = user.hand;

		for (size_t i = 0; i < read; ++i)
		{
			// back to deck
			deck.emplace_back(hand[index[i]]);
			// erase card with given index
			hand.erase(hand.begin() + index[i]); 
		}

		std::shuffle(deck.begin(), deck.end(), m_generator);
		Draw(user, read);

		BYTE drawType = static_cast<BYTE>(Step::BEGIN_MULLIGAN);
		// pass only drawn cards, not existing card
		DrawStructure data2(drawType, user.id, static_cast<BYTE>(read), &*hand.end() - read);
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
		const unsigned int result = Draw(user, 1);
		// for over draw or exhausted deck
		if (result == DRAW_SUCCESS)
		{
			BYTE drawType = static_cast<BYTE>(Step::MAIN_DRAW);
			DrawStructure data(drawType, user.id, 1, &*user.hand.end() - 1);
			WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(DrawStructure));
		}	
	}

	unsigned int GameAgent::MainMenu(User& user, User& enemy)
	{
		// Check before starting main phase
		if (IsGameEnd())
		{
			return GAME_END;
		}

		GameBrief brief(
			user.id, enemy.id, user.existMana, enemy.existMana, 
			static_cast<BYTE>(user.hand.size()), 
			static_cast<BYTE>(enemy.hand.size()), 
			static_cast<BYTE>(user.field.size()), 
			static_cast<BYTE>(enemy.field.size()),
			user.hero, enemy.hero,
			user.field.data(), user.hand.data(), enemy.field.data());

		WriteOutputBuffer(reinterpret_cast<BYTE*>(&brief), sizeof(GameBrief));

		MainMenuStructure data(user.id);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(MainMenuStructure));

		BYTE menu;
		// Read index of the menu table, m_mainMenuFuncs
		ReadInputBuffer(&menu, 1);

		if (menu >= 0 && menu < GAME_MAIN_MENU_SIZE - 1)
		{
			// call action methods, like UseCard or Combat
			m_mainMenuFuncs[menu](*this, user);
			// call recursively for next action until user enter MainEnd menu
			return MainMenu(user, enemy);
		}
		else if (menu == GAME_MAIN_MENU_SIZE - 1)
		{
			MainEnd(user);
		}
		else
		{
			// menu index must be in range 0 to size of m_mainMenuFuncs
			throw std::runtime_error("Main menu should be in range [0, GAME_MAIN_MENU_SIZE).");
		}

		return GAME_CONTINUE;
	}

	void GameAgent::MainUseCard(User& user)
	{
		MainUseCardStructure data(
			user.id, user.existMana, 
			static_cast<BYTE>(user.field.size()), 
			static_cast<BYTE>(user.hand.size()), 
			user.hand.data());
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(MainUseCardStructure));

		// Read what kinds of card user wants to use
		ReadInputBuffer(m_buffer, m_bufferCapacity);

		if (m_buffer[0] == static_cast<BYTE>(CardType::MINION))
		{
			MainUseMinionStructure* minion = reinterpret_cast<MainUseMinionStructure*>(m_buffer);
			if (user.hand[minion->cardIndex]->GetCost() > user.existMana)
			{
				// requested mana of minion must be under or equal with user's exist mana
				throw std::runtime_error("Cost of the card must be under or equal with user.existMana.");
			}

			if (minion->position < 0 || minion->position > user.field.size())
			{
				// position of the minion must be in range of field size of user
				throw std::runtime_error("Minion position should be in range [0, user.field.size].");
			}

			if (minion->cardIndex < 0 || minion->cardIndex >= user.hand.size())
			{
				// minion card must be in user's hand
				throw std::runtime_error("Card index should be in range [0, user.hand.size).");
			}

			// summoned minion must be rest at that turn
			user.attacked.emplace_back(user.hand[minion->cardIndex]);
			BYTE cost = static_cast<BYTE>(user.hand[minion->cardIndex]->GetCost());
			ModifyMana(user, NumericModification::SUB, MANA_EXIST, cost);

			// summon minion on the field
			user.field.insert(user.field.begin() + minion->position, user.hand[minion->cardIndex]);
			// erase from user's hand
			user.hand.erase(user.hand.begin() + minion->cardIndex);
		}
	}

	void GameAgent::MainCombat(User& user)
	{
		User& opponent = GetOpponentOf(user);
		MainCombatStructure data(
			user.id, 
			static_cast<BYTE>(user.field.size()), 
			static_cast<BYTE>(opponent.field.size()), 
			static_cast<BYTE>(user.attacked.size()),
			user.field.data(), opponent.field.data(), user.attacked.data());

		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(MainCombatStructure));

		// read combating minion and target minion
		ReadInputBuffer(m_buffer, sizeof(TargetingStructure));
		TargetingStructure* targeting = reinterpret_cast<TargetingStructure*>(m_buffer);

		size_t src = static_cast<size_t>(targeting->src);
		size_t dst = static_cast<size_t>(targeting->dst);

		if (src >= user.field.size())
		{
			// source minion must be in field
			throw std::runtime_error("Combat source index must be in range [0, user.field.size).");
		}

		std::vector<Card*>& attacked = user.attacked;
		if (std::find(attacked.begin(), attacked.end(), user.field[src]) != attacked.end())
		{
			// minion already attacked couldn't be a source of combat action
			throw std::runtime_error("Combat source minion couldn't attack dst.");
		}

		attacked.emplace_back(user.field[src]);

		// if dst == 0 then destination is hero else minion
		if (dst > opponent.field.size())
		{
			// destinted minion must be in field or hero
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

		// processing target hurted by source's attack
		if (source->GetAttack() > 0)
		{
			int targetHurted = target->GetHealth() - source->GetAttack();
			target->SetHealth(targetHurted);

			// if target is not exhausted
			if (targetHurted > 0)
			{
				ModifyHealthStructure modified(user.id, target);
				WriteOutputBuffer(reinterpret_cast<BYTE*>(&modified), sizeof(ModifyHealthStructure));
			}
			// if target is exhausted, but target is not hero
			// if target is hero, processing is not necessary, because game is end
			else if (dst != 0)
			{
				opponent.usedMinion.emplace_back(target);

				std::vector<Card*>& field = opponent.field;
				field.erase(field.begin() + dst - 1);

				ExhaustMinionStructure exhausted(user.id, target);
				WriteOutputBuffer(reinterpret_cast<BYTE*>(&exhausted), sizeof(ExhaustMinionStructure));
			}
		}

		// processing source hurted by target's attack
		if (target->GetAttack() > 0)
		{
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

	unsigned int GameAgent::Draw(User& user, int num)
	{
		unsigned int result = DRAW_SUCCESS;
		std::vector<Card*>& deck = user.deck;
		std::vector<Card*>& hand = user.hand;

		size_t size = num;

		// when deck is exhausted
		if (deck.size() < size)
		{
			size_t rest = size - deck.size();
			ExhaustDeckStructure data(user.id, static_cast<BYTE>(rest));
			WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(ExhaustDeckStructure));

			// processing damage by exhausting
			for (size_t i = 1; i <= rest; ++i)
			{
				int hurted = user.hero->GetHealth() - (user.exhausted + i);
				user.hero->SetHealth(hurted);

				ModifyHealthStructure health(user.id, user.hero);
				WriteOutputBuffer(reinterpret_cast<BYTE*>(&health),  sizeof(ModifyHealthStructure));
			}

			user.exhausted += static_cast<BYTE>(rest);
			// calculating rest deck size
			size = deck.size();

			// full draw is fail
			result = DRAW_FAIL;
		}

		// when hand size over 10, over draw
		if (hand.size() + size > 10)
		{	
			// number of over draw
			size_t over = hand.size() + size - 10;
			Card** burnt = new Card*[over];

			for (size_t i = 0; i < over; ++i)
			{
				burnt[i] = deck.back();
				deck.pop_back();
			}

			// passing over draw cards
			OverDrawStructure data(user.id, static_cast<BYTE>(over), burnt);
			WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(OverDrawStructure));

			size = 10 - hand.size();
			// draw is fail
			result = DRAW_FAIL;
		}

		for (size_t i = 0; i < size; ++i)
		{
			hand.push_back(deck.back());
			deck.pop_back();
		}

		return result;
	}

	void GameAgent::ModifyMana(User& user, NumericModification mod, unsigned int type, BYTE num)
	{
		auto getMana = [this](User& user, unsigned int type) -> BYTE& {
			if (type == MANA_TOTAL)
				return user.totalMana;
			else
				return user.existMana;
		};

		BYTE& mana = getMana(user, type);
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

		// over mana
		if (mana > 10) {
			mana = 10;
		}
		// under mana
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

	size_t GameAgent::ReadBuffer(BYTE* arr, size_t maxSize)
	{
		return m_outBuffer.ReadBuffer(arr, maxSize);
	}

	size_t GameAgent::WriteBuffer(BYTE* arr, size_t size)
	{
		return m_inBuffer.WriteBuffer(arr, size);
	}

	size_t GameAgent::ReadInputBuffer(BYTE* arr, size_t maxSize)
	{
		return m_inBuffer.ReadBuffer(arr, maxSize);
	}

	size_t GameAgent::WriteOutputBuffer(BYTE* arr, size_t size)
	{
		return m_outBuffer.WriteBuffer(arr, size);
	}
}
