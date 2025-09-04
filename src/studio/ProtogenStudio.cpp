#include "ProtogenStudio.h"
#include "SimpleWindows.h"

#include "imgui.h"

#include "protogen/Common.h"

#include <iostream>

using namespace Proto;

namespace Studio
{
    bool ProtogenStudio::IsInitialized()
    {
        return _initialized;
    }


    void ProtogenStudio::LoadProject(std::filesystem::path& path)
    {
        // Initialze the project. 
        _project.LoadProject(path);

        // re-create our protogen
        _protogen.Load(_project.Settings());
        

        _initialized = true;
    }

    void ProtogenStudio::CreateFaceTextures(SDL_Window* window)
    {
        for(SDL_Texture* texture : _textures)
        {
            SDL_DestroyTexture(texture);
        }
        _textures.clear();

        // Create some textures
        for(auto& faceGrid : _protogen.faceGrids)
        {
            int width = faceGrid.Width();
            int height = faceGrid.Height();

            SDL_Texture* texture = SDL_CreateTexture(
                SDL_GetRenderer(window), 
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
        ImGui::Begin("ERROR!", &_hasError);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Continue"))
            _hasError = false;
        ImGui::End();
        return true;
    }

    bool ProtogenStudio::RenderProjectLoadUI(ImGuiIO& io)
    {
        ImGui::Begin("LOADING PROJECT!!", &_initialized);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        ImGui::Text("Loading...");
        ImGui::End();
        return true;
    }

    void ProtogenStudio::Save()
    {
        _project.SaveProject(_rootPath);
        _statusBar.SetStatus(StatusBar::Status::Info, "Save successful!");
    }

    void ProtogenStudio::Reload()
    {
        LoadProject(_rootPath);
        _statusBar.SetStatus(StatusBar::Status::Info, "Reload successful!");
    }

    void ProtogenStudio::RenderStudioSettings()
    {
        ImGui::SeparatorText("Studio Settings");
        ImGui::BeginChild("Studio Settings!", ImVec2(0, 120));

        ImGui::Checkbox("Demo Window", &showDemoWindow);
        ImGui::Checkbox("Another Window", &showAnotherWindow);

        ImGui::ColorEdit3("Background color", (float*)&clear_color);
        ImGui::EndChild();
    }

    void ProtogenStudio::CheckInput()
    {
        if(ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_S))
        {
            Save();
        }
        if(ImGui::IsKeyChordPressed(ImGuiMod_Ctrl | ImGuiKey_R))
        {
            Reload();
        }
    }

    bool ProtogenStudio::RenderStandardUI(ImGuiIO& io, SDL_Window& window)
    {
        float dt = io.DeltaTime;

        // Update the protogen
        _protogen.Update(_project, dt);
        GenerateTextures(window);

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (showDemoWindow)
            ImGui::ShowDemoWindow(&showDemoWindow);

        // Show the project settings window
        {
            ImGui::Begin("Main Window");

            if (ImGui::BeginMainMenuBar())
            {
                // Menu!
                if (ImGui::BeginMenu("File"))
                {
                    if (ImGui::MenuItem("Save", "Ctrl+S"))
                    {
                        Save();
                    }
                    if (ImGui::MenuItem("Reload", "Ctrl+R"))
                    {
                        Reload();
                    }
                    ImGui::EndMenu();
                }
                ImGui::EndMainMenuBar();
            }

            RenderStudioSettings();

            ProtoWindows::RenderProjectSettingsWindow(_project.Settings());
            RenderProtogenPanelsWindow();

            ImGui::End();
        }

        // 3. Show another simple window.
        if (showAnotherWindow)
        {
            ImGui::Begin("Another Window", &showAnotherWindow);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                showAnotherWindow = false;
            ImGui::End();
        }

        return true;
    }

    void ProtogenStudio::GenerateTextures(SDL_Window& window)
    {
        assert(_protogen.faceGrids.size() == _textures.size());

        for(int i = 0; i < _protogen.faceGrids.size(); i++)
        {
            SDL_Texture* texture = _textures[i];
            auto& faceGrid = _protogen.faceGrids[i];
            int width = faceGrid.Width();
            int height = faceGrid.Height();

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
                        pixel_data[y * (pitch / sizeof(u32)) + x] = faceGrid.Get(x, y).ToRGBA();
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
        ImGui::Begin("Protogen Panels");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

        assert(_protogen.faceGrids.size() == _textures.size());

        for(int i = 0; i < _protogen.faceGrids.size(); i++)
        {
            ImGui::SeparatorText("Face grid");

            constexpr float PIXEL_WIDTH = 10.0f;
            constexpr float PIXEL_HEIGHT = 10.0f;

            // Render a grid. 
            SDL_Texture* texture = _textures[i];
            const auto& grid = _protogen.faceGrids[i];
            float width = (grid.Width() * (PIXEL_WIDTH));
            float height = (grid.Height() * (PIXEL_HEIGHT));

            // Nested, colored grid elements
            ImVec2 size(width, height);
            ImGui::Image((ImTextureID)(intptr_t)texture, size);
        }
        
        ImGui::End();
    }

    bool ProtogenStudio::Render(ImGuiIO& io, SDL_Window& window)
    {
        float dt = io.DeltaTime;

        CheckInput();

        // Render the status bar at the bottom of screen. 
        _statusBar.Render(dt);

        bool shouldContinue = true;
        if(_hasError)
        {
            shouldContinue = RenderErrorUI(io);
        }
        else if(!_initialized)
        {
            shouldContinue = RenderProjectLoadUI(io);
            LoadProject(_rootPath);
            CreateFaceTextures(&window);

            _initialized = true;
        }
        else
        {
            shouldContinue = RenderStandardUI(io, window);
        }

        return shouldContinue;
    }
}