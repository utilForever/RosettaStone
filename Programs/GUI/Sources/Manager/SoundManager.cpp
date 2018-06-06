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

void SoundManager::PlayMusic(const char* musicFileName, bool isForceToPlay)
{
    // If you try to play the same music,
    // the music that was being played will continue to play,
    // except when you forcibly play it.
    if (IsMusicPlaying() && m_musicName == musicFileName && !isForceToPlay)
    {
        return;
    }

    m_music.openFromFile(std::string(SOUNDS_DIR) + musicFileName);
    m_music.play();

    m_musicName = musicFileName;
}

void SoundManager::StopMusic()
{
    m_music.stop();
}

bool SoundManager::IsMusicPlaying() const
{
    return m_music.getStatus() == sf::SoundSource::Playing;
}

std::optional<std::string> SoundManager::GetPlayingMusicName() const
{
    if (IsMusicPlaying())
    {
        return m_musicName;
    }

    return std::nullopt;
}
}