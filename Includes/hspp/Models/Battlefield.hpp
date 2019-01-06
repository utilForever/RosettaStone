// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_BATTLEFIELD_HPP
#define HEARTHSTONEPP_BATTLEFIELD_HPP

#include <hspp/Cards/Character.hpp>
#include <hspp/Commons/Constants.hpp>

#include <array>

namespace Hearthstonepp
{
//!
//! \brief Battlefield class.
//!
//! This class is where the action takes place, representing the board on which
//! each game is played out. Around the battlefield are various important UI
//! elements, such as each player's hand, deck and Mana Crystals, as well as the
//! two heroes themselves. Each battlefield features its own design and numerous
//! interactive elements, but play is in no way affected or determined by
//! battlefield selection. Battlefields are chosen at random and are independent
//! of the heroes chosen by players or used by the Innkeeper.
//!
class Battlefield
{
 public:
    //! Default constructor.
    Battlefield();

    //! Returns the owner of battlefield.
    //! \return The owner of battlefield.
    Player& GetOwner() const;

    //! Sets the owner of battlefield.
    //! \param owner The owner of battlefield.
    void SetOwner(Player& owner);

    //! Returns all minions in battlefield.
    std::vector<Character*> GetAllMinions();

 private:
    Player* m_owner = nullptr;
    std::array<Character*, FIELD_SIZE> m_minions{};
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_BATTLEFIELD_HPP