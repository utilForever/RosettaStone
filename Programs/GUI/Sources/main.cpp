// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Manager/GameManager.h>
#include <Manager/NetworkManager.h>
#include <Manager/SceneManager.h>
#include <Manager/SoundManager.h>
#include <Scenes/CreateAccountScene.h>
#include <Scenes/ForgotPasswordScene.h>
#include <Scenes/LoginScene.h>

using namespace Hearthstonepp;

GameManager* GameManager::m_instance = nullptr;
NetworkManager* NetworkManager::m_instance = nullptr;
SceneManager* SceneManager::m_instance = nullptr;
SoundManager* SoundManager::m_instance = nullptr;

int main()
{
    // Login Scene
    LoginScene loginScene;
    loginScene.SetName("Login");
    SceneManager::GetInstance()->AddScene(&loginScene);

    // Create account scene
    CreateAccountScene createAccountScene;
    createAccountScene.SetName("CreateAccount");
    SceneManager::GetInstance()->AddScene(&createAccountScene);

    // Forgot password Scene
    ForgotPasswordScene forgotPasswordScene;
    forgotPasswordScene.SetName("ForgotPassword");
    SceneManager::GetInstance()->AddScene(&forgotPasswordScene);

    // Starts the scene manager
    SceneManager::GetInstance()->StartSceneManager("Login");

    return 0;
}