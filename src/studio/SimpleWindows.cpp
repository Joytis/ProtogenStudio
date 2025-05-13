#include "SimpleWindows.h"
#include "imgui.h"

namespace Studio::ProtoWindows
{
    void RenderProjectSettingsWindow(Proto::ProjectSettings& settings)
    {
        ImGui::SeparatorText("Child windows");
        ImGui::BeginChild("Project Settings", ImVec2(0, 200), ImGuiChildFlags_None);

        ImGui::Text("Edit project settings here!");
        ImGui::InputInt("LED Panel Width", &settings.panelWidth);
        ImGui::InputInt("LED Panel Height", &settings.panelHeight);

        ImGui::EndChild();
    }
}
