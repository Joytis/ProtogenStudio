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
        _protogen = std::make_unique<Proto::Protogen>(_project.Settings());

        _initialized = true;
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
        _protogen->Update(_project, dt);
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
        for(int i = 0; i < _protogen->faceGrids.size(); i++)
        {
            // Render a grid. 
            const auto& grid = _protogen->faceGrids[i];
            int width = grid.Width();
            int height = grid.Height();

            SDL_Texture* texture = SDL_CreateTexture(
                SDL_GetRenderer(&window), 
                SDL_PIXELFORMAT_RGBA8888, 
                SDL_TEXTUREACCESS_STREAMING, 
                width, 
                height
            );
        
            // Nested, colored grid elements
            void *pixels;
            int pitch;
            SDL_LockTexture(texture, NULL, &pixels, &pitch);

            // Example: Set a pixel to red
            u32* pixel_data = (u32*)pixels;
            
            
            for(int y = 0; y < height; y++)
            {   
                for(int x = 0; x < width; x++)
                {
                    // pixel_data[y * (pitch / sizeof(u32)) + x] = grid.Get(x, y).ToRGBA(); // RGBA
                    float fWidth = static_cast<float>(width);
                    float fHeight = static_cast<float>(height);
                    u8 r = static_cast<u8>(((x / fWidth) * 255.0f));
                    u8 g = static_cast<u8>(((y / fHeight) * 255.0f));

                    u32 testColor = 0; 
                    testColor |= (r << 24);
                    testColor |= (r << 16);
                    testColor |= (0xFF);
                    pixel_data[y * (pitch / sizeof(u32)) + x] = testColor; // RGBA

                }
            }
            SDL_UnlockTexture(texture);
            _textures.push_back(texture);
        }
    }

    void ProtogenStudio::RenderProtogenPanelsWindow()
    {
        ImGui::Begin("Protogen Panels");   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

        assert(_protogen->faceGrids.size() == _textures.size());

        for(int i = 0; i < _protogen->faceGrids.size(); i++)
        {
            ImGui::SeparatorText("Face grid");

            constexpr float PIXEL_WIDTH = 10.0f;
            constexpr float PIXEL_HEIGHT = 10.0f;

            // Render a grid. 
            SDL_Texture* texture = _textures[i];
            const auto& grid = _protogen->faceGrids[i];
            float width = (grid.Width() * (PIXEL_WIDTH));
            float height = (grid.Height() * (PIXEL_HEIGHT));

            // Nested, colored grid elements
            ImVec2 size(width, height);
            ImGui::Image((ImTextureID)(intptr_t)texture, size);
        }
        
        ImGui::End();
    }

    void ProtogenStudio::ClearTextures()
    {
        for(auto& texture : _textures)
        {
            SDL_DestroyTexture(texture);
        }
        _textures.clear();
    }

    bool ProtogenStudio::Render(ImGuiIO& io, SDL_Window& window)
    {
        float dt = io.DeltaTime;

        CheckInput();

        // Start ImGUI frame
        ImGui::NewFrame();

        // Render the status bar at the bottom of screen. 
        _statusBar.Render(dt);

        bool shouldContinue = true;
        try
        {
            if(_hasError)
            {
                shouldContinue = RenderErrorUI(io);
            }
            else if(!_initialized)
            {
                shouldContinue = RenderProjectLoadUI(io);
                LoadProject(_rootPath);
                _initialized = true;
            }
            else
            {
                shouldContinue = RenderStandardUI(io, window);
            }
        }
        catch (const std::exception& e)
        {
            _hasError = true;
            _errorMessage = e.what();
            std::cout << "Caught an exception: " << _errorMessage << std::endl;
        }
        
        // Rendering
        ImGui::Render();
        ClearTextures();

        return shouldContinue;
    }
}