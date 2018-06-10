/*************************************************************************
> File Name: Scene.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Abstract base class for scene.
> Created Time: 2018/05/31
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_GUI_SCENE_H
#define HEARTHSTONEPP_GUI_SCENE_H

#include <imgui/imgui.h>

#include <string>

namespace Hearthstonepp
{
class Scene
{
 public:
    Scene() = default;
    virtual ~Scene() = default;

    virtual void Start() = 0;

    virtual void Input() = 0;

    virtual void Update() = 0;

    virtual void Finish() = 0;

    void SetName(std::string name)
    {
        m_name = name;
    }

    std::string GetName() const
    {
        return m_name;
    }

 protected:
    std::string m_name;
};
}

#endif