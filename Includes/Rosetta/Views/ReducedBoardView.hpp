// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

// It is based on peter1591's hearthstone-ai repository.
// References: https://github.com/peter1591/hearthstone-ai

#ifndef ROSETTASTONE_REDUCED_BOARD_VIEW_HPP
#define ROSETTASTONE_REDUCED_BOARD_VIEW_HPP

#include <Rosetta/Views/ViewTypes.hpp>

namespace RosettaStone
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
    ReducedBoardView(const BoardRefView& board);

    ReducedBoardView(const ReducedBoardView&) = default;
    ReducedBoardView(ReducedBoardView&&) = default;

    ReducedBoardView& operator=(const ReducedBoardView&) = default;
    ReducedBoardView& operator=(ReducedBoardView&&) = default;

    bool operator==(const ReducedBoardView& rhs) const;
    bool operator!=(const ReducedBoardView& rhs) const;

    int GetTurn() const;
    PlayerType GetPlayerType() const;

    const ViewTypes::MyHero& GetMyHero() const;
    const ViewTypes::HeroPower& GetMyHeroPower() const;
    const ViewTypes::Weapon& GetMyWeapon() const;
    const ViewTypes::ManaCrystal& GetMyManaCrystal() const;
    const ViewTypes::MyMinions& GetMyMinions() const;
    const ViewTypes::MyHand& GetMyHand() const;
    const ViewTypes::Deck& GetMyDeck() const;

    const ViewTypes::Hero& GetOpHero() const;
    const ViewTypes::HeroPower& GetOpHeroPower() const;
    const ViewTypes::Weapon& GetOpWeapon() const;
    const ViewTypes::ManaCrystal& GetOpManaCrystal() const;
    const ViewTypes::Minions& GetOpMinions() const;
    const ViewTypes::OpHand& GetOpHand() const;
    const ViewTypes::Deck& GetOpDeck() const;

 private:
    constexpr static int changeID = 3;

    int m_turn;
    PlayerType m_playerType;

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
}  // namespace RosettaStone

namespace std
{
using namespace RosettaStone;

template <>
struct hash<ReducedBoardView>
{
    std::size_t operator()(const ReducedBoardView& rhs) const noexcept
    {
        static_assert(ReducedBoardView::changeID == 3);

        std::size_t result = 0;
        CombineHash(result, rhs.m_turn);
        CombineHash(result, static_cast<int>(rhs.m_playerType));

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

#endif  // ROSETTASTONE_REDUCED_BOARD_VIEW_HPP
