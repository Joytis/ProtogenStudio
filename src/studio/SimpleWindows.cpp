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

    void RenderProtogenPanelsWindow(const Proto::Protogen& protogen)
    {
        ImGui::Begin("Protogen Panels");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

        for(int i = 0; i < protogen.faceGrids.size(); i++)
        {
            ImGui::SeparatorText("Face grid");

            constexpr float BORDER = 10.0f;
            constexpr float SPACER = 2.0f;
            constexpr float PIXEL_WIDTH = 7.0f;
            constexpr float PIXEL_HEIGHT = 7.0f;
            
            // Render a grid. 
            const auto& grid = protogen.faceGrids[i];
            int width = grid->Width();
            int height = grid->Height();
            int childWidth = (grid->Width() * (SPACER + PIXEL_WIDTH)) + (BORDER * 2.0f);
            int childHeight = (grid->Height() * (SPACER + PIXEL_HEIGHT)) + (BORDER * 2.0f);

            ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoScrollWithMouse;
            ImVec2 p = ImGui::GetCursorScreenPos();
            ImGui::Dummy(ImVec2(childWidth, childHeight));

            // Nested, colored grid elements
            for(int y = 0; y < height; y++)
            {   
                for(int x = 0; x < width; x++)
                {
                    Proto::Vector4 myColor = grid->Get(x, y);
                    ImVec4 c(myColor.x, myColor.y, myColor.z, myColor.w);

                    int offsetX = BORDER + (x * (SPACER + PIXEL_WIDTH));
                    int offsetY = BORDER + (y * (SPACER + PIXEL_HEIGHT));

                    ImVec2 p1(p.x + offsetX, p.y + offsetY);
                    ImVec2 p2(p1.x + PIXEL_WIDTH, p1.y + PIXEL_HEIGHT);

                    auto imColor = IM_COL32(
                        IM_F32_TO_INT8_UNBOUND(c.x), 
                        IM_F32_TO_INT8_UNBOUND(c.y), 
                        IM_F32_TO_INT8_UNBOUND(c.z), 
                        IM_F32_TO_INT8_UNBOUND(c.w));

                    ImGui::GetWindowDrawList()->AddRectFilled(p1, p2, imColor);
                }
            }
        }
        
        ImGui::End();
    }

}
