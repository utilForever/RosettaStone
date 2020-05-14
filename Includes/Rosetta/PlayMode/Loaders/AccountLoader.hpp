// Copyright (c) 2019 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef ROSETTASTONE_PLAYMODE_ACCOUNT_LOADER_HPP
#define ROSETTASTONE_PLAYMODE_ACCOUNT_LOADER_HPP

#include <Rosetta/PlayMode/Accounts/AccountInfo.hpp>

#include <json/json.hpp>

namespace RosettaStone::PlayMode
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
    AccountInfo* Load(std::string email) const;

    //! Saves account information \p p to a json file.
    //! \param account A pointer to account instance that stores information.
    void Save(AccountInfo* account) const;
};
}  // namespace RosettaStone::PlayMode

#endif  // ROSETTASTONE_PLAYMODE_ACCOUNT_LOADER_HPP
