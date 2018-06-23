/*************************************************************************
> File Name: Powers.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Powers class that stores power in every card.
> Created Time: 2018/06/23
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_POWERS_H
#define HEARTHSTONEPP_POWERS_H

#include <map>
#include <string>

namespace Hearthstonepp
{
struct Powers
{
    Powers(const Powers& other) = delete;
    ~Powers() = delete;

    static Powers* GetInstance();

private:
    Powers();

    static Powers* m_instance;

    std::map<std::string, Power> m_powers;
};
}

#endif