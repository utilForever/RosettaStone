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
    m_height = GameManager::GetInstance()->GetWindowHeight() * 0.4f;

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
}

void CreateAccountScene::Finish()
{
    // Do nothing
}
}