// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_PLAYMODE_REDUCED_BOARD_VIEW_HPP
#define ROSETTASTONE_PLAYMODE_REDUCED_BOARD_VIEW_HPP

#include <Rosetta/PlayMode/Views/ViewTypes.hpp>

namespace RosettaStone::PlayMode
{
class BoardRefView;

//!
//! \brief ReducedBoardView class.
//!
//! Reduced board view which is designed to determine if an identical game state
//! is reached via different action orderings, and is also designed to be
//! storable and hashable The information here should be enough so that
//! available actions are identical if the reduced board view are identical.
//!
class ReducedBoardView
{
    friend std::hash<ReducedBoardView>;

 public:
    //! Constructs reduced board view with given \p view.
    //! \param view The board ref view.
    explicit ReducedBoardView(const BoardRefView& view);

    //! Default copy constructor.
    ReducedBoardView(const ReducedBoardView&) = default;

    //! Default move constructor.
    ReducedBoardView(ReducedBoardView&&) noexcept = default;

    //! Default copy assignment operator.
    ReducedBoardView& operator=(const ReducedBoardView&) = default;

    //! Default move assignment operator.
    ReducedBoardView& operator=(ReducedBoardView&&) noexcept = default;

    //! Operator overloading: operator==.
    bool operator==(const ReducedBoardView& rhs) const;

    //! Operator overloading: operator!=.
    bool operator!=(const ReducedBoardView& rhs) const;

    //! Returns the current turn of the game.
    //! \return The current turn of the game.
    int GetTurn() const;

    //! Returns the side of the view.
    //! \return the side of the view.
    PlayerType GetSide() const;

    //! Returns the hero of the current player.
    //! \return The hero of the current player.
    const ViewTypes::MyHero& GetMyHero() const;

    //! Returns the hero power of the current player.
    //! \return the hero power of the current player.
    const ViewTypes::HeroPower& GetMyHeroPower() const;

    //! Returns the weapon of the current player.
    //! \return The weapon of the current player.
    const ViewTypes::Weapon& GetMyWeapon() const;

    //! Returns the mana crystals of the current player.
    //! \return The mana crystals of the current player.
    const ViewTypes::ManaCrystal& GetMyManaCrystal() const;

    //! Returns a list of minions in the field of the current player.
    //! \return A list of minions in the field of the current player.
    const ViewTypes::MyMinions& GetMyMinions() const;

    //! Returns a list of cards in the hand of the current player.
    //! \return A list of cards in the hand of the current player.
    const ViewTypes::MyHand& GetMyHand() const;

    //! Returns a list of cards in the deck of the current player.
    //! \return A list of cards in the deck of the current player.
    const ViewTypes::Deck& GetMyDeck() const;

    //! Returns the hero of the opponent player.
    //! \return The hero of the opponent player.
    const ViewTypes::Hero& GetOpHero() const;

    //! Returns the hero power of the opponent player.
    //! \return the hero power of the opponent player.
    const ViewTypes::HeroPower& GetOpHeroPower() const;

    //! Returns the weapon of the opponent player.
    //! \return The weapon of the opponent player.
    const ViewTypes::Weapon& GetOpWeapon() const;

    //! Returns the mana crystals of the opponent player.
    //! \return The mana crystals of the opponent player.
    const ViewTypes::ManaCrystal& GetOpManaCrystal() const;

    //! Returns a list of minions in the field of the opponent player.
    //! \return A list of minions in the field of the opponent player.
    const ViewTypes::Minions& GetOpMinions() const;

    //! Returns a list of cards in the hand of the opponent player.
    //! \return A list of cards in the hand of the opponent player.
    const ViewTypes::OpHand& GetOpHand() const;

    //! Returns a list of cards in the deck of the current player.
    //! \return A list of cards in the deck of the current player.
    const ViewTypes::Deck& GetOpDeck() const;

 private:
    int m_turn;
    PlayerType m_side;

    ViewTypes::MyHero m_myHero;
    ViewTypes::HeroPower m_myHeroPower;
    ViewTypes::Weapon m_myWeapon;
    ViewTypes::ManaCrystal m_myManaCrystal;
    ViewTypes::MyMinions m_myMinions;
    ViewTypes::MyHand m_myHand;
    ViewTypes::Deck m_myDeck;

    ViewTypes::Hero m_opHero;
    ViewTypes::HeroPower m_opHeroPower;
    ViewTypes::Weapon m_opWeapon;
    ViewTypes::ManaCrystal m_opManaCrystal;
    ViewTypes::Minions m_opMinions;
    ViewTypes::OpHand m_opHand;
    ViewTypes::Deck m_opDeck;
};
}  // namespace RosettaStone::PlayMode

namespace std
{
using namespace RosettaStone::PlayMode;

//! \brief Template specialization of std::hash for ReducedBoardView.
template <>
struct hash<ReducedBoardView>
{
    std::size_t operator()(const ReducedBoardView& rhs) const noexcept
    {
        std::size_t result = 0;
        CombineHash(result, rhs.m_turn);
        CombineHash(result, static_cast<int>(rhs.m_side));

        CombineHash(result, rhs.m_myHero);
        CombineHash(result, rhs.m_myHeroPower);
        CombineHash(result, rhs.m_myWeapon);
        CombineHash(result, rhs.m_myManaCrystal);
        CombineHash(result, rhs.m_myMinions);
        CombineHash(result, rhs.m_myHand);
        CombineHash(result, rhs.m_myDeck);

        CombineHash(result, rhs.m_opHero);
        CombineHash(result, rhs.m_opHeroPower);
        CombineHash(result, rhs.m_opWeapon);
        CombineHash(result, rhs.m_opManaCrystal);
        CombineHash(result, rhs.m_opMinions);
        CombineHash(result, rhs.m_opHand);
        CombineHash(result, rhs.m_opDeck);

        return result;
    }
};
}  // namespace std

#endif  // ROSETTASTONE_PLAYMODE_REDUCED_BOARD_VIEW_HPP
