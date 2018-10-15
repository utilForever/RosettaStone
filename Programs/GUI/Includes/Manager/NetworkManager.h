// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

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

    bool Login(const std::string& email, const std::string&& password) const;
    bool CreateAccount(std::string email, std::string nickname,
                       const std::string&& password) const;

 private:
    NetworkManager() = default;

    static NetworkManager* m_instance;
};
}

#endif