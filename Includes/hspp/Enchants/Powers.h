// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_POWERS_H
#define HEARTHSTONEPP_POWERS_H

#include <hspp/Enchants/Power.h>

#include <map>
#include <string>

namespace Hearthstonepp
{
//!
//! \brief Powers class.
//!
//! This class stores a list of power.
//!
class Powers
{
 public:
    //! Deleted copy constructor.
    Powers(const Powers& powers) = delete;

    //! Deleted copy assignment operator.
    Powers& operator=(const Powers& powers) = delete;

    //! Returns a pointer to instance of Powers class.
    //! \return A pointer to instance of Powers class.
    static Powers& GetInstance();

    //! Returns a pointer to card that matches \p cardID.
    //! \param cardID The ID of the card.
    //! \return A pointer to card that matches \p cardID.
    Power* FindPowerByCardID(std::string cardID) const;

 private:
    //! Constructor: Loads power data.
    Powers();

    //! Destructor: Releases power data.
    ~Powers();

    std::map<std::string, Power*> m_powers;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_POWERS_H