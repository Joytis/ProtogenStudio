#include "ProtogenStudio.h"
#include "SimpleWindows.h"

#include "imgui.h"

#include <iostream>

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

    bool ProtogenStudio::RenderStandardUI(ImGuiIO& io)
    {
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
            ProtoWindows::RenderProtogenPanelsWindow(*_protogen);
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

    bool ProtogenStudio::Render(ImGuiIO& io)
    {
        float dt = io.DeltaTime;

        CheckInput();

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
            }
            else
            {
                shouldContinue = RenderStandardUI(io);
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

        return shouldContinue;
    }
}