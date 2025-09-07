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

    bool LineAddButton(const char* label)
    {
        ImGui::SeparatorText(label);
        ImGui::SameLine();
        return ImGui::Button("+");
    }
    
    void RenderExpression(Proto::Expression& e)
    {
        ImGui::SeparatorText("Expression");
        
    }

    void RenderExpressionGroup(Proto::Protogen& p, Proto::ExpressionGroup& group)
    {
        if(LineAddButton("Group"))
        {
            group.expressions.emplace_back(p.PanelWidth(), p.PanelHeight());
        }

        // Render all the groups. 
        for(int i = 0; i < group.expressions.size(); i++)
        {
            ImGui::PushID(i);
            RenderExpression(group.expressions[i]);
            ImGui::PopID();
        }
    }

    void RenderExpressionGroups(Proto::Protogen& p)
    {
        if(LineAddButton("Expression Groups"))
        {
            p.expressionGroups.emplace_back();
        }

        // Render all the groups. 
        for(int i = 0; i < p.expressionGroups.size(); i++)
        {
            ImGui::PushID(i);
            RenderExpressionGroup(p, p.expressionGroups[i]);
            ImGui::PopID();
        }
    }

    void RenderExpressionsWindow(Proto::Protogen& p)
    {
        ImGui::Begin("Expressions");

        RenderExpressionGroups(p);
        
        ImGui::End();

    }
}
