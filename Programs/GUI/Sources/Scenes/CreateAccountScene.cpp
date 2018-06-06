/*************************************************************************
> File Name: CreateAccountScene.cpp
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Create account scene of Hearthstone++ GUI program.
> Created Time: 2018/06/06
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#include <Manager/NetworkManager.h>
#include <Manager/SoundManager.h>
#include <Scenes/CreateAccountScene.h>
#include <Utils/ImGuiUtils.h>

#include <regex>

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

    m_popupFlags |= ImGuiWindowFlags_AlwaysAutoResize;
    m_popupFlags |= ImGuiWindowFlags_NoTitleBar;

    m_width = GameManager::GetInstance()->GetWindowWidth() * 0.3f;
    m_height = GameManager::GetInstance()->GetWindowHeight() * 0.52f;

    m_positionX =
        GameManager::GetInstance()->GetWindowWidth() * 0.5f - m_width * 0.5f;
    m_positionY =
        GameManager::GetInstance()->GetWindowHeight() * 0.5f - m_height * 0.5f;

    memset(m_email, 0, sizeof(m_email));
    memset(m_nickname, 0, sizeof(m_nickname));
    memset(m_password1, 0, sizeof(m_password1));
    memset(m_password2, 0, sizeof(m_password2));
}

void CreateAccountScene::Input()
{
    // Do nothing
}

void CreateAccountScene::Update()
{
    ImGui::SetNextWindowPos(ImVec2(m_positionX, m_positionY));
    ImGui::SetNextWindowPosCenter(true);

    ImGui::Begin("CreateAccount", &m_isOpened, ImVec2(m_width, m_height), 0.5f,
                 m_flags);
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
            if (IsValidAccountInfo())
            {

            }
            else
            {
                ImGui::OpenPopup("CreateAccountFail");
            }
        }

        ImGui::NewLine();

        // Back
        SetAlignmentHorizontalCenter("Back", true);
        if (ImGui::Button("Back"))
        {
            SceneManager::GetInstance()->ChangeScene("Login");
        }

        // Popup notifying why create account is not possible
        ImGui::SetNextWindowPosCenter(true);

        if (ImGui::BeginPopupModal("CreateAccountFail", nullptr, m_popupFlags))
        {
            SetAlignmentHorizontalCenter("Create account is failed.", false);
            ImGui::Text("Create account is failed.");

            ImGui::NewLine();

            SetAlignmentHorizontalCenter("Try again.", false);
            ImGui::Text("Try again.");

            ImGui::NewLine();

            SetAlignmentHorizontalCenter("Close", true);
            if (ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
            }

            ImGui::EndPopup();
        }
    }
    ImGui::End();
}

void CreateAccountScene::Finish()
{
    // Do nothing
}

bool CreateAccountScene::IsValidAccountInfo() const
{
    // Check email is not empty and has valid format
    const std::string email = m_email;
    const std::regex emailPattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    if (!std::regex_match(email, emailPattern))
    {
        return false;
    }

    // Check Nickname is not empty
    if (std::strlen(m_nickname) == 0)
    {
        return false;
    }

    // Check two passwords not empty
    if (std::strlen(m_password1) == 0 || std::strlen(m_password2) == 0)
    {
        return false;
    }

    // Check two passwords are same
    if (std::strlen(m_password1) != std::strlen(m_password2) ||
        std::strcmp(m_password1, m_password2) != 0)
    {
        return false;
    }

    return true;
}
}