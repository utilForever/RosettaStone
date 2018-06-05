/*************************************************************************
> File Name: ForgotPasswordScene.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Forgot password scene of Hearthstone++ GUI program.
> Created Time: 2018/06/04
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Manager/SoundManager.h>
#include <Scenes/ForgotPasswordScene.h>
#include <Utils/ImGuiUtils.h>

namespace Hearthstonepp
{
void ForgotPasswordScene::Start()
{
    GameManager::GetInstance()->SetBackground(IMAGES_DIR
                                              "Background_Login.png");
    SoundManager::GetInstance()->PlayMusic(SOUNDS_DIR "BGM_Login.ogg");

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
}

void ForgotPasswordScene::Update()
{
    ImGui::SetNextWindowSize(sf::Vector2f(450, 250), ImGuiCond_Always);
    ImGui::SetNextWindowPos(ImVec2(m_positionX, m_positionY));
    ImGui::SetNextWindowPosCenter(true);

    ImGui::Begin("Create Account", &m_isOpened, ImVec2(m_width, m_height),
                 0.5f, m_flags);
    {
        ImGui::PushItemWidth(-1);

        ImGui::SetWindowFontScale(1.0f);

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