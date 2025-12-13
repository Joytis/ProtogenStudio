#include "ProtogenStudio.h"

#include "imgui.h"

#include "protogen/Common.h"

#include <iostream>


namespace Studio
{
    constexpr char SETTINGS_FILE[] = "settings.json";

    std::filesystem::path GetSettingsPath()
    {
        return std::filesystem::current_path()/SETTINGS_FILE;
    }

    bool ProtogenStudio::IsInitialized()
    {
        return !_settings.lastRootPath.empty();
    }

    void ProtogenStudio::LoadSettings()
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);
        
        std::filesystem::path path = GetSettingsPath();
        if(std::filesystem::exists(path))
        {
            Proto::Utils::LoadFromJSON(path, _settings);

            // If we have a project path, load it. 
            if(!_settings.lastProjectPath.empty())
            {
                std::filesystem::path projectPath = _settings.lastProjectPath;
                LoadProject(projectPath);
            }

            SDL_SetWindowSize(_window, _settings.lastWindowWidth, _settings.lastWindowHeight);
            SDL_SetWindowPosition(_window, _settings.lastWindowX, _settings.lastWindowY);
        }
    }
    
    void ProtogenStudio::LoadProject(std::filesystem::path& path)
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        // re-create our protogen
        _settings.lastProjectPath = path.string();
        _settings.lastRootPath = path.parent_path().string();

        // Try a project load
        auto loadResult =  Proto::Utils::LoadFromJSON(path, _protogen);
        _statusBar.SetStatus(StatusBar::Status::Info, loadResult.message);
        if(loadResult.result != Proto::LoadResultType::Success)
        {
            Controls::ErrorPopup(loadResult.message.c_str(), loadResult.message.size());
            _settings.lastRootPath.clear();
        }

        // Generate the SDL textures. 
        CreateFaceTextures();
    }

    void ProtogenStudio::CreateFaceTextures()
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        for(SDL_Texture* texture : _textures)
        {
            SDL_DestroyTexture(texture);
        }
        _textures.clear();

        // Create some textures
        for(auto& faceGrid : _protogen.panels)
        {
            int width = _protogen.PanelWidth();
            int height = _protogen.PanelHeight();

            SDL_Texture* texture = SDL_CreateTexture(
                SDL_GetRenderer(_window), 
                SDL_PIXELFORMAT_RGBA8888, 
                SDL_TEXTUREACCESS_STREAMING, 
                width, 
                height
            );
            SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);
            
            _textures.push_back(texture);
        }
    }
    
    bool ProtogenStudio::RenderErrorUI(ImGuiIO& io)
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        ImGui::Begin("ERROR!", &_hasError);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Continue"))
            _hasError = false;
        ImGui::End();
        return true;
    }

    void ProtogenStudio::RenderProjectLoadUI()
    {        
        CheckInput(MenuMode::NewOpen);
        RenderMenu(MenuMode::NewOpen);
    }

    void ProtogenStudio::New()
    {

    }

    void ProtogenStudio::Open()
    {
        _showOpenFileDialog = true;
    }

    void ProtogenStudio::ShowOpenModal()
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        char path[512] = {};
        if(_showOpenFileDialog)
        {
            auto result = Controls::RenderFileDialog(_showOpenFileDialog, path, ".proot");
            if(result != FileDialog::Result::None)
            {
                if(result == FileDialog::Result::Confirm)
                {
                    std::filesystem::path filePath = path;
                    LoadProject(filePath);
                }
            }
        }
    }
    
    void ProtogenStudio::Save()
    {
        std::filesystem::path path = _settings.lastProjectPath;
        Proto::Utils::SaveToJSON(path, _protogen);
        std::filesystem::path settingsPath = GetSettingsPath();
        Proto::Utils::SaveToJSON(settingsPath, _settings);

        std::string status_message = std::format("Save Successful! ({})", path.string());

        _statusBar.SetStatus(StatusBar::Status::Info, status_message);
    }

    void ProtogenStudio::ShowReloadModal()
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        if(_showReloadModal)
        {
            const char* message = "Are you sure you'd like to reload the project? All unsaved "
                "progress will be lost.";
    
            auto confirmCancel = Controls::ConfirmCancelPopup(message); 
            if(confirmCancel != Controls::ConfirmCancel::None)
            {
                _showReloadModal = false;
                if(confirmCancel == Controls::ConfirmCancel::Confirm)
                {
                    std::filesystem::path path = _settings.lastProjectPath;
                    LoadProject(path);
                }
            }
        }
    }

    void ProtogenStudio::Reload()
    {
        _showReloadModal = true;
    }

    void ProtogenStudio::RenderStudioSettings()
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        ImGui::SeparatorText("Studio Settings");
        ImGui::BeginChild("Studio Settings!", ImVec2(0, 120));

        ImGui::Checkbox("Demo Window", &showDemoWindow);
        ImGui::ColorEdit3("Background color", (float*)&clear_color);
        ImGui::EndChild();
    }

    void ProtogenStudio::CheckInput(MenuMode mode)
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        if(ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_N)) { New(); }
        if(ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_O)) { Open(); }
        if(mode == MenuMode::All)
        {
            if(ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_S)) { Save(); }
            if(ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_R)) { Reload(); }
        }
    }
    
    void ProtogenStudio::RenderMenu(MenuMode mode)
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        if (ImGui::BeginMainMenuBar())
        {
            // Menu!
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("New", "Ctrl+N")) { New(); }
                if (ImGui::MenuItem("Open", "Ctrl+O")) { Open(); }
                if(mode == MenuMode::All)
                {
                    ImGui::Separator();
                    if (ImGui::MenuItem("Save", "Ctrl+S")) { Save(); }
                    if (ImGui::MenuItem("Reload", "Ctrl+R")) { Reload(); }
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    bool ProtogenStudio::RenderStandardUI(ImGuiIO& io)
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        float dt = io.DeltaTime;

        CheckInput(MenuMode::All);

        // Update the protogen
        Protogen_Update(_protogen, dt);
        UpdateTextures();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (showDemoWindow)
            ImGui::ShowDemoWindow(&showDemoWindow);

        // Show the project settings window
        ImGui::Begin("Main Window");

        RenderMenu(MenuMode::All);

        RenderStudioSettings();

        Windows::RenderProjectSettingsWindow(_protogen);
        Windows::RenderExpressionsWindow(_protogen);
        RenderProtogenPanelsWindow();

        ImGui::End();

        return true;
    }

    void ProtogenStudio::UpdateTextures()
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        assert(_protogen.panels.size() == _textures.size());

        for(int i = 0; i < _protogen.panels.size(); i++)
        {
            SDL_Texture* texture = _textures[i];
            auto& grid = _protogen.panels[i].grid;
            int width = grid.Width();
            int height = grid.Height();

            // Nested, colored grid elements
            void *pixels;
            int pitch;
            if(SDL_LockTexture(texture, NULL, &pixels, &pitch))
            {
                u32* pixel_data = static_cast<u32*>(pixels);
                for (int y = 0; y < height; ++y) 
                {
                    for (int x = 0; x < width; ++x) 
                    {
                        pixel_data[y * (pitch / sizeof(u32)) + x] = Float4ToRGBAU32(grid.Get(x, y));
                    }
                }

                SDL_UnlockTexture(texture);
            } 
            else 
            {
                // Handle error
                std::cerr << "SDL_LockTexture failed: " << SDL_GetError() << std::endl;
            }

        }
    }

    void ProtogenStudio::RenderProtogenPanelsWindow()
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        ImGui::Begin("Protogen Panels");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

        assert(_protogen.panels.size() == _textures.size());

        for(int i = 0; i < _protogen.panels.size(); i++)
        {
            ImGui::SeparatorText("Face grid");

            constexpr float PIXEL_WIDTH = 10.0f;
            constexpr float PIXEL_HEIGHT = 10.0f;

            // Render a grid. 
            SDL_Texture* texture = _textures[i];
            const auto& grid = _protogen.panels[i].grid;
            float width = (grid.Width() * (PIXEL_WIDTH));
            float height = (grid.Height() * (PIXEL_HEIGHT));

            // Nested, colored grid elements
            ImVec2 size(width, height);
            ImGui::Image((ImTextureID)(intptr_t)texture, size);
        }
        
        ImGui::End();
    }

    bool ProtogenStudio::Render(ImGuiIO& io)
    {
        ZoneScopedCS(Proto::Color::ProtoImGui, Proto::StackDepth::Shallow);

        float dt = io.DeltaTime;

        // Render the status bar at the bottom of screen. 
        _statusBar.Render(dt);

        bool shouldContinue = true;
        if(_hasError)
        {
            shouldContinue = RenderErrorUI(io);
        }
        else if(!IsInitialized())
        {
            RenderProjectLoadUI();
        }
        else
        {
            shouldContinue = RenderStandardUI(io);
        }


        // Render all active modals
        ShowReloadModal();
        ShowOpenModal();

        // Skim the active window size. 
        SDL_GetWindowSize(_window, &_settings.lastWindowWidth, &_settings.lastWindowHeight);
        SDL_GetWindowPosition(_window, &_settings.lastWindowX, &_settings.lastWindowY);

        return shouldContinue;
    }
}