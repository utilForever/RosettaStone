/*************************************************************************
> File Name: AccountLoader.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Account loader that loads data from <accountName>.json.
> Created Time: 2017/10/19
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_PLAYER_LOADER_H
#define HEARTHSTONEPP_PLAYER_LOADER_H

#include <Models/Account.h>

#include <json/json.hpp>

namespace Hearthstonepp
{
    using json = nlohmann::json;

    class AccountLoader
    {
    public:
        Account* Load(std::string accountID) const;
        void Save(Account* p) const;
    };
}

#endif