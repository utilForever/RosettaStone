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
#include <Utils/ImGuiUtils.h>

namespace Hearthstonepp
{
void LoginScene::Start()
{
    GameManager::GetInstance()->SetBackground(IMAGES_DIR
                                              "Background_Login.png");
    GameManager::GetInstance()->PlayBGM(SOUNDS_DIR "BGM_Login.ogg");

    m_flags |= ImGuiWindowFlags_NoResize;
    m_flags |= ImGuiWindowFlags_NoMove;
    m_flags |= ImGuiWindowFlags_NoCollapse;
    m_flags |= ImGuiWindowFlags_NoTitleBar;

    m_width = GameManager::GetInstance()->GetWindowWidth() * 0.3f;
    m_height = GameManager::GetInstance()->GetWindowHeight() * 0.4f;

    m_positionX =
        GameManager::GetInstance()->GetWindowWidth() * 0.5f - m_width * 0.5f;
    m_positionY =
        GameManager::GetInstance()->GetWindowHeight() * 0.5f - m_height * 0.5f;

    memset(m_id, 0, sizeof(m_id));
    memset(m_password, 0, sizeof(m_password));
}

void LoginScene::Input()
{
    // Do nothing
}

void LoginScene::Update()
{
    ImGui::SetNextWindowSize(sf::Vector2f(450, 250), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(m_positionX, m_positionY));
    ImGui::SetNextWindowPosCenter(true);

    ImGui::Begin("Login", &m_isOpened, ImVec2(m_width, m_height), 0.5f,
                 m_flags);
    {
        ImGui::PushItemWidth(-1);
        
        ImGui::SetWindowFontScale(1.0f);

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "ID:");
        static bool focusHere = true;
        if (focusHere)
        {
            ImGui::SetKeyboardFocusHere();
            focusHere = false;
        }
        ImGui::InputText("##ID", m_id, sizeof(m_id));

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Password:");
        ImGui::InputText("##Password", m_password, sizeof(m_password),
                         ImGuiInputTextFlags_Password);

        ImGui::NewLine();
        ImGui::NewLine();

        ImGui::SetWindowFontScale(1.0f);

        // Check Login
        SetAlignmentHorizontalCenter("Login", true);
        if (ImGui::Button("Login"))
        {
            // CheckLogin(m_id, m_password);
        }

        ImGui::NewLine();

        // Create Account
        SetAlignmentHorizontalCenter("Create Account", true);
        if (ImGui::Button("Create Account"))
        {
            // SceneManager::GetInstance()->ChangeScene("CreateAccount");
        }

        ImGui::NewLine();

        // Forgot Password
        SetAlignmentHorizontalCenter("Forgot Password", true);
        if (ImGui::Button("Forgot Password"))
        {
            SceneManager::GetInstance()->ChangeScene("ForgotPassword");
        }

        ImGui::PopItemWidth();
    }
    ImGui::End();
}

void LoginScene::Finish()
{
    // Do nothing
}
}