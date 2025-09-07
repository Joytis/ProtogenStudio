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
        ProtogenStudio(SDL_Window* window) : _window(window) {}
    
        bool IsInitialized();

        void LoadProject(std::filesystem::path& path);
        void CreateFaceTextures();

        void New();
        void Open();
        void Save();
        void Reload();

        void ShowOpenModal();
        void ShowReloadModal();
        
        bool Render(ImGuiIO& io);
        
        void RenderStudioSettings();
        
        bool RenderStandardUI(ImGuiIO& io);
        void RenderProtogenPanelsWindow();


        void RenderProjectLoadUI();
        bool RenderErrorUI(ImGuiIO& io);
        
        enum class MenuMode
        {
            NewOpen,
            All
        };

        void CheckInput(MenuMode mode);
        void RenderMenu(MenuMode mode);


        void GenerateTextures();

        bool showDemoWindow = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
        
    private:

        bool _hasError = false;
        bool _showReloadModal = false;
        bool _showOpenFileDialog = false;

        std::string _errorMessage;
        Studio::StatusBar _statusBar;

        SDL_Window* _window;

        Proto::Protogen _protogen;
        std::filesystem::path _projectFilePath;
        std::filesystem::path _rootPath;
        std::vector<SDL_Texture*> _textures;
    };
}