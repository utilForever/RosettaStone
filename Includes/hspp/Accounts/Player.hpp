// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_PLAYER_HPP
#define HEARTHSTONEPP_PLAYER_HPP

#include <hspp/Cards/Character.hpp>
#include <hspp/Cards/Deck.hpp>
#include <hspp/Cards/Entity.hpp>
#include <hspp/Cards/Hero.hpp>
#include <hspp/Cards/Spell.hpp>
#include <hspp/Policy/Policy.hpp>

#include <string>
#include <vector>

namespace Hearthstonepp
{
using BYTE = unsigned char;

class GameAgent;

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

    //! Returns player ID.
    //! \return Player ID.
    BYTE GetID() const;

    //! Sets player ID.
    //! \param id Player ID.
    void SetID(BYTE id);

    //! Returns player's hero.
    //! \return Player's hero.
    Hero* GetHero() const;

    //! Returns player's deck.
    //! \return Player's deck.
    std::vector<Entity*>& GetDeck();

    //! Returns player's field.
    //! \return Player's field.
    std::vector<Character*>& GetField();

    //! Returns player's hand.
    //! \return Player's hand.
    std::vector<Entity*>& GetHand();

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

    //! Returns the number of drawn card that causes fatigue after a player has
    //! exhausted their deck.
    //! \return The number of drawn card that causes fatigue after a player has
    //! exhausted their deck.
    BYTE GetNumCardAfterExhaust() const;

    //! Sets the number of drawn card that causes fatigue after a player has
    //! exhausted their deck.
    //! \param numCard The number of drawn card.
    void SetNumCardAfterExhaust(BYTE numCard);

    //! Returns the opponent player.
    //! \return The opponent player.
    Player& GetOpponent() const;

    //! Sets the opponent player.
    //! \param player The opponent player.
    void SetOpponent(Player* player);

    //! Sets the deck.
    //! \param deck A pointer to the deck.
    void SetDeck(Deck* deck);

    //! Adds hero and hero power.
    //! \param heroCard A card that represents hero.
    //! \param powerCard A card that represents hero power.
    void AddHeroAndPower(Card&& heroCard, Card&& powerCard);

    //! Returns game playing policy of current player.
    //! \return The policy of current player.
    IPolicy& GetPolicy() const;

   //! Sets game playing policy for current player.
   //! \param policy Policy for playing game.
    void SetPolicy(IPolicy* policy);

 private:
    //! Releases dynamic allocated resources.
    void FreeMemory();

    std::string m_nickname;
    BYTE m_id = 0;

    Hero* m_hero = nullptr;

    // Card storage
    std::vector<Entity*> m_deck;

    // Card objects
    std::vector<Character*> m_field;
    std::vector<Entity*> m_hand;
    std::vector<Spell*> m_playedSpell;
    std::vector<Character*> m_playedMinion;

    BYTE m_availableMana = 0;
    BYTE m_maximumMana = 0;
    BYTE m_numCardAfterExhaust = 0;

    Player* m_opponent = nullptr;
    IPolicy* m_policy = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_PLAYER_HPP
