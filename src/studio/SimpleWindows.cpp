#include "SimpleWindows.h"

#include "protogen/Grid.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "imgui_extensions/L2DFileDialog.h"

namespace Studio::ProtoWindows
{
    void RenderProjectSettingsWindow(Proto::Protogen& p)
    {
        ImGui::SeparatorText("Child windows");
        ImGui::BeginChild("Project Settings", ImVec2(0, 200), ImGuiChildFlags_None);

        ImGui::Text("Edit project settings here!");
        ImGui::InputInt("LED Panel Width", &p.facePanelWidth, 1, Proto::MAX_GRID_WIDTH);
        ImGui::InputInt("LED Panel Height", &p.facePanelHeight, 1, Proto::MAX_GRID_HEIGHT);

        // Testing file dialog
        static char* file_dialog_buffer = nullptr;
        static char path[512] = "";
        static bool coolBoolField = false;

        Controls::PathInput(coolBoolField, "Path", path, sizeof(path));

        ImGui::EndChild();
    }

}
