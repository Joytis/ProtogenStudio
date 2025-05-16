#pragma once

#include "Common.h"
#include "Grid.h"
#include "SDL3/SDL.h"

namespace Proto
{
    class Mouth
    {
        void LoadFromImage(SDL_Surface* surface);

        Grid<u8> grid;
    };
}