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
    
    enum GroupResult
    {
        None,
        Remove
    };

    GroupResult RenderExpression(Proto::Expression& e)
    {
        ImGui::SeparatorText("Expression");
        ImGui::SameLine();
        if(ImGui::Button("-"))
        {
            return GroupResult::Remove;
            // Todo remove this expression
        }
        return GroupResult::None;
    }

    GroupResult RenderExpressionGroup(Proto::Protogen& p, Proto::ExpressionGroup& group)
    {
        ImGui::SeparatorText("Group");
        ImGui::SameLine();
        if(ImGui::Button("+"))
        {
            group.expressions.emplace_back(p.PanelWidth(), p.PanelHeight());
        }
        ImGui::SameLine();
        if(ImGui::Button("-"))
        {
            return GroupResult::Remove;
        }

        // Render all the groups.
        int toRemove = -1;
        for(int i = 0; i < group.expressions.size(); i++)
        {
            ImGui::PushID(i);
            if(RenderExpression(group.expressions[i]) == GroupResult::Remove)
            {
                toRemove = i;
            }
            ImGui::PopID();
        }
        // Remove something if we've noted we should!
        if(toRemove != -1)
        {
            group.expressions.erase(group.expressions.begin() + toRemove);
        }

        return GroupResult::None;
    }

    void RenderExpressionGroups(Proto::Protogen& p)
    {
        ImGui::SeparatorText("Expression Groups");
        ImGui::SameLine();
        if(ImGui::Button("+"))
        {
            p.expressionGroups.emplace_back();
        }

        // Render all the groups. 
        int toRemove = -1;
        for(int i = 0; i < p.expressionGroups.size(); i++)
        {
            ImGui::PushID(i);
            if(RenderExpressionGroup(p, p.expressionGroups[i])  == GroupResult::Remove)
            {
                toRemove = i;
            }
            ImGui::PopID();
        }
        // Remove something if we've noted we should!
        if(toRemove != -1)
        {
            p.expressionGroups.erase(p.expressionGroups.begin() + toRemove);
        }
    }

    void RenderExpressionsWindow(Proto::Protogen& p)
    {
        ImGui::Begin("Expressions");

        RenderExpressionGroups(p);
        
        ImGui::End();

    }
}
