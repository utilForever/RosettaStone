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

#include <SFML/Audio/Music.hpp>

namespace Hearthstonepp
{
class SoundManager
{
 public:
    SoundManager(const SoundManager& other) = delete;
    ~SoundManager() = delete;

    static SoundManager* GetInstance();

    //! Play Music.
    void PlayMusic(const char* musicFileName, bool isForceToPlay = false);

    //! Stop Music.
    void StopMusic();

    //! Returns whether the music is playing.
    bool IsMusicPlaying() const;

    //! Returns the name of the currently playing music.
    std::string GetPlayingMusicName() const;

 private:
    SoundManager() = default;

    static SoundManager* m_instance;

    sf::Music m_music;
    std::string m_musicName;
};
}

#endif