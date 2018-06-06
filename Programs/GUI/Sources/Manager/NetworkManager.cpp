/*************************************************************************
> File Name: NetworkManager.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Network manager of Hearthstone++ GUI program.
> Created Time: 2018/06/06
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Manager/NetworkManager.h>

#include <Commons/Macros.h>

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

bool NetworkManager::CreateAccount(std::string email, std::string nickname,
                                   std::string password)
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

    //m_player = new Player(std::move(playerID), std::move(name));

    //PlayerLoader loader;
    //loader.Save(m_player);

    return true;
}
}