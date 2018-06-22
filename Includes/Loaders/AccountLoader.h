/*************************************************************************
> File Name: AccountLoader.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Account loader that loads data from <email>.json.
> Created Time: 2017/10/19
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_ACCOUNT_LOADER_H
#define HEARTHSTONEPP_ACCOUNT_LOADER_H

#include <Accounts/Account.h>

#include <json/json.hpp>

namespace Hearthstonepp
{
using json = nlohmann::json;

class AccountLoader
{
public:
    Account* Load(std::string email) const;
    void Save(Account* p) const;
};
}

#endif