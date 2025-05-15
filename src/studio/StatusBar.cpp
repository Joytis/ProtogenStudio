
#include "StatusBar.h"

#include "imgui.h"
#include "imgui_internal.h"

namespace Studio
{
    bool StatusBar::Render(float dt)
    {
        // ---- Change state ----
        _timeSinceLastMessage += dt;
        if(_timeSinceLastMessage > MAX_MESSAGE_TIME)
        {
            _message = "";
            _status = Status::Info;
        }
        
        // ---- Render bottom bar -----
        ImGuiContext& g = *GImGui;
        ImGuiViewportP* viewport = (ImGuiViewportP*)(void*)ImGui::GetMainViewport();

        // Notify of viewport change so GetFrameHeight() can be accurate in case of DPI change
        ImGui::SetCurrentViewport(NULL, viewport);

        // For the main menu bar, which cannot be moved, we honor g.Style.DisplaySafeAreaPadding to ensure text can be visible on a TV set.
        g.NextWindowData.MenuBarOffsetMinVal = ImVec2(g.Style.DisplaySafeAreaPadding.x, ImMax(g.Style.DisplaySafeAreaPadding.y - g.Style.FramePadding.y, 0.0f));
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
        // Cache build work position so we can reset it later. 
        auto oldBuildInsertMin = viewport->BuildWorkInsetMin;
        float height = ImGui::GetFrameHeight();
        // Manually position our status bar right at the edge of our screen. 
        viewport->BuildWorkInsetMin = ImVec2(0.0f, viewport->Size.y - height);
        bool is_open = ImGui::BeginViewportSideBar("##StatusMenuBar", viewport, ImGuiDir_Up, height, window_flags);

        g.NextWindowData.MenuBarOffsetMinVal = ImVec2(0.0f, 0.0f);
        if (!is_open)
        {
            ImGui::End();
            return false;
        }

        // Temporarily disable _NoSavedSettings, in the off-chance that tables or child windows submitted within the menu-bar may want to use settings. (#8356)
        g.CurrentWindow->Flags &= ~ImGuiWindowFlags_NoSavedSettings;
        ImGui::BeginMenuBar();

        // Render the status text here. 
        ImGui::Text(_message.c_str());

        ImGui::EndMenuBar();
        ImGui::End();

        // Set the build work position back to its original position
        viewport->BuildWorkInsetMin = oldBuildInsertMin;

        return is_open;
    }

    void StatusBar::SetStatus(Status status, const char* message)
    {
        _message = message;
        _status = status;
        _timeSinceLastMessage = 0.0f;
    }
}