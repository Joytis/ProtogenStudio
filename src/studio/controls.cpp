
#include "Common.h"
#include "imgui_extensions/L2DFileDialog.h"


namespace Controls
{
    
    FileDialog::Result RenderFileDialog(bool& open, char* output, const char* extension = "")
    {
        if (open) 
        {
            return FileDialog::ShowFileDialog(open, output, extension);
        }
        return FileDialog::Result::None;
    }
    
    void PathInput(bool& open, const char* name, char* output, u32 outputSize, const char* extension = "")
    {
        ImGui::TextUnformatted(name);
        ImGui::InputText("##path", output, outputSize);
        ImGui::SameLine();
        if (ImGui::Button("Browse##path")) 
        {
            open = true;
        }

        RenderFileDialog(open, output, extension);
    }

    void ErrorPopup(const char* message, u32 size)
    {
        constexpr u32 MAX_SIZE = 2048;
        static char errorMessage[MAX_SIZE];
        u32 errorSize = sizeof(errorMessage) - 1;

        std::memset(errorMessage, '\0', sizeof(errorMessage));
        char* dest = errorMessage;
        std::strncpy(dest, message, Proto::Math::Minimum(size, errorSize));

        // Simple selection popup (if you want to show the current selection inside the Button itself,
        // you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
        ImGui::OpenPopup("studio_error_modal");
        ImGui::SameLine();
        if (ImGui::BeginPopup("studio_error_modal", ImGuiWindowFlags_Modal))
        {
            ImGui::SeparatorText("ERROR");
            ImGui::Text(errorMessage);
            // if(ImGui::Button("Close"))
            // {
            //     ImGui::EndPopup();
            // }
            ImGui::EndPopup();
        }
    }

    void InfoModal(const char* message, ImGuiWindowFlags flags = ImGuiWindowFlags_None)
    {
        // Simple selection popup (if you want to show the current selection inside the Button itself,
        // you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
        ImGui::OpenPopup("studio_info_modal");
        ImGui::SameLine();
        if (ImGui::BeginPopup("studio_info_modal", flags))
        {
            ImGui::SeparatorText("Info");
            ImGui::Text(message);
            ImGui::EndPopup();
        }
    }

    enum class ConfirmCancel
    {
        None,
        Confirm,
        Cancel
    };

    ConfirmCancel ConfirmCancelPopup(const char* message)
    {
        constexpr u32 MAX_SIZE = 2048;
        static char errorMessage[MAX_SIZE];
        std::strcpy(errorMessage, message);

        // Simple selection popup (if you want to show the current selection inside the Button itself,
        // you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
        ImGui::OpenPopup("studio_confirm_cancel_popup");
        ImGui::SameLine();
        
        ConfirmCancel result = ConfirmCancel::None;
        if (ImGui::BeginPopup("studio_confirm_cancel_popup", ImGuiWindowFlags_Modal))
        {
            ImGui::SeparatorText("ERROR");
            ImGui::Text(errorMessage);
            if(ImGui::Button("Confirm"))
            {
                ImGui::CloseCurrentPopup();
                result = ConfirmCancel::Confirm;
            }
            ImGui::SameLine();
            if(ImGui::Button("Cancel"))
            {
                ImGui::CloseCurrentPopup();
                result = ConfirmCancel::Cancel;
            }
            ImGui::EndPopup();
        }
        return result;
    }
}