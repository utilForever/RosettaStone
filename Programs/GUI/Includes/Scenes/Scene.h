// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

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