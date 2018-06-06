/*************************************************************************
> File Name: NetworkManager.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Network manager of Hearthstone++ GUI program.
> Created Time: 2018/06/06
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Manager/NetworkManager.h>

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
}