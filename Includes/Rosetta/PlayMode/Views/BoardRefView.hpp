// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_BOARD_REF_VIEW_HPP
#define ROSETTASTONE_PLAYMODE_BOARD_REF_VIEW_HPP

#include <Rosetta/PlayMode/Actions/ActionValidGetter.hpp>
#include <Rosetta/PlayMode/Games/Game.hpp>

namespace RosettaStone::PlayMode
{
//!
//! \brief BoardRefView class.
//!
//! This class considers when a particular player looks at a game
//! from his or her point of view.
//!
class BoardRefView
{
 public:
    //! Constructs board with given \p game and \p playerType.
    //! \param game The game context.
    //! \param playerType The player type of the board.
    BoardRefView(Game& game, PlayerType playerType);

    //! Returns the side of the view.
    //! \return The side of the view.
    PlayerType GetSide() const;

    //! Returns the current turn of the game.
    //! \return The current turn of the game.
    int GetTurn() const;

    //! Returns the current player of the game.
    //! \return The current player of the game.
    PlayerType GetCurrentPlayer() const;

    //! Returns the fatigue damage of the player in the current status.
    //! \param playerType The player type to separate players.
    //! \return The fatigue damage of the player in the current status.
    int GetFatigueDamage(PlayerType playerType) const;

    //! Returns the total mana of the player during this turn.
    //! \param playerType The player type to separate players.
    //! \return The total mana of the player during this turn.
    int GetTotalMana(PlayerType playerType) const;

    //! Returns the used mana of the player during this turn.
    //! \param playerType The player type to separate players.
    //! \return The used mana of the player during this turn.
    int GetUsedMana(PlayerType playerType) const;

    //! Returns the temporary mana of the player during this turn.
    //! \param playerType The player type to separate players.
    //! \return The temporary mana of the player during this turn.
    int GetTemporaryMana(PlayerType playerType) const;

    //! Returns the mana that is overload owed of the player during this turn.
    //! \param playerType The player type to separate players.
    //! \return The mana that is overload owed of the player during this turn.
    int GetOverloadOwed(PlayerType playerType) const;

    //! Returns the mana that is overload locked of the player during this turn.
    //! \param playerType The player type to separate players.
    //! \return The mana that is overload locked of the player during this turn.
    int GetOverloadLocked(PlayerType playerType) const;

    //! Returns the remaining mana of the player during this turn.
    //! \param playerType The player type to separate players.
    //! \return The remaining mana of the player during this turn.
    int GetRemainingMana(PlayerType playerType) const;

    //! Returns the hero of the current player.
    //! \return The hero of the current player.
    Hero* GetHero() const;

    //! Returns the hero of the opponent player.
    //! \return The hero of the opponent player.
    Hero* GetOpponentHero() const;

    //! Returns the hero power of the player.
    //! \param playerType The player type to separate players.
    //! \return The hero power of the player.
    HeroPower& GetHeroPower(PlayerType playerType) const;

    //! Returns the weapon of the player.
    //! \param playerType The player type to separate players.
    //! \return The weapon of the player.
    Weapon* GetWeapon(PlayerType playerType) const;

    //! Returns a list of cards in the hand of the current player.
    //! \return A list of cards in the hand of the current player.
    std::vector<Playable*> GetHandCards() const;

    //! Returns a list of cards in the hand of the opponent player.
    //! \return A list of cards in the hand of the opponent player.
    std::vector<std::pair<Playable*, bool>> GetOpponentHandCards() const;

    //! Returns the number of cards in the hand of the opponent player.
    //! \return The number of cards in the hand of the opponent player.
    int GetOpponentHandCardCount() const;

    //! Returns a list of minions in the field of the player.
    //! \param playerType The player type to separate players.
    //! \return A list of minions in the field of the player.
    std::vector<Minion*> GetMinions(PlayerType playerType) const;

    //! Returns the number of cards in the deck of the player.
    //! \param playerType The player type to separate players.
    //! \return The number of cards in the deck of the player.
    int GetDeckCardCount(PlayerType playerType) const;

    //! Returns the flag indicates that whether the hero can attack.
    //! \param playerType The player type to separate players.
    //! \return The flag indicates that whether the hero can attack.
    bool IsHeroAttackable(PlayerType playerType) const;

    //! Returns the flag indicates that whether the minion can attack.
    //! \param playerType The player type to separate players.
    //! \param idx The index of minion in the field.
    //! \return The flag indicates that whether the minion can attack.
    bool IsMinionAttackable(PlayerType playerType, int idx) const;

    //! Runs \p functor on each minion of the player.
    //! \param playerType The player type to separate players.
    //! \param functor A function to run for each minion.
    template <typename Functor>
    void ForEachMinion(PlayerType playerType, Functor&& functor) const
    {
        auto fieldZone = (playerType == PlayerType::PLAYER1)
                             ? m_game.GetPlayer1()->GetFieldZone()
                             : m_game.GetPlayer2()->GetFieldZone();

        for (auto& minion : fieldZone->GetAll())
        {
            functor(minion);
        }
    }

    //! Runs \p functor on each card in the current player's hand.
    //! \param functor A function to run for each card.
    template <typename Functor>
    void ForEachCurHandCard(Functor&& functor) const
    {
        auto handZone = (GetCurrentPlayer() == PlayerType::PLAYER1)
                            ? m_game.GetPlayer1()->GetHandZone()
                            : m_game.GetPlayer2()->GetHandZone();

        for (auto& entity : handZone->GetAll())
        {
            functor(entity->card->id);
        }
    }

    //! Runs \p functor on each card in the opponent player's hand.
    //! \param functor A function to run for each card.
    template <typename Functor>
    void ForEachOpHandCard(Functor&& functor) const
    {
        auto handZone = (GetCurrentPlayer() == PlayerType::PLAYER1)
                            ? m_game.GetPlayer2()->GetHandZone()
                            : m_game.GetPlayer1()->GetHandZone();

        for (auto& entity : handZone->GetAll())
        {
            std::string cardID = entity->card->id;
            if (cardID == "GAME_005")
            {
                // Do nothing
            }
            else
            {
                cardID = INVALID_CARD_ID;
            }

            functor(cardID);
        }
    }

 private:
    Game& m_game;
    PlayerType m_playerType;
};

//!
//! \brief CurrentPlayerBoardRefView class.
//!
//! This class is BoardRefView-like class for the current player.
//!
class CurrentPlayerBoardRefView
{
 public:
    //! Constructs current player board ref view with given \p game.
    //! \param game The game context.
    explicit CurrentPlayerBoardRefView(Game& game);

    //! Returns the current player of the game.
    //! \return The current player of the game.
    Player* GetCurrentPlayer() const;

    //! Returns the action valid getter.
    //! \return The action valid getter.
    ActionValidGetter GetActionValidGetter() const;

 private:
    Game& m_game;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_BOARD_REF_VIEW_HPP
