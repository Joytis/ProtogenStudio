#pragma once

#include "Common.h"
#include "Grid.h"
#include "SDL3/SDL.h"

#include <filesystem>

namespace Proto
{
    struct Expression
    {
        Expression(std::filesystem::path& rootPath, SDL_Surface* surface);

        std::filesystem::path path;
        Grid<u8> grid;
    };
}