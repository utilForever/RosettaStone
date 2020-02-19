// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#include <Rosetta/Games/GameRestorer.hpp>

namespace RosettaStone
{
GameRestorer::GameRestorer(const BoardView& view) : m_view(view)
{
    // Do nothing
}

GameRestorer GameRestorer::Prepare(BoardView& view,
                                   Views::Types::UnknownCardsInfo& p1Unknown,
                                   Views::Types::UnknownCardsInfo& p2Unknown)
{
    GameRestorer restorer(view);

    restorer.p1UnknownCardsManager.Setup(p1Unknown.unknownCardsSets);
    restorer.p2UnknownCardsManager.Setup(p2Unknown.unknownCardsSets);

    return restorer;
}

GameState GameRestorer::RestoreGameState()
{
    p1UnknownCardsManager.Prepare();
    p2UnknownCardsManager.Prepare();

    GameState gameState;
    MakePlayer(gameState.GetPlayerInfo(PlayerType::PLAYER1), gameState,
               m_view.GetPlayer1(), p1UnknownCardsManager);
    MakePlayer(gameState.GetPlayerInfo(PlayerType::PLAYER2), gameState,
               m_view.GetPlayer2(), p2UnknownCardsManager);
    gameState.SetCurrentPlayer(m_view.GetCurrentPlayer());
    gameState.SetTurn(m_view.GetTurn());

    return gameState;
}

void GameRestorer::MakePlayer(
    GameState::PlayerInfo& info, GameState& gameState,
    const Views::Types::Player& viewPlayer,
    const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager)
{
    MakeHeroAndHeroPower(info, viewPlayer.hero, viewPlayer.heroPower);
    MakeDeck(info, viewPlayer.deck, unknownCardsSetsManager);
    MakeHand(info, viewPlayer.hand, unknownCardsSetsManager);
    MakeMinions(info, viewPlayer.minions);

    info.gameTags.emplace(GameTag::FATIGUE, viewPlayer.fatigue);
    MakeManaCrystal(info, viewPlayer.manaCrystal);
}

void GameRestorer::MakeHeroAndHeroPower(
    GameState::PlayerInfo& info, const Views::Types::Hero& hero,
    const Views::Types::HeroPower& heroPower)
{
    info.hero.cardID = hero.cardID;
    info.heroPower.cardID = heroPower.cardID;

    info.hero.gameTags.emplace(GameTag::ATK, hero.attack);
    info.hero.gameTags.emplace(GameTag::DAMAGE, hero.maxHealth - hero.health);
    info.hero.gameTags.emplace(GameTag::HEALTH, hero.maxHealth);
    info.hero.gameTags.emplace(GameTag::ARMOR, hero.armor);
    info.hero.gameTags.emplace(GameTag::EXHAUSTED, hero.isExhausted);

    info.heroPower.gameTags.emplace(GameTag::EXHAUSTED, heroPower.isExhausted);
}

void GameRestorer::MakeDeck(
    GameState::PlayerInfo& info, std::vector<Views::Types::CardInfo> cards,
    const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager)
{
    for (const auto& card : cards)
    {
        const std::string cardID = card.GetCardID(unknownCardsSetsManager);

        GameState::GameStateInfo cardInfo;
        cardInfo.cardID = cardID;

        info.deck.emplace_back(cardInfo);
    }
}

void GameRestorer::MakeHand(
    GameState::PlayerInfo& info, std::vector<Views::Types::CardInfo> cards,
    const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager)
{
    for (const auto& card : cards)
    {
        const std::string cardID = card.GetCardID(unknownCardsSetsManager);

        GameState::GameStateInfo cardInfo;
        cardInfo.cardID = cardID;

        info.hand.emplace_back(cardInfo);
    }
}

void GameRestorer::MakeMinions(GameState::PlayerInfo& info,
                               const Views::Types::Minions& minions)
{
    for (const auto& minion : minions.minions)
    {
        AddMinion(info, minion);
    }
}

void GameRestorer::MakeManaCrystal(GameState::PlayerInfo& info,
                                   const Views::Types::ManaCrystal& manaCrystal)
{
    info.gameTags.emplace(GameTag::RESOURCES_USED, manaCrystal.used);
    info.gameTags.emplace(GameTag::RESOURCES, manaCrystal.total);
    info.gameTags.emplace(GameTag::OVERLOAD_OWED, manaCrystal.overloadOwed);
    info.gameTags.emplace(GameTag::OVERLOAD_LOCKED, manaCrystal.overloadLocked);
}

void GameRestorer::AddMinion(GameState::PlayerInfo& info,
                             const Views::Types::Minion& minion)
{
    GameState::GameStateInfo cardInfo;
    cardInfo.cardID = minion.cardID;
    cardInfo.gameTags.emplace(GameTag::ATK, minion.attack);
    cardInfo.gameTags.emplace(GameTag::DAMAGE,
                              minion.maxHealth - minion.health);
    cardInfo.gameTags.emplace(GameTag::HEALTH, minion.maxHealth);
    cardInfo.gameTags.emplace(GameTag::SPELLPOWER, minion.spellPower);
    cardInfo.gameTags.emplace(GameTag::EXHAUSTED, minion.isExhausted);
}
}  // namespace RosettaStone