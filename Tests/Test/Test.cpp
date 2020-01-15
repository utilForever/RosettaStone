#include <Rosetta/Commons/Macros.hpp>

#if defined(ROSETTASTONE_WINDOWS)
#include <crtdbg.h>
#include <tchar.h>

#include <Rosetta/Actions/ActionParams.hpp>
#include <Rosetta/Cards/Cards.hpp>
#include <Rosetta/Commons/DeckCode.hpp>
#include <Rosetta/Games/Game.hpp>
#include <Rosetta/Games/GameConfig.hpp>
#include <Rosetta/Games/GameManager.hpp>
#include <Rosetta/Tasks/PlayerTasks/AttackTask.hpp>
#include <Rosetta/Views/Board.hpp>

#include <effolkronium/random.hpp>

using Random = effolkronium::random_static;

using namespace RosettaStone;
using namespace PlayerTasks;

class TestActionParams : public ActionParams
{
 public:
    TestActionParams() = default;

    TestActionParams(const TestActionParams&) = delete;
    TestActionParams(TestActionParams&&) noexcept = delete;

    TestActionParams& operator=(const TestActionParams&) = delete;
    TestActionParams& operator=(TestActionParams&&) noexcept = delete;

    void Init(const Board& board)
    {
        m_board = &board;
        Initialize(m_board->GetCurPlayerStateRefView().GetActionValidGetter());
    }

    std::size_t GetNumber(ActionType actionType, ActionChoices& choices) final
    {
        if (actionType != ActionType::MAIN_ACTION)
        {
            if (choices.Size() == 1)
            {
                return choices.Get(0);
            }
        }

        const std::size_t count = choices.Size();
        const auto randIdx = Random::get<std::size_t>(0, count - 1);
        const int result = static_cast<int>(randIdx);

        return result;
    }

 private:
    const Board* m_board = nullptr;
};

#ifdef _DEBUG
#define new new (_CLIENT_BLOCK, __FILE__, __LINE__)
#endif

int _tmain(int argc, _TCHAR* argv[])
{
    Cards::GetInstance();

    GameConfig config;
    config.player1Class = CardClass::WARLOCK;
    config.player2Class = CardClass::ROGUE;
    config.startPlayer = PlayerType::PLAYER1;
    config.doShuffle = false;
    config.doFillDecks = false;
    config.skipMulligan = true;
    config.autoRun = true;

    const std::string INNKEEPER_EXPERT_WARLOCK =
        "AAEBAfqUAwAPMJMB3ALVA9AE9wTOBtwGkgeeB/sHsQjCCMQI9ggA";
    auto deck = DeckCode::Decode(INNKEEPER_EXPERT_WARLOCK).GetCardIDs();

    for (std::size_t j = 0; j < deck.size(); ++j)
    {
        config.player1Deck[j] = *Cards::FindCardByID(deck[j]);
        config.player2Deck[j] = *Cards::FindCardByID(deck[j]);
    }

    Game game(config);
    game.Start();
    game.MainReady();

    Player* curPlayer = game.GetCurrentPlayer();
    Player* opPlayer = game.GetOpponentPlayer();
    curPlayer->SetTotalMana(10);
    curPlayer->SetUsedMana(0);
    opPlayer->SetTotalMana(10);
    opPlayer->SetUsedMana(0);

    while (game.state != State::COMPLETE)
    {
        TestActionParams params;
        Board board(game, game.GetCurrentPlayer()->playerType);

        params.Init(board);
        board.ApplyAction(params);
    }

    return 0;
}
#else
int main(int argc, char* argv[])
{
    return 0;
}
#endif