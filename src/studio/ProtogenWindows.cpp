#include "protogen/Grid.h"

#include "imgui.h"
#include "imgui_internal.h"

#include "imgui_extensions/L2DFileDialog.h"

namespace Windows
{


    void RenderProjectSettingsWindow(Proto::Protogen& p)
    {
        ImGui::SeparatorText("Child windows");
        ImGui::BeginChild("Project Settings", ImVec2(0, 200), ImGuiChildFlags_None);

        ImGui::Text("Edit project settings here!");
        ImGui::Combo("Panel Hardware", (int*)(&p.panelHardware), Proto::PanelHardware_Names[0], (int)Proto::PanelHardware::MAX);

        // Testing file dialog
        static char* file_dialog_buffer = nullptr;
        static char path[512] = "";
        static bool coolBoolField = false;

        
        Controls::PathInput(coolBoolField, "Path", path, sizeof(path));

        ImGui::EndChild();
    }
    

    void RenderExpression(Proto::Expression& e)
    {
        e.editorTreeFoldedOut = ImGui::TreeNode("##Expression");
        ImGui::SameLine();
        ImGui::Text("%s", ExpressionType_Name(e.type));
        if(e.editorTreeFoldedOut)
        {

            ImGui::TreePop();
            
        }
    }

    void RenderExpressionGroup(Proto::Protogen& p, Proto::FacialRegion& region)
    {
        region.editorTreeFoldedOut = ImGui::TreeNode("##Facial Region");
        ImGui::SameLine();
        ImGui::Text("%s", FacialRegionType_Name(region.type));

        if(region.editorTreeFoldedOut)
        {
            // Render the Facial Region data
            bool treeActive = ImGui::TreeNode("Expressions");

            if(treeActive)
            {
                for(int i = 0; i < PROOT_ARRAYSIZE(region.expressions); i++)
                {
                    ImGui::PushID(i);
                    RenderExpression(region.expressions[i]);
                    ImGui::PopID();
                }
                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
    }

    void RenderExpressionGroups(Proto::Protogen& p)
    {
        if(ImGui::TreeNode("Facial Regions"))
        {
            // Render all the groups. 
            for(int i = 0; i < PROOT_ARRAYSIZE(p.facialRegions); i++)
            {
                ImGui::PushID(i);
                RenderExpressionGroup(p, p.facialRegions[i]);
                ImGui::PopID();
            }
            ImGui::TreePop();
        }
    }

    void RenderExpressionsWindow(Proto::Protogen& p)
    {
        ImGui::Begin("Expressions");

        RenderExpressionGroups(p);
        
        ImGui::End();

    }
}
