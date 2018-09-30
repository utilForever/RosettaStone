// Copyright (c) 2018 Chris Ohk, Youngjoong Kim, SeungHyun Jeon

// We are making my contributions/submissions to this project solely in our
// personal capacity and are not conveying any rights to any intellectual
// property of any third parties.

#ifndef HEARTHSTONEPP_GUI_IMGUI_UTILS_H
#define HEARTHSTONEPP_GUI_IMGUI_UTILS_H

#include <Manager/GameManager.h>
#include <Manager/SceneManager.h>

#include <imgui/imgui.h>

namespace Hearthstonepp
{
inline void SetAlignmentHorizontalCenter(const char* text, bool isButton)
{
    const ImVec2 textSize = ImGui::CalcTextSize(text, nullptr, true);

    if (isButton)
    {
        ImGui::SetCursorScreenPos(
            ImVec2(GameManager::GetInstance()->GetWindowWidth() * 0.5f -
                       (textSize.x / 2) - ImGui::GetStyle().WindowPadding.x,
                   ImGui::GetCursorScreenPos().y));
    }
    else
    {
        ImGui::SetCursorScreenPos(
            ImVec2(GameManager::GetInstance()->GetWindowWidth() * 0.5f -
                       (textSize.x / 2),
                   ImGui::GetCursorScreenPos().y));
    }
}
}

#endif