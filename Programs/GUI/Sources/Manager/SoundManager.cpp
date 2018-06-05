/*************************************************************************
> File Name: SoundManager.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Sound manager of Hearthstone++ GUI program.
> Created Time: 2018/06/05
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Manager/SoundManager.h>

namespace Hearthstonepp
{
SoundManager* SoundManager::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new SoundManager();
    }

    return m_instance;
}

void SoundManager::PlayMusic(const char* musicFileName)
{
    m_music.openFromFile(std::string(SOUNDS_DIR) + musicFileName);
    m_music.play();
}

void SoundManager::StopMusic()
{
    m_music.stop();
}
}