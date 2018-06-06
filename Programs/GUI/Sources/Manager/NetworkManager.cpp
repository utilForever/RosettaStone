/*************************************************************************
> File Name: NetworkManager.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Network manager of Hearthstone++ GUI program.
> Created Time: 2018/06/06
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Manager/GameManager.h>
#include <Manager/NetworkManager.h>

#include <Commons/Macros.h>
#include <Loaders/PlayerLoader.h>

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
    std::string path = "Datas/" + playerID + ".json";
    if (stat(path.c_str(), &buf) == -1)
#endif
    {
        return false;
    }

    PlayerLoader loader;
    GameManager::GetInstance()->SetPlayer(loader.Load(email));

    return GameManager::GetInstance()->GetPlayer() != nullptr;
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

    GameManager::GetInstance()->SetPlayer(
        new Player(std::move(email), std::move(nickname)));

    if (Player* p = GameManager::GetInstance()->GetPlayer())
    {
        PlayerLoader loader;
        loader.Save(p);

        return true;
    }

    return false;
}
}