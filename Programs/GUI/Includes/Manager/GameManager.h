/*************************************************************************
> File Name: GameManager.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Game manager of Hearthstone++ GUI program.
> Created Time: 2018/05/31
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_GUI_GAME_MANAGER_H
#define HEARTHSTONEPP_GUI_GAME_MANAGER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace Hearthstonepp
{
class GameManager
{
 public:
    GameManager(const GameManager& other) = delete;
    ~GameManager() = delete;

    static GameManager* GetInstance();

    //! Start the game.
    void Start(sf::RenderWindow* window);

    //! Finish the game.
    void Finish();

    //! Set the background.
    void SetBackground(const char* imagePath);

    //! Remove the background.
    void RemoveBackground();

    //! Clear draw lists.
    void ClearDrawList();

    //! Return the window is opened.
    bool IsOpen() const;

    //! Close the window.
    void CloseWindow() const;

    //! Draw everything.
    void Draw();

    //! Return the width of the window
    int GetWindowWidth() const;

    //! Return the height of the window
    int GetWindowHeight() const;

 private:
    GameManager() = default;

    static GameManager* m_instance;

    sf::RenderWindow* m_window;

    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;

    int m_windowWidth = 1024;
    int m_windowHeight = 768;
};
}

#endif