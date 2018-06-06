/*************************************************************************
> File Name: CreateAccountScene.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Create account scene of Hearthstone++ GUI program.
> Created Time: 2018/06/06
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Manager/SoundManager.h>
#include <Scenes/CreateAccountScene.h>
#include <Utils/ImGuiUtils.h>

namespace Hearthstonepp
{
void CreateAccountScene::Start()
{
    GameManager::GetInstance()->SetBackground("Background_Login.png");
    SoundManager::GetInstance()->PlayMusic("BGM_Login.ogg");

    m_flags |= ImGuiWindowFlags_NoResize;
    m_flags |= ImGuiWindowFlags_NoMove;
    m_flags |= ImGuiWindowFlags_NoCollapse;
    m_flags |= ImGuiWindowFlags_NoTitleBar;

    m_width = GameManager::GetInstance()->GetWindowWidth() * 0.3f;
    m_height = GameManager::GetInstance()->GetWindowHeight() * 0.52f;

    m_positionX =
        GameManager::GetInstance()->GetWindowWidth() * 0.5f - m_width * 0.5f;
    m_positionY =
        GameManager::GetInstance()->GetWindowHeight() * 0.5f - m_height * 0.5f;
}

void CreateAccountScene::Input()
{
}

void CreateAccountScene::Update()
{
    ImGui::SetNextWindowSize(sf::Vector2f(450, 250), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(m_positionX, m_positionY));
    ImGui::SetNextWindowPosCenter(true);

    ImGui::Begin("CreateAccount", &m_isOpened, ImVec2(m_width, m_height),
                 0.5f, m_flags);
    {
        ImGui::PushItemWidth(-1);

        ImGui::SetWindowFontScale(SceneManager::GetInstance()->GetFontScale());

        // Email
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Email:");
        ImGui::InputText("##Email", m_email, IM_ARRAYSIZE(m_email));

        ImGui::NewLine();

        // Nickname
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Nickname:");
        ImGui::InputText("##Nickname", m_nickname, IM_ARRAYSIZE(m_nickname));

        ImGui::NewLine();

        // Password 1
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Password:");
        ImGui::InputText("##Password1", m_password1, IM_ARRAYSIZE(m_password1),
                         ImGuiInputTextFlags_Password);

        ImGui::NewLine();

        // Password 2
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Confirm Password:");
        ImGui::InputText("##Password2", m_password2, IM_ARRAYSIZE(m_password2),
                         ImGuiInputTextFlags_Password);

        ImGui::NewLine();

        // Create Account
        SetAlignmentHorizontalCenter("Create Account", true);
        if (ImGui::Button("Create Account"))
        {
            
        }

        ImGui::NewLine();

        // Back
        SetAlignmentHorizontalCenter("Back", true);
        if (ImGui::Button("Back"))
        {
            SceneManager::GetInstance()->ChangeScene("Login");
        }
    }
    ImGui::End();
}

void CreateAccountScene::Finish()
{
    // Do nothing
}
}