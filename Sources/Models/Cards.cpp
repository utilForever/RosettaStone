/*************************************************************************
> File Name: Cards.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Cards class that stores a list of cards.
> Created Time: 2017/10/10
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Loaders/CardLoader.h>
#include <Models/Cards.h>

namespace Hearthstonepp
{
    Cards* Cards::m_instance = nullptr;

    Cards::Cards()
    {
        CardLoader loader;
        m_cards = loader.Load();
    }

    Cards::~Cards()
    {
        
    }

    Cards* Cards::GetInstance()
    {
        if (m_instance == nullptr)
        {
            m_instance = new Cards();
        }

        return m_instance;
    }
}