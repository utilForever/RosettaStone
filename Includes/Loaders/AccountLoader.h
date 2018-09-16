#ifndef HEARTHSTONEPP_ACCOUNT_LOADER_H
#define HEARTHSTONEPP_ACCOUNT_LOADER_H

#include <Accounts/Account.h>

#include <json/json.hpp>

namespace Hearthstonepp
{
//!
//! \brief AccountLoader class.
//!
//! This class loads/saves data from/to <email>.json.
//!
class AccountLoader
{
 public:
    //! Loads account information from a json file named \p email.
    Account* Load(std::string email) const;

    //! Saves account information \p p to a json file.
    void Save(Account* account) const;
};
}  // namespace Hearthstonepp

#endif