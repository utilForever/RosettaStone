// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_PLAYER_HPP
#define HEARTHSTONEPP_PLAYER_HPP

#include <hspp/Commons/Constants.hpp>
#include <hspp/Models/Battlefield.hpp>
#include <hspp/Models/Deck.hpp>
#include <hspp/Models/Entity.hpp>
#include <hspp/Models/Graveyard.hpp>
#include <hspp/Models/Hand.hpp>
#include <hspp/Models/Hero.hpp>

#include <string>

namespace Hearthstonepp
{
class Game;
class IPolicy;

//!
//! \brief Player class.
//!
//! This class stores various information that used in Hearthstone game.
//! NOTE: This information should be used differently from the existing card
//! information because there are various effects on the card.
//!
class Player
{
 public:
    static constexpr std::size_t USER_INVALID = 255;

    //! Default constructor.
    Player();

    //! Destructor.
    ~Player();

    //! Copy constructor.
    Player(const Player& p) = delete;

    //! Move constructor.
    Player(Player&& p) = delete;

    //! Copy assignment operator.
    Player& operator=(const Player& p) = delete;

    //! Move assignment operator.
    Player& operator=(Player&& p) = delete;

    //! Returns player nickname.
    //! \return player nickname.
    std::string GetNickname() const;

    //! Sets player nickname.
    //! \param nickname player nickname.
    void SetNickname(std::string nickname);

    //! Returns player type.
    //! \return Player type.
    PlayerType GetPlayerType() const;

    //! Sets player type.
    //! \param type Player type.
    void SetPlayerType(PlayerType type);

    //! Returns player ID.
    //! \return Player ID.
    std::size_t GetID() const;

    //! Sets player ID.
    //! \param id Player ID.
    void SetID(std::size_t id);

    //! Returns a pointer to game.
    //! \return A pointer to game.
    Game* GetGame() const;

    //! Sets a pointer to game.
    //! \param game A pointer to game.
    void SetGame(Game* game);

    //! Returns player's battlefield.
    //! \return Player's battlefield.
    Battlefield& GetField();

    //! Returns player's deck.
    //! \return Player's deck.
    Deck& GetDeck();

    //! Returns player's graveyard.
    //! \return Player's graveyard.
    Graveyard& GetGraveyard();

    //! Returns player's hand.
    //! \return Player's hand.
    Hand& GetHand();

    //! Returns player's hero.
    //! \return Player's hero.
    Hero* GetHero() const;

    //! Returns game playing policy of current player.
    //! \return The policy of current player.
    IPolicy& GetPolicy() const;

    //! Sets game playing policy for current player.
    //! \param policy Policy for playing game.
    void SetPolicy(IPolicy* policy);

    //! Returns the opponent player.
    //! \return The opponent player.
    Player& GetOpponent() const;

    //! Sets the opponent player.
    //! \param player The opponent player.
    void SetOpponent(Player* player);

    //! Adds hero and hero power.
    //! \param heroCard A card that represents hero.
    //! \param powerCard A card that represents hero power.
    void AddHeroAndPower(Card&& heroCard, Card&& powerCard);

    std::size_t availableMana = 0;
    std::size_t maximumMana = 0;

 private:
    std::string m_nickname;
    PlayerType m_playerType = PlayerType::PLAYER1;
    std::size_t m_id = 0;

    Battlefield m_field;
    Deck m_deck;
    Graveyard m_graveyard;
    Hand m_hand;

    Hero* m_hero = nullptr;

    Game* m_game = nullptr;
    IPolicy* m_policy = nullptr;
    Player* m_opponent = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_PLAYER_HPP
