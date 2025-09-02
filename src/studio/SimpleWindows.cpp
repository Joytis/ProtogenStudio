#include "SimpleWindows.h"

#include "protogen/Grid.h"

#include "imgui.h"
#include "imgui_internal.h"

namespace Studio::ProtoWindows
{
    void RenderProjectSettingsWindow(Proto::ProjectSettings& settings)
    {
        ImGui::SeparatorText("Child windows");
        ImGui::BeginChild("Project Settings", ImVec2(0, 200), ImGuiChildFlags_None);

        ImGui::Text("Edit project settings here!");
        ImGui::SliderInt("LED Panel Width", &settings.facePanelWidth, 1, Proto::MAX_GRID_WIDTH);
        ImGui::SliderInt("LED Panel Height", &settings.facePanelHeight, 1, Proto::MAX_GRID_HEIGHT);

        ImGui::EndChild();
    }

}
