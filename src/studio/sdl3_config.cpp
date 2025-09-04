
namespace SDL
{
    SDL_Window* CreateSDL3Window()
    {
        // Setup SDL
        // [If using SDL_MAIN_USE_CALLBACKS: all code below until the main loop starts would likely be your SDL_AppInit() function]
        if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
        {
            printf("Error: SDL_Init(): %s\n", SDL_GetError());
            return nullptr;
        }
    
        // GL 3.0 + GLSL 130
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    
        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        SDL_WindowFlags window_flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN | SDL_WINDOW_HIGH_PIXEL_DENSITY;
        SDL_Window* window = SDL_CreateWindow("Dear ImGui SDL3+OpenGL3 example", 1920, 1080, window_flags);
        if (window == nullptr)
        {
            printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
            return nullptr;
        }
        
        return window;
    }

    SDL_GLContext MakeGLContext(SDL_Window* window)
    {
        SDL_GLContext gl_context = SDL_GL_CreateContext(window);
        if (gl_context == nullptr)
        {
            printf("Error: SDL_GL_CreateContext(): %s\n", SDL_GetError());
            return nullptr;
        }
    
        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1); // Enable vsync
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        SDL_ShowWindow(window);

        return gl_context;
    }

    enum class ProcessResult
    {
        NotDone,
        Done,
        Minimized
    };

    ProcessResult ProcessEvents(SDL_Window* window)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        // [If using SDL_MAIN_USE_CALLBACKS: call ImGui_ImplSDL3_ProcessEvent() from your SDL_AppEvent() function]
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
            {
                return ProcessResult::Done;
            }
            if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED && event.window.windowID == SDL_GetWindowID(window))
            {    
                return ProcessResult::Done;
            }
        }

        // [If using SDL_MAIN_USE_CALLBACKS: all code below would likely be your SDL_AppIterate() function]
        if (SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED)
        {
            SDL_Delay(10);
            return ProcessResult::Minimized;
        }
        return ProcessResult::NotDone;
    }

    void Viewport(int width, int height, ImVec4 color)
    {
        // Render viewport
        glViewport(0, 0, width, height);

        glClearColor(color.x * color.w, color.y * color.w, color.z * color.w, color.w);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void SwapBackbuffer(SDL_Window* window)
    {
        SDL_GL_SwapWindow(window);
    }

    void Shutdown(SDL_GLContext context, SDL_Window* window)
    {
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

}
