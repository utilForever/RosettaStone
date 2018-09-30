// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#include <Manager/GameManager.h>
#include <Manager/SceneManager.h>
#include <Utils/Constants.h>

#include <hspp/Commons/Macros.h>

#include <imgui/imgui-SFML.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <cmath>

namespace Hearthstonepp
{
SceneManager* SceneManager::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new SceneManager();
    }

    return m_instance;
}

sf::RenderWindow* SceneManager::GetWindow() const
{
    return m_window;
}

void SceneManager::AddScene(Scene* scene)
{
    m_sceneList.push_back(scene);
}

void SceneManager::AddPopupScene(Scene* scene)
{
    m_popupSceneList.push_back(scene);
}

void SceneManager::PopInScene(const std::string& sceneName)
{
    Scene* scene = GetPopupSceneByName(sceneName);

    if (scene != nullptr)
    {
        m_visiblePopupSceneList.push_back(scene);
    }
}

void SceneManager::PopOutScene(const std::string& sceneName)
{
    Scene* scene = GetPopupSceneByName(sceneName);

    for (unsigned int i = 0; i < m_visiblePopupSceneList.size(); ++i)
    {
        if (scene == m_visiblePopupSceneList.at(i))
        {
            m_visiblePopupSceneList.erase(m_visiblePopupSceneList.begin() + i);
        }
    }
}

void SceneManager::StartSceneManager(const std::string& sceneName)
{
    sf::Clock deltaClock;

    // Init
    {
        // Create the window with a default values
        m_window->create(
            sf::VideoMode(GameManager::GetInstance()->GetWindowWidth(),
                          GameManager::GetInstance()->GetWindowHeight()),
            "Hearthstone++ GUI",
            (!sf::Style::Resize) | sf::Style::Titlebar | sf::Style::Close);
        m_window->setFramerateLimit(60);

        // Starts the GameManager
        GameManager::GetInstance()->Start(GetWindow());

        // Starts the SFML + ImGui
        ImGui::SFML::Init(*m_window);

        // Set the default values of the scene
        m_nextScene = GetSceneByName(sceneName);
        m_actualScene = m_nextScene;

        // Start the default scene
        m_actualScene->Start();

        m_window->clear(sf::Color::White);

        // ImGui style
        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowRounding = 0.0f;
        style.ChildRounding = 0.0f;
    }

    // Main loop
    sf::Event newEvent;
    while (GameManager::GetInstance()->IsOpen())
    {
        // Input
        while (m_window->pollEvent(newEvent))
        {
            ImGui::SFML::ProcessEvent(newEvent);

            // Close windows
            if (newEvent.type == sf::Event::Closed)
            {
                GameManager::GetInstance()->CloseWindow();
            }
        }

        // Update
        ImGui::SFML::Update(*m_window, deltaClock.restart());
        if (m_isSceneChanged)
        {
            GameManager::GetInstance()->ClearDrawList();
            m_actualScene->Finish();
            m_actualScene = m_nextScene;
            m_actualScene->Start();
            m_isSceneChanged = false;
        }
        m_actualScene = m_nextScene;
        m_actualScene->Input();
        m_actualScene->Update();

        // FPS and Latency
        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
        if (ImGui::BeginMainMenuBar())
        {
            char fps[256];
#ifdef HEARTHSTONEPP_WINDOWS
            sprintf_s(fps, "%.3f ms/frame (%.1f FPS)",
                      1000.0f / ImGui::GetIO().Framerate,
                      ImGui::GetIO().Framerate);
#else
            sprintf(fps, "%.3f ms/frame (%.1f FPS)",
                      1000.0f / ImGui::GetIO().Framerate,
                      ImGui::GetIO().Framerate);
#endif
            ImGui::MenuItem(fps);
            ImGui::EndMainMenuBar();
        }

        // Draw
        GameManager::GetInstance()->Draw();
        ImGui::SFML::Render(*m_window);
        m_window->display();
        m_window->resetGLStates();
    }

    // Finish the game
    ImGui::SFML::Shutdown();
    m_actualScene->Finish();
    m_actualScene = nullptr;
    m_nextScene = nullptr;
    GameManager::GetInstance()->Finish();
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
    Scene* newScene = GetSceneByName(sceneName);

    if (newScene != nullptr)
    {
        m_nextScene = newScene;
        m_isSceneChanged = true;
    }
}

float SceneManager::GetFontScale() const
{
    const sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    return std::max(std::ceil(videoMode.width / FONT_RATIO_STD_RES), 1.0f);
}

Scene* SceneManager::GetSceneByName(const std::string& sceneName)
{
    for (auto& scene : m_sceneList)
    {
        if (scene->GetName() == sceneName)
        {
            return scene;
        }
    }

    return nullptr;
}

Scene* SceneManager::GetPopupSceneByName(const std::string& sceneName)
{
    for (auto& scene : m_popupSceneList)
    {
        if (scene->GetName() == sceneName)
        {
            return scene;
        }
    }

    return nullptr;
}
}