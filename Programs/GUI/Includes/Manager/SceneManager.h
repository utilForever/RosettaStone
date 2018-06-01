/*************************************************************************
> File Name: SceneManager.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Scene manager of Hearthstone++ GUI program.
> Created Time: 2018/05/31
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_GUI_SCENE_MANAGER_H
#define HEARTHSTONEPP_GUI_SCENE_MANAGER_H

#include <Scenes/Scene.h>

#include <SFML/Graphics/RenderWindow.hpp>

#include <string>
#include <vector>

namespace Hearthstonepp
{
class SceneManager
{
 public:
    SceneManager(const SceneManager& other) = delete;
    ~SceneManager() = delete;

    static SceneManager* GetInstance();

    sf::RenderWindow* GetWindow() const;

    void AddScene(Scene* scene);
    void AddPopupScene(Scene* scene);

    void PopInScene(const std::string& sceneName);
    void PopOutScene(const std::string& sceneName);

    void StartSceneManager(const std::string& sceneName);

    void ChangeScene(const std::string& sceneName);

 private:
    SceneManager() = default;

    Scene* GetSceneByName(const std::string& sceneName);
    Scene* GetPopupSceneByName(const std::string& sceneName);

    static SceneManager* m_instance;

    sf::RenderWindow* m_window = new sf::RenderWindow();

    Scene* m_actualScene;
    Scene* m_nextScene;
    bool m_isSceneChanged = false;

    std::vector<Scene*> m_sceneList;
    std::vector<Scene*> m_popupSceneList;
    std::vector<Scene*> m_visiblePopupSceneList;
};
}

#endif