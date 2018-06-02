/*************************************************************************
> File Name: LoginScene.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Login scene of Hearthstone++ GUI program.
> Created Time: 2018/05/31
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Manager/GameManager.h>
#include <Scenes/LoginScene.h>

namespace Hearthstonepp
{
void LoginScene::Start()
{
    GameManager::GetInstance()->SetBackground(IMAGES_DIR "Background_Login.png");
    GameManager::GetInstance()->PlayBGM(SOUNDS_DIR "BGM_Login.ogg");

    m_flags |= ImGuiWindowFlags_NoResize;
    m_flags |= ImGuiWindowFlags_NoMove;
    m_flags |= ImGuiWindowFlags_NoCollapse;
    m_flags |= ImGuiWindowFlags_NoTitleBar;

    m_positionX =
        GameManager::GetInstance()->GetWindowWidth() * 0.5f - m_width * 0.5f;
    m_positionY =
        GameManager::GetInstance()->GetWindowHeight() * 0.5f - m_height * 0.5f;
}

void LoginScene::Input()
{
    // Do nothing
}

void LoginScene::Update()
{
    ImGui::SetNextWindowPos(ImVec2(m_positionX, m_positionY));

    ImGui::Begin("Login", &m_isOpened, ImVec2(m_width, m_height), 0.0f,
                 m_flags);
    {
        // Info
        // ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f),
        // data.info.c_str());

        ImGui::NewLine();

        // Nick
        ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "Nick:");
        static bool focusHere = true;
        if (focusHere)
        {
            ImGui::SetKeyboardFocusHere();
            focusHere = false;
        }
        /*ImGui::InputText("##Nick", data.nick, IM_ARRAYSIZE(data.nick));*/

        ImGui::NewLine();

        // Password
        // ImGui::TextColored(ImVec4(0.0f, 0.0f, 0.0f, 1.0f), "Password:");
        // if (ImGui::InputText("##Password", data.password,
        //                     IM_ARRAYSIZE(data.password),
        //                     ImGuiInputTextFlags_Password |
        //                         ImGuiInputTextFlags_EnterReturnsTrue))
        //{
        //    checkLogin(sceneData_);
        //}

        ImGui::NewLine();

        // Check Login
        if (ImGui::Button("Login"))
        {
        }

        ImGui::NewLine();

        // Create Account
        if (ImGui::Button("Create Account"))
        {
        }

        ImGui::NewLine();

        // Forgot Password
        if (ImGui::Button("Forgot Password"))
        {
        }
    }
    ImGui::End();
}

void LoginScene::Finish()
{
    // Do nothing
}
}