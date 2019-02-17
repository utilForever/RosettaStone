// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_PLAYER_HPP
#define HEARTHSTONEPP_PLAYER_HPP

#include <hspp/Accounts/DeckInfo.hpp>
#include <hspp/Commons/Constants.hpp>
#include <hspp/Models/Battlefield.hpp>
#include <hspp/Models/Character.hpp>
#include <hspp/Models/Deck.hpp>
#include <hspp/Models/Entity.hpp>
#include <hspp/Models/Hand.hpp>
#include <hspp/Models/Hero.hpp>
#include <hspp/Models/Spell.hpp>

#include <string>
#include <vector>

namespace Hearthstonepp
{
using BYTE = unsigned char;

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
    static constexpr BYTE USER_INVALID = 255;

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
    BYTE GetID() const;

    //! Sets player ID.
    //! \param id Player ID.
    void SetID(BYTE id);

    //! Returns a pointer to game.
    //! \return A pointer to game.
    Game* GetGame() const;

    //! Sets a pointer to game.
    //! \param game A pointer to game.
    void SetGame(Game* game);

    //! Returns player's hero.
    //! \return Player's hero.
    Hero* GetHero() const;

    //! Returns player's battlefield.
    //! \return Player's battlefield.
    Battlefield& GetField();

    //! Returns player's deck.
    //! \return Player's deck.
    Deck& GetDeck();

    //! Returns player's hand.
    //! \return Player's hand.
    Hand& GetHand();

    //! Returns available mana that player has.
    //! \return Available mana that player has.
    BYTE GetAvailableMana() const;

    //! Sets available mana that player has.
    //! \param mana Available mana that player has.
    void SetAvailableMana(BYTE mana);

    //! Returns maximum mana that player has.
    //! \return Maximum mana that player has.
    BYTE GetMaximumMana() const;

    //! Sets maximum mana that player has.
    //! \param mana Maximum mana that player has.
    void SetMaximumMana(BYTE mana);

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

 private:
    //! Releases dynamic allocated resources.
    void FreeMemory();

    std::string m_nickname;
    PlayerType m_playerType = PlayerType::PLAYER1;
    BYTE m_id = 0;

    Hero* m_hero = nullptr;

    // Card storage
    Deck m_deck;

    // Card objects
    Battlefield m_field;
    Hand m_hand;
    std::vector<Spell*> m_playedSpell;
    std::vector<Character*> m_playedMinion;

    BYTE m_availableMana = 0;
    BYTE m_maximumMana = 0;

    Game* m_game = nullptr;
    IPolicy* m_policy = nullptr;
    Player* m_opponent = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_PLAYER_HPP
