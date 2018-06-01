/*************************************************************************
> File Name: main.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Main entry of Hearthstone++ GUI program.
> Created Time: 2018/02/04
> Copyright (c) 2017, Chan-Ho Chris Ohk
*************************************************************************/
#include <Manager/GameManager.h>
#include <Manager/SceneManager.h>
#include <Scenes/LoginScene.h>

using namespace Hearthstonepp;

GameManager* GameManager::m_instance = nullptr;
SceneManager* SceneManager::m_instance = nullptr;

int main()
{
    // Login Scene
    LoginScene loginScene;
    loginScene.SetName("Login");
    SceneManager::GetInstance()->AddScene(&loginScene);

    // Starts the scene manager
    SceneManager::GetInstance()->StartSceneManager("Login");

    return 0;
}