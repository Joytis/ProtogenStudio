#pragma once

#include "Common.h"
#include "Grid.h"
#include "SDL3/SDL.h"

#include <filesystem>

namespace Proto
{
    struct Expression
    {
        Expression(std::filesystem::path& rootPath, u32 width, u32 height);

        std::filesystem::path path;
        Grid<u8> grid;
    };
}