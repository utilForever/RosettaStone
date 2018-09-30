// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

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

std::string SoundManager::GetPlayingMusicName() const
{
    if (IsMusicPlaying())
    {
        return m_musicName;
    }

    return "";
}
}