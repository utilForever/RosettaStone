/*************************************************************************
> File Name: LoginScene.h
> Project Name: Hearthstone++
> Author: Chan-Ho Chris Ohk
> Purpose: Login scene of Hearthstone++ GUI program.
> Created Time: 2018/05/31
> Copyright (c) 2018, Chan-Ho Chris Ohk
*************************************************************************/
#ifndef HEARTHSTONEPP_GUI_IMGUI_UTILS_H
#define HEARTHSTONEPP_GUI_IMGUI_UTILS_H

#include <Manager/GameManager.h>
#include <Manager/SceneManager.h>

#include <imgui/imgui.h>

namespace Hearthstonepp
{
void SetAlignmentHorizontalCenter(const char* text)
{
    ImVec2 textSize = ImGui::CalcTextSize(text, nullptr, true);
    ImGui::SetCursorScreenPos(
        ImVec2(GameManager::GetInstance()->GetWindowWidth() * 0.5f -
                   (textSize.x / 2) - ImGui::GetStyle().WindowPadding.x,
               ImGui::GetCursorScreenPos().y));
}
}

#endif