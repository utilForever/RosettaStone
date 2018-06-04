/*************************************************************************
> File Name: SoundManager.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Sound manager of Hearthstone++ GUI program.
> Created Time: 2018/06/05
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_GUI_SOUND_MANAGER_H
#define HEARTHSTONEPP_GUI_SOUND_MANAGER_H

namespace Hearthstonepp
{
class SoundManager
{
 public:
    SoundManager(const SoundManager& other) = delete;
    ~SoundManager() = delete;

    static SoundManager* GetInstance();

 private:
    SoundManager() = default;

    static SoundManager* m_instance;
};
}

#endif