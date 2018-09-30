// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GUI_FORGOT_PASSWORD_SCENE_H
#define HEARTHSTONEPP_GUI_FORGOT_PASSWORD_SCENE_H

#include <Scenes/Scene.h>

namespace Hearthstonepp
{
class ForgotPasswordScene : public Scene
{
public:
    ForgotPasswordScene() = default;
    ~ForgotPasswordScene() = default;

    void Start() override;

    void Input() override;

    void Update() override;

    void Finish() override;

 private:
    ImGuiWindowFlags m_flags = 0;

    bool m_isOpened = true;

    float m_positionX = 0.0f;
    float m_positionY = 0.0f;

    float m_width = 0.0f;
    float m_height = 0.0f;
};
}

#endif