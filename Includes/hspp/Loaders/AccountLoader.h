// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_ACCOUNT_LOADER_H
#define HEARTHSTONEPP_ACCOUNT_LOADER_H

#include <hspp/Accounts/Account.h>

#include <json/json.hpp>

namespace Hearthstonepp
{
//!
//! \brief AccountLoader class.
//!
//! This class loads/saves account data from/to <email>.json.
//!
class AccountLoader
{
 public:
    //! Loads account information from a json file named \p email.
    //! \param email The email address of the account.
    //! \return Account instance that stores information that was loaded.
    Account* Load(std::string email) const;

    //! Saves account information \p p to a json file.
    //! \param account A pointer to account instance that stores information.
    void Save(Account* account) const;
};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_ACCOUNT_LOADER_H