#include "Expression.h"

namespace Proto
{
    Expression::Expression(std::filesystem::path& rootPath, u32 width, u32 height) :
        path(rootPath),
        grid(width, height, false)
    {
        
    }
}
