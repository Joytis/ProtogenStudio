cmake_minimum_required(VERSION 3.26)
project(protogen_studio C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(protogen_studio src/main.cpp)

file(GLOB_RECURSE EXTRA_SOURCES
    "src/*.cpp"
    "src/*.c"
)

# Explicitly list source files
set(IMGUI_SOURCE_FILES
    libs/imgui/imgui_demo.cpp 
    libs/imgui/imgui_draw.cpp 
    libs/imgui/imgui_tables.cpp 
    libs/imgui/imgui_widgets.cpp 
    libs/imgui/imgui.cpp 
    libs/imgui/backends/imgui_impl_sdl3.cpp
    libs/imgui/backends/imgui_impl_opengl3.cpp
)

set(IMGUI_INCLUDE_DIRS
    libs/imgui
    libs/imgui/backends
)

target_sources(protogen_studio PRIVATE ${EXTRA_SOURCES} ${IMGUI_SOURCE_FILES})
target_include_directories(protogen_studio PRIVATE ${IMGUI_INCLUDE_DIRS})

target_link_libraries(protogen_studio SDL3::SDL3 OpenGL::GL)