// Dear ImGui: standalone example application for SDL3 + OpenGL
// (SDL is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)

// Learn about Dear ImGui:
// - FAQ                  https://dearimgui.com/faq
// - Getting Started      https://dearimgui.com/getting-started
// - Documentation        https://dearimgui.com/docs (same as your local docs/ folder).
// - Introduction, links and more at the top of imgui.cpp

#define IMGUI_DEFINE_MATH_OPERATORS

#include <stdio.h>
#include <iostream>

// Include all external .cpp files for our unity build. Nice. 
#include "external.cpp"
#include "internal.cpp"

// Main code
int main(int, char**)
{
    // SDL
    SDL_Window* window = SDL::CreateSDL3Window();
    SDL_Renderer* renderer = SDL::MakeRenderer(window);

    // ImGUI
    ImGuiIO& io = ImGUI::CreateImGUIIO(window, renderer);

    Studio::ProtogenStudio protogenStudio(window);

    // Main loop
    bool done = false;
    while (!done)
    {
        SDL::ProcessResult processResult = SDL::ProcessEvents(window);
        if(processResult == SDL::ProcessResult::Done)
        {
            done = true;
        }
        else if(processResult == SDL::ProcessResult::Minimized)
        {
            continue;
        }
        
        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        
        // Studio render
        ImGui::NewFrame();
        bool studioSuccess = protogenStudio.Render(io);
        ImGui::Render();

        // Render viewport
        SDL::Render(renderer, io, protogenStudio.clear_color);
    }

#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif
   
    ImGUI::Shutdown();
    SDL::Shutdown(window, renderer);
    return 0;
}