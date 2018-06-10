/*************************************************************************
> File Name: ForgotPasswordScene.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Forgot password scene of Hearthstone++ GUI program.
> Created Time: 2018/06/04
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
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