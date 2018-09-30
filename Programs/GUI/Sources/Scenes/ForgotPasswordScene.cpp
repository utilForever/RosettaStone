// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Manager/SoundManager.h>
#include <Scenes/ForgotPasswordScene.h>
#include <Utils/ImGuiUtils.h>

#include <SFML/Window/Keyboard.hpp>

namespace Hearthstonepp
{
void ForgotPasswordScene::Start()
{
    GameManager::GetInstance()->SetBackground("Background_Login.png");
    SoundManager::GetInstance()->PlayMusic("BGM_Login.ogg");

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
}

void ForgotPasswordScene::Input()
{
    if (GameManager::GetInstance()->HasWindowFocus())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            SceneManager::GetInstance()->ChangeScene("Login");
        }
    }
}

void ForgotPasswordScene::Update()
{
    ImGui::SetNextWindowPos(ImVec2(m_positionX, m_positionY));
    ImGui::SetNextWindowPosCenter(true);

    ImGui::Begin("Create Account", &m_isOpened, ImVec2(m_width, m_height),
                 0.5f, m_flags);
    {
        ImGui::PushItemWidth(-1);

        ImGui::SetWindowFontScale(SceneManager::GetInstance()->GetFontScale());

        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();
        ImGui::NewLine();

        // Info
        SetAlignmentHorizontalCenter("Not supported yet.", false);
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Not supported yet.");

        ImGui::NewLine();
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

void ForgotPasswordScene::Finish()
{
    // Do nothing
}
}