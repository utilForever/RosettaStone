// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GAME_HPP
#define HEARTHSTONEPP_GAME_HPP

#include <hspp/Accounts/Player.hpp>
#include <hspp/Commons/Constants.hpp>
#include <hspp/Enums/CardEnums.hpp>
#include <hspp/Policy/Policy.hpp>

namespace Hearthstonepp
{
class Game
{
 public:
    Game(CardClass p1Class, CardClass p2Class,
         PlayerType firstPlayer = PlayerType::PLAYER1);

    

 private:
    Player m_player1;
    Player m_player2;

    PlayerType m_firstPlayer;
    PlayerType m_currentPlayer;
};
}  // namespace Hearthstonepp

#endif