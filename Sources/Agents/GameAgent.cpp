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

namespace Hearthstonepp
{
	GameAgent::GameAgent(User& user1, User& user2, int maxBufferSize) :
		m_userCurrent(user1), m_userOpponent(user2), m_bufferCapacity(maxBufferSize)
		, m_inBuffer(maxBufferSize), m_outBuffer(maxBufferSize), m_generator(m_rd())
	{
		// Do Nothing
	}

	GameAgent::GameAgent(User&& user1, User&& user2, int maxBufferSize) :
		m_userCurrent(std::move(user1)), m_userOpponent(std::move(user2)), m_bufferCapacity(maxBufferSize),
		m_inBuffer(maxBufferSize), m_outBuffer(maxBufferSize), m_generator(m_rd())
	{
		// Do Nothing
	}

	std::thread GameAgent::StartAgent(GameResult& result)
	{
		return std::thread([this](GameResult& result)
		{
			BeginPhase();

			while (!IsGameEnd())
			{
				MainPhase();
			}

			FinalPhase(result);
		}, std::ref(result));
	}

	void GameAgent::BeginPhase()
	{
		// userCurrent : user who start first
		// userOpponent : user who start later
		DecideDeckOrder();

		ShuffleDeck(m_userCurrent);
		ShuffleDeck(m_userOpponent);

		BeginDraw(m_userCurrent);
		BeginDraw(m_userOpponent);

		Mulligan(m_userCurrent);
		Mulligan(m_userOpponent);

		// TODO: Coin for later user
		m_userOpponent.hand.push_back(new Card());
	}

	void GameAgent::MainPhase()
	{
		MainDraw(m_userCurrent);
		ModifyMana(m_userCurrent, ManaModification::ADD, 1);
		
		BYTE i;
		scanf("%c\n", &i);

		std::swap(m_userCurrent, m_userOpponent);
	}

	void GameAgent::FinalPhase(GameResult& result)
	{
		BYTE end = static_cast<BYTE>(Step::FINAL_GAMEOVER);
		WriteOutputBuffer(&end, 1);
	}

	void GameAgent::DecideDeckOrder()
	{
		// get random number, zero or one.
		const std::uniform_int_distribution<int> bin(0, 1);
		if (bin(m_generator) == 1) // swap user with 50% probability
		{
			std::swap(m_userCurrent, m_userOpponent);
		}

		m_userCurrent.id = 0;
		m_userOpponent.id = 1;

		BeginFirstStructure data(m_userCurrent.userID, m_userOpponent.userID);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(BeginFirstStructure));
	}

	void GameAgent::ShuffleDeck(User& user)
	{
		std::vector<Card*>& deck = user.deck;
		std::shuffle(deck.begin(), deck.end(), m_generator); // shuffle with random generator

		BeginShuffleStructure data(user.id);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(BeginShuffleStructure));
	}

	void GameAgent::BeginDraw(User& user)
	{
		Draw(user, NUM_BEGIN_DRAW);

		Card** hand = user.hand.data();
		BYTE drawType = static_cast<BYTE>(Step::BEGIN_DRAW);
		DrawStructure data(drawType, user.id, NUM_BEGIN_DRAW, NUM_BEGIN_DRAW, hand);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(DrawStructure));
	}

	void GameAgent::Mulligan(User& user)
	{
		BeginMulliganStructure data(user.id);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(BeginMulliganStructure));

		BYTE index[NUM_BEGIN_DRAW] = { 0, };
		const int read = ReadInputBuffer(index, NUM_BEGIN_DRAW); // read index of the card to be mulligan

		std::vector<Card*>& deck = user.deck;
		std::vector<Card*>& hand = user.hand;

		std::sort(index, index + read, std::greater<int>());
		for (int i = 0; i < read; ++i)
		{
			deck.emplace_back(hand[index[i]]);
			hand.erase(hand.begin() + index[i]); // erase card with given index
		}

		std::shuffle(deck.begin(), deck.end(), m_generator);
		Draw(user, read);

		BYTE drawType = static_cast<BYTE>(Step::BEGIN_MULLIGAN);
		DrawStructure data2(drawType, user.id, read, NUM_BEGIN_DRAW, hand.data());
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data2), sizeof(DrawStructure)); // send new card data
	}

	void GameAgent::MainDraw(User& user)
	{
		Draw(user, 1);

		Card** hand = user.hand.data();
		BYTE drawType = static_cast<BYTE>(Step::MAIN_DRAW);
		DrawStructure data(drawType, user.id, 1, user.hand.size(), hand);
		WriteOutputBuffer(reinterpret_cast<BYTE*>(&data), sizeof(DrawStructure));
	}

	bool GameAgent::IsGameEnd()
	{
		
		int healthCurrent = m_userCurrent.hero->GetHealth();
		int healthOpponent = m_userOpponent.hero->GetHealth();

		if (healthCurrent < 1 || healthOpponent < 1)
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}

	void GameAgent::Draw(User& user, int num)
	{
		std::vector<Card*>& deck = user.deck;
		std::vector<Card*>& hand = user.hand;

		for (int i = 0; i < num; ++i)
		{
			hand.push_back(deck.back());
			deck.pop_back();
		}
	}

	void GameAgent::ModifyMana(User& user, ManaModification mod, int num)
	{
		if (mod == ManaModification::ADD)
		{
			user.mana += num;
		}
		else if (mod == ManaModification::SUB)
		{
			user.mana -= num;
		}
		else if (mod == ManaModification::SYNC)
		{
			user.mana = num;
		}

		if (user.mana > 10)
		{
			user.mana = 10;
		}
		else if (user.mana < 0)
		{
			user.mana = 0;
		}

		ModifyManaStructure modified(user.id, user.mana);
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
