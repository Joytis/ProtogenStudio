#pragma once

#include "protogen/ProtogenProject.h"

#include "StatusBar.h"

#include "imgui.h"

#include <filesystem>

namespace Studio
{
    class ProtogenStudio
    {
    public:
        ProtogenStudio(std::filesystem::path path) : _rootPath(path) {} 

        bool IsInitialized();

        void LoadProject(std::filesystem::path& path);

        void Save();
        void Reload();
        
        bool Render(ImGuiIO& io);
        
        void RenderStudioSettings();
        
        bool RenderStandardUI(ImGuiIO& io);
        bool RenderProjectLoadUI(ImGuiIO& io);
        bool RenderErrorUI(ImGuiIO& io);
        
        void CheckInput();

        bool showDemoWindow = true;
        bool showAnotherWindow = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        
    private:

        bool _hasError = false;
        bool _initialized = false;

        std::string _errorMessage;

        std::filesystem::path _rootPath;
        Proto::ProtogenProject _project;
        Studio::StatusBar _statusBar;
    };
}