/*************************************************************************
> File Name: Runnable.h
> Project Name: Hearthstonepp
> Author: Young-Joong Kim
> Purpose:
> Created Time: 2018/07/05
> Copyright (c) 2018, Young-Joong Kim
*************************************************************************/

#ifndef HEARTHSTONEPP_RUNNABLE_H
#define HEARTHSTONEPP_RUNNABLE_H

namespace Hearthstonepp
{
class Runnable
{
public:
    virtual Task GetTask() const = 0;

private:

};
}  // namespace Hearthstonepp

#endif  // HEARTHSTONEPP_RUNNABLE_H
