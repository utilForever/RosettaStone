// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYER_HPP
#define ROSETTASTONE_PLAYER_HPP

#include <Rosetta/Commons/Constants.hpp>
#include <Rosetta/Models/Battlefield.hpp>
#include <Rosetta/Models/Choice.hpp>
#include <Rosetta/Models/Deck.hpp>
#include <Rosetta/Models/Entity.hpp>
#include <Rosetta/Models/Graveyard.hpp>
#include <Rosetta/Models/Hand.hpp>
#include <Rosetta/Models/Hero.hpp>

#include <string>

namespace RosettaStone
{
class Game;
class IPolicy;
class TaskMeta;

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

    //! Returns the value of game tag.
    //! \param tag The game tag of card.
    //! \return The value of game tag.
    int GetGameTag(GameTag tag) const;

    //! Sets game tag to the card.
    //! \param tag The game tag to indicate ability or condition.
    //! \param value The value to set for game tag.
    void SetGameTag(GameTag tag, int value);

    //! Returns total amount of mana available.
    //! \return Total amount of mana available.
    int GetTotalMana() const;

    //! Sets total amount of mana available.
    //! \param amount Total amount of mana available.
    void SetTotalMana(int amount);

    //! Returns amount of mana used.
    //! \return Amount of mana used.
    int GetUsedMana() const;

    //! Sets amount of mana used.
    //! \param amount Amount of mana used.
    void SetUsedMana(int amount);

    //! Returns additional mana gained during this turn.
    //! \return additional mana gained during this turn.
    int GetTemporaryMana() const;

    //! Sets additional mana gained during this turn.
    //! \param amount additional mana gained during this turn.
    void SetTemporaryMana(int amount);

    //! Returns the amount of mana available to actually use after calculating
    //! all resource factors.
    //! \return The amount of mana available to actually use.
    int GetRemainingMana() const;

    //! Returns whether combo is active.
    //! \return Whether combo is active.
    bool IsComboActive() const;

    //! Sets the value of combo active.
    //! \param isActive Whether combo is active.
    void SetComboActive(bool isActive);

    //! Returns the next action of policy.
    //! \return A task to run that is determined by policy.
    ITask* GetNextAction();

    //! Adds hero and hero power.
    //! \param heroCard A card that represents hero.
    //! \param powerCard A card that represents hero power.
    void AddHeroAndPower(Card&& heroCard, Card&& powerCard);

    std::string nickname;
    PlayerType playerType = PlayerType::PLAYER1;
    std::size_t playerID = 0;

    PlayState playState = PlayState::INVALID;
    Mulligan mulliganState = Mulligan::INVALID;
    std::optional<Choice> choice = std::nullopt;

    IPolicy* policy = nullptr;
    Player* opponent = nullptr;

    std::vector<Entity*> setaside;

    int currentSpellPower = 0;

 private:
    // Returns a task that is selected by action.
    //! \param next A next action selected by policy.
    //! \param req A requirement for action.
    //! \return A task that is selected by action.
    static ITask* GetTaskByAction(TaskMeta& next, TaskMeta& req);

    Battlefield m_field;
    Deck m_deck;
    Graveyard m_graveyard;
    Hand m_hand;

    Hero* m_hero = nullptr;
    Game* m_game = nullptr;

    std::map<GameTag, int> m_gameTags;
};
}  // namespace RosettaStone

#endif  // ROSETTASTONE_PLAYER_HPP
