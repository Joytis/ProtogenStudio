#include "Expression.h"

namespace Proto
{
    Expression::Expression(std::filesystem::path& rootPath, SDL_Surface* surface) :
        path(rootPath),
        grid(surface->w, surface->h, false)
    {
           
    }
}
