#pragma once

#include "protogen/Protogen.h"

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
        void CreateFaceTextures(SDL_Window* window);

        void Save();
        void Reload();
        
        bool Render(ImGuiIO& io, SDL_Window& window);
        
        void RenderStudioSettings();
        
        bool RenderStandardUI(ImGuiIO& io, SDL_Window& window);
        void RenderProtogenPanelsWindow();


        bool RenderProjectLoadUI(ImGuiIO& io);
        bool RenderErrorUI(ImGuiIO& io);
        
        void CheckInput();

        void GenerateTextures(SDL_Window& window);

        bool showDemoWindow = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        
    private:

        bool _hasError = false;
        bool _initialized = false;

        
        std::string _errorMessage;
        Studio::StatusBar _statusBar;
        
        Proto::Protogen _protogen;
        std::filesystem::path _rootPath;
        std::vector<SDL_Texture*> _textures;
    };
}