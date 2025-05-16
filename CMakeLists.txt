cmake_minimum_required(VERSION 3.26)
project(protogen_studio C CXX)

# C++ variables
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# This assumes the SDL source is available in libs/SDL
add_subdirectory(libs/SDL EXCLUDE_FROM_ALL)

# This assumes the SDL_image source is available in libs/SDL_image
add_subdirectory(libs/SDL_image EXCLUDE_FROM_ALL)

find_package(OpenGL REQUIRED)

# Protogen Library
file(GLOB_RECURSE PROTOGEN_SOURCES
    "src/protogen/*.cpp"
    "src/protogen/*.c"
)

set(EXTERNAL_INCLUDE_DIRS
    libs
    libs/SDL/include
    libs/SDL_image/include/SDL3_image
)

add_library(Protogen ${PROTOGEN_SOURCES})
target_include_directories(Protogen PRIVATE 
    ${EXTERNAL_INCLUDE_DIRS}
    src/protogen
)

# ---- Protogen Studio ---- 
file(GLOB_RECURSE STUDIO_SOURCES
    "src/studio/*.cpp"
    "src/studio/*.c"
)

# Dear ImGui - Explicitly list source files
set(IMGUI_INCLUDE_DIRS
    libs/imgui
    libs/imgui/backends
)

set(IMGUI_SOURCE_FILES
    libs/imgui/imgui_demo.cpp 
    libs/imgui/imgui_draw.cpp 
    libs/imgui/imgui_tables.cpp 
    libs/imgui/imgui_widgets.cpp 
    libs/imgui/imgui.cpp 
    libs/imgui/backends/imgui_impl_sdl3.cpp
    libs/imgui/backends/imgui_impl_opengl3.cpp
)

# Executable
add_executable(ProtogenStudio src/studio/main.cpp)

target_sources(ProtogenStudio PRIVATE 
    ${STUDIO_SOURCES} 
    ${IMGUI_SOURCE_FILES}
)

target_include_directories(ProtogenStudio PRIVATE 
    ${IMGUI_INCLUDE_DIRS} 
    ${EXTERNAL_INCLUDE_DIRS}
    ${INTERNAL_INCLUDE_DIRS}
    src/
)
target_link_libraries(ProtogenStudio Protogen SDL3::SDL3 OpenGL::GL SDL3_image::SDL3_image)

# ---- Post Build ----
file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})