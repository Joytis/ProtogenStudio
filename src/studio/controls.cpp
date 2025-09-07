
#include "Common.h"
#include "imgui_extensions/L2DFileDialog.h"


namespace Controls
{
    void PathInput(const char* name, char* output, u32 outputSize)
    {
        ImGui::TextUnformatted(name);
        ImGui::InputText("##path", output, outputSize);
        ImGui::SameLine();
        if (ImGui::Button("Browse##path")) {
            FileDialog::file_dialog_open = true;
        }

        if (FileDialog::file_dialog_open) {
            FileDialog::ShowFileDialog(
                &FileDialog::file_dialog_open, 
                output, 
                FileDialog::FileDialogType::OpenFile);
        }
    }


    void ErrorPopup(const char* message, u32 size)
    {
        constexpr u32 MAX_SIZE = 2048;
        static char errorMessage[MAX_SIZE];
        u32 errorSize = sizeof(errorMessage) - 1;

        std::memset(errorMessage, '\0', sizeof(errorMessage));
        char* dest = errorMessage;
        std::strncpy(dest, message, Proto::Utils::Minimum(size, errorSize));

        // Simple selection popup (if you want to show the current selection inside the Button itself,
        // you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
        ImGui::OpenPopup("studio_error_modal");
        ImGui::SameLine();
        if (ImGui::BeginPopup("studio_error_modal"))
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
}