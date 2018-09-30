// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GUI_GAME_MANAGER_H
#define HEARTHSTONEPP_GUI_GAME_MANAGER_H

#include <hspp/Accounts/Account.h>

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
    void SetBackground(const char* imageFileName);

    //! Remove the background.
    void RemoveBackground();

    //! Clear draw lists.
    void ClearDrawList();

    //! Returns the window is opened.
    bool IsOpen() const;

    //! Close the window.
    void CloseWindow() const;

    //! Returns the window has focus.
    bool HasWindowFocus() const;

    //! Draw everything.
    void Draw();

    //! Returns the width of the window.
    int GetWindowWidth() const;

    //! Returns the height of the window.
    int GetWindowHeight() const;

    //! Set account object.
    void SetAccount(Account* account);

    //! Returns account object.
    Account* GetAccount() const;

 private:
    GameManager() = default;

    static GameManager* m_instance;

    sf::RenderWindow* m_window;

    sf::Texture m_backgroundTexture;
    sf::Sprite m_backgroundSprite;

    int m_windowWidth;
    int m_windowHeight;

    Account* m_account;
};
}

#endif