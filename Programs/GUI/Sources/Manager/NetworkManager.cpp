// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Manager/GameManager.h>
#include <Manager/NetworkManager.h>

#include <hspp/Commons/Macros.h>
#include <hspp/Loaders/AccountLoader.h>

#ifdef HEARTHSTONEPP_WINDOWS
#include <filesystem>
#endif
#ifdef HEARTHSTONEPP_LINUX
#include <experimental/filesystem>
#endif
#ifdef HEARTHSTONEPP_MACOSX
#include <sys/stat.h>
#endif

#ifndef HEARTHSTONEPP_MACOSX
namespace filesystem = std::experimental::filesystem;
#endif

namespace Hearthstonepp
{
NetworkManager* NetworkManager::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new NetworkManager();
    }

    return m_instance;
}

bool NetworkManager::Login(const std::string& email,
                           [[maybe_unused]] const std::string&& password) const
{
#ifndef HEARTHSTONEPP_MACOSX
    if (!filesystem::exists("Datas/" + email + ".json"))
#else
    struct stat buf;
    std::string path = "Datas/" + email + ".json";
    if (stat(path.c_str(), &buf) == -1)
#endif
    {
        return false;
    }

    AccountLoader loader;
    GameManager::GetInstance()->SetAccount(loader.Load(email));

    return GameManager::GetInstance()->GetAccount() != nullptr;
}

bool NetworkManager::CreateAccount(
    std::string email, std::string nickname,
    [[maybe_unused]] const std::string&& password) const
{
#ifndef HEARTHSTONEPP_MACOSX
    if (filesystem::exists("Datas/" + email + ".json"))
#else
    struct stat buf;
    std::string path = "Datas/" + email + ".json";
    if (stat(path.c_str(), &buf) == 0)
#endif
    {
        return false;
    }

    GameManager::GetInstance()->SetAccount(
        new Account(std::move(email), std::move(nickname)));

    if (Account* p = GameManager::GetInstance()->GetAccount())
    {
        AccountLoader loader;
        loader.Save(p);

        return true;
    }

    return false;
}
}