/*************************************************************************
> File Name: NetworkManager.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Network manager of Hearthstone++ GUI program.
> Created Time: 2018/06/06
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_GUI_NETWORK_MANAGER_H
#define HEARTHSTONEPP_GUI_NETWORK_MANAGER_H

#include <string>

namespace Hearthstonepp
{
class NetworkManager
{
 public:
    NetworkManager(const NetworkManager& other) = delete;
    ~NetworkManager() = delete;

    static NetworkManager* GetInstance();

    bool CreateAccount(std::string email, std::string nickname,
                       std::string password);

 private:
    NetworkManager() = default;

    static NetworkManager* m_instance;
};
}

#endif