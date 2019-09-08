// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_GAME_RESTORER_HPP
#define ROSETTASTONE_GAME_RESTORER_HPP

#include <Rosetta/Views/BoardView.hpp>

namespace RosettaStone
{
//!
//! \brief GameRestorer class.
//!
class GameRestorer
{
 public:
    GameRestorer(const BoardView& view);

    static GameRestorer Prepare(BoardView& view,
                                Views::Types::UnknownCardsInfo& p1Unknown,
                                Views::Types::UnknownCardsInfo& p2Unknown);

    Game* RestoreGame();

 private:
    void MakePlayer(
        PlayerType playerType, Game& game,
        const Views::Types::Player& viewPlayer,
        const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager);

    void MakeHeroAndHeroPower(PlayerType playerType, Game& game,
                              const Views::Types::Hero& hero,
                              const Views::Types::HeroPower& heroPower);

    void MakeDeck(
        PlayerType playerType, Game& game,
        std::vector<Views::Types::CardInfo> cards,
        const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager);

    void MakeHand(
        PlayerType playerType, Game& game,
        std::vector<Views::Types::CardInfo> cards,
        const Views::Types::UnknownCardsSetsManager& unknownCardsSetsManager);

    void MakeMinions(PlayerType playerType, Game& game,
                     const Views::Types::Minions& minions);

    void MakeManaCrystal(Player& player,
                         const Views::Types::ManaCrystal& manaCrystal);

    void AddMinion(PlayerType playerType, Game& game,
                   const Views::Types::Minion& minion, int pos);

    const BoardView& m_view;

    Views::Types::UnknownCardsInfo p1UnknownCardsInfo;
    Views::Types::UnknownCardsInfo p2UnknownCardsInfo;

    Views::Types::UnknownCardsSetsManager p1UnknownCardsManager;
    Views::Types::UnknownCardsSetsManager p2UnknownCardsManager;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_GAME_RESTORER_HPP
