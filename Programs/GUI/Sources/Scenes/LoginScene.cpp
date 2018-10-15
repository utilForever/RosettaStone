// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Manager/GameManager.h>
#include <Manager/NetworkManager.h>
#include <Manager/SoundManager.h>
#include <Scenes/LoginScene.h>
#include <Utils/ImGuiUtils.h>

#include <regex>

namespace Hearthstonepp
{
void LoginScene::Start()
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
    m_height = GameManager::GetInstance()->GetWindowHeight() * 0.4f;

    m_positionX =
        GameManager::GetInstance()->GetWindowWidth() * 0.5f - m_width * 0.5f;
    m_positionY =
        GameManager::GetInstance()->GetWindowHeight() * 0.5f - m_height * 0.5f;

    memset(m_email, 0, sizeof(m_email));
    memset(m_password, 0, sizeof(m_password));
}

void LoginScene::Input()
{
    // Do nothing
}

void LoginScene::Update()
{
    ImGui::SetNextWindowPos(ImVec2(m_positionX, m_positionY));
    ImGui::SetNextWindowPosCenter(true);

    ImGui::Begin("Login", &m_isOpened, ImVec2(m_width, m_height), 0.5f,
                 m_flags);
    {
        ImGui::PushItemWidth(-1);

        ImGui::SetWindowFontScale(SceneManager::GetInstance()->GetFontScale());

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Email:");
        ImGui::InputText("##Email", m_email, sizeof(m_email));

        ImGui::TextColored(ImVec4(1.0f, 1.0f, 1.0f, 1.0f), "Password:");
        ImGui::InputText("##Password", m_password, sizeof(m_password),
                         ImGuiInputTextFlags_Password);

        ImGui::NewLine();
        ImGui::NewLine();

        // Check Login
        SetAlignmentHorizontalCenter("Login", true);
        if (ImGui::Button("Login"))
        {
            if (IsValidLoginInfo())
            {
                if (NetworkManager::GetInstance()->Login(m_email, m_password))
                {
                    ImGui::OpenPopup("LoginSuccess");
                }
                else
                {
                    ImGui::OpenPopup("LoginFail");
                }
            }
            else
            {
                ImGui::OpenPopup("LoginFail");
            }
        }

        ImGui::NewLine();

        // Create Account
        SetAlignmentHorizontalCenter("Create Account", true);
        if (ImGui::Button("Create Account"))
        {
            SceneManager::GetInstance()->ChangeScene("CreateAccount");
        }

        ImGui::NewLine();

        // Forgot Password
        SetAlignmentHorizontalCenter("Forgot Password", true);
        if (ImGui::Button("Forgot Password"))
        {
            SceneManager::GetInstance()->ChangeScene("ForgotPassword");
        }

        ImGui::PopItemWidth();

        // Popup notifying login is success
        ImGui::SetNextWindowPosCenter(true);

        ImGui::SetWindowFontScale(SceneManager::GetInstance()->GetFontScale());

        if (ImGui::BeginPopup("LoginSuccess", m_popupFlags))
        {
            ImGui::SetWindowFontScale(
                SceneManager::GetInstance()->GetFontScale());

            SetAlignmentHorizontalCenter("Login success!", false);
            ImGui::Text("Login success!");

            ImGui::NewLine();

            SetAlignmentHorizontalCenter("Close", true);
            if (ImGui::Button("Close"))
            {
                ImGui::CloseCurrentPopup();
                SceneManager::GetInstance()->ChangeScene("Main");
            }

            ImGui::EndPopup();
        }

        // Popup notifying login is fail
        ImGui::SetNextWindowPosCenter(true);

        if (ImGui::BeginPopup("LoginFail", m_popupFlags))
        {
            ImGui::SetWindowFontScale(
                SceneManager::GetInstance()->GetFontScale());

            SetAlignmentHorizontalCenter("Login is failed.", false);
            ImGui::Text("Login is failed.");

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

void LoginScene::Finish()
{
    // Do nothing
}

bool LoginScene::IsValidLoginInfo() const
{
    // Check email is not empty and has valid format
    const std::string email = m_email;
    const std::regex emailPattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    if (!std::regex_match(email, emailPattern))
    {
        return false;
    }

    // Check password is not empty
    if (std::strlen(m_password) == 0)
    {
        return false;
    }

    return true;
}
}