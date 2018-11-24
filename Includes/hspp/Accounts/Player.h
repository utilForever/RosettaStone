// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_PLAYER_H
#define HEARTHSTONEPP_PLAYER_H

#include <hspp/Accounts/Account.h>
#include <hspp/Cards/Entity.h>
#include <hspp/Cards/Hero.h>
#include <hspp/Cards/Minion.h>
#include <hspp/Cards/Spell.h>

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

    //! Operator overloading: The equality operator.
    bool operator==(const Player& player) const;

    //! Returns the game agent.
    //! \return The game agent.
    GameAgent& GetGameAgent() const;

    //! Sets the game agent.
    //! \param agent The game agent.
    void SetGameAgent(GameAgent* agent);

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
    void AddHeroAndPower(Card heroCard, Card powerCard);

    Hero* hero = nullptr;

    BYTE id = 0;
    BYTE totalMana = 0;
    BYTE existMana = 0;
    BYTE exhausted = 0;

    std::string email;

    // Card storage
    std::vector<Entity*> cards;

    // Card objects
    std::vector<Character*> field;
    std::vector<Entity*> hand;
    std::vector<Spell*> usedSpell;
    std::vector<Character*> usedMinion;

 private:
    //! Releases dynamic allocated resources.
    void FreeMemory();

    GameAgent* m_gameAgent = nullptr;
    Player* m_opponent = nullptr;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_PLAYER_H
